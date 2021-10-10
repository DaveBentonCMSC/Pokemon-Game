/*****************************************
 ** File:    PokemonList.cpp
 ** Project: CMSC 202 Project 3, Spring 2020, Covid-19 Era
 ** Author:  Dave Benton
 ** Date:    3/28/2020
 ** Section: 42
 ** E-mail:  dbenton2@umbc.edu
 ** Description: C++ file for the game class. Manages the game and populates the
 **              various PokemonList.
*****************************************/
#include "Game.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;


// Name: Game Constructor
// Desc - Creates a new game and sets m_filename based on string passed
// Additionally, makes m_list and userPoken = new PokemonLists
// Preconditions - Input file passed and populated with Pokemon
// Postconditions - m_filename, m_list, and userPocket created
Game::Game(string fileName)
{
  //sets all values
  m_filename = fileName;//sets filename
  m_list = new PokemonList();//dynamically creates big list
  m_userPocket = new PokemonList();//dynamically creates user list
  m_enemyPocket = new PokemonList();//dynamically crates enemy list
}


// Name: Game Destructor
// Desc - Calls destructor for all linked lists in game
// Preconditions - Linked lists populated
// Postconditions - m_list, userPocket, and enemyPocket are all destructed
Game::~Game()
{
  delete m_list;//deallocates big list
  delete m_userPocket;//deallocates user list
  delete m_enemyPocket;//deallocates enemy list
}


// Name: LoadFile
// Desc - Opens file and reads in each Pokemon. Each Pokemon dynamically allocated
// and put into m_list
// Preconditions - Input file passed and populated with Pokemon
// Postconditions - m_list populated with Pokemon
void Game::LoadFile()
{
  //creates variables for each pokemon attribute
  int index;
  string name;
  string type;
  string strong;
  ifstream myFile;
  myFile.open(m_filename);//opens file
  while(myFile >> index)//used to get pokemon's index, goes until it cannot
    {
      myFile.ignore(2, ',');//used to go to the next
      getline(myFile, name, ',');//sets name to name
      getline(myFile, type, ',');//sets type to type
      getline(myFile, strong);//sets it's strength to strong
      Pokemon *newPokemon = new Pokemon(index, name, type, strong);//creates a new pokemon
      m_list->InsertEnd(newPokemon);//inserts pokemon into big list
    }
  myFile.close();//closes file
}


// Name: ChooseTeam
// Desc - Allows user to choose team and populates m_userPocket
// Preconditions - m_list populated with Pokemon
// Postconditions - m_userPocket populated with Pokemon to battle
void Game::ChooseTeam()
{
  int usrChoice;//initalizes user choice
  int numPoke = 0;//number in user's team
  while (numPoke < NUM_TEAM)//goes until user has 5 pokemon
    {
      cout << "Here is a list of Pokemon you can choose from:"<<endl;//gets user choice
      cout << "------------------------------" <<endl;//formatting
      m_list->Display();//displays list of choices
      cout << "------------------------------" <<endl;
      cout << "Pick a pokemon by entering the index" << " (" << NUM_TEAM-numPoke
	   << "left):\n";
      cin >>usrChoice;//sets user choice to usrChoice
      while (m_list->Exist(usrChoice) == false)//validates
	{
	  cout << "That choice does not exist, Enter a valid choice: ";
	  cin >>usrChoice;
	}
      if (m_list->Exist(usrChoice))//if it exists
        {
          m_list->Transfer(usrChoice, m_userPocket);//transfers to user pocket
          numPoke++;//increments user's number of pokemon for loop
        }
    }
}


// Name: Menu
// Desc - Displays menu and returns choice
// Preconditions - m_list, m_userPocket, and m_enemyPocket all populated
// Postconditions - Returns choice
int Game::Menu()
{
  int usrChoice = 0;//initializes user choice
  cout << "Menu:" <<endl;
  cout << "1. Attack\n2. Swap\n3. Forfeit\n";
  cout << "------------------------------" << endl;
  cin >> usrChoice;//gets user choice
  return usrChoice;//returns user's choice
}


// Name: Battle
// Desc - Manages the battle between m_userPocket and m_enemyPocket.
// Displays both the m_userPocket and m_enemyPocket
// For each round, makes sure each team has Pokemon. Makes Pokemon in head fight.
// Indicates if the round yields user win, enemy win, and if a pokemon was switched
// Fights continue until there are no remaining Pokemon in one of the lists
// Preconditions - m_userPocket and m_enemyPocket must all be > 0 and populated
// Postconditions - Returns result of battle back to Start (1=user win, 2=cpu win)
int Game::Battle()
{
  int rounds = 1;//keeps track of rounds
  int attack;//for what the attack function returns
  int menu=0;//variable for menu choice
  int enemySize = m_enemyPocket->GetSize();//size of enemy list
  int usrSize = m_userPocket->GetSize();//size of user list
  //displays both pockets
  cout << "------------------------------\nUser Pocket\n";
  m_userPocket->Display();
  cout << "------------------------------\nEnemy Pocket\n";
  m_enemyPocket->Display();
  cout << "------------------------------" << endl;
  
  while (usrSize != 0 &&  enemySize != 0)//until user or enemy list is empty
    {
      cout << "Round " << rounds << ":" << endl;//prints the round
      cout << "Your Pokemon: " << *m_userPocket->GetHead();//prints user head
      cout << "CPU's Pokemon: " << *m_enemyPocket->GetHead();//prints enemy head
      cout << "------------------------------" << endl;
      menu = Menu();//uses the menu
      rounds++;//increases the round
      while(menu != 1 && menu != 2 && menu != 3)//validates menu input
	{
	  cout<<"Please enter a valid choice: ";
	  cin >> menu;
	  cout << endl;
	}
      if (menu == 1)//if user attacks
	{
	  attack = m_userPocket->Attack(m_enemyPocket);//gets outcome of attacking
	  cout << "------------------------------" << endl;
	  if (attack == 1)//if user faints
	    {
	      m_userPocket->Remove(m_userPocket->GetHead()->GetIndex());//removes from user list
	      usrSize = m_userPocket->GetSize();//changes size of user list
	      if (usrSize > 0)//if list is not empty
		{
		  m_userPocket->SwapPokemon();//has user swap a new pokemon to the head
		  cout << "------------------------------" << endl;
		}
	    }
	  else if (attack == 2)//if enemy faints
	    {
	      m_enemyPocket->Remove(m_enemyPocket->GetHead()->GetIndex());//removes from enemy pocket
	      enemySize = m_enemyPocket->GetSize();//changes size of enemy list
	    }
	}
      else if (menu == 2)//if user chooses swap
	{
	  m_userPocket->SwapPokemon();//lets user swap pokemon
	  cout << "------------------------------" << endl;
	}
      else//if user picks quit
	{
	  return 2;//returns 2 as user loses upon quit
	}
    }
  if (enemySize <= 0)//if enemy lost
    {
      return 1;//returns a 1
    }
  else if (usrSize <= 0)//if user loses
    {
      return 2;//returns 2
    }
}


// Name: Start
// Desc - Loads input file, allows user to choose their team, randomly populates the
// m_enemyPocket with remaining Pokemon and returns the result of the battle
// Preconditions - m_list, m_userPocket, and m_enemyPocket must all be PokemonLists
// Postconditions - Returns result of battle back to main
int Game::Start()
{
  LoadFile();//loads file
  ChooseTeam();//user chooses team
  int enemyNum = 0;//keeps track of num of enemy pokemon
  int battle;//used to return outcome of battle
  while (enemyNum < NUM_TEAM)//while the enemy team has less than 5 pokemon
    {
      int poke = rand() % m_list->GetSize();//picks a random number from the big list
      if (m_list->Exist(poke) == true)//if it exists
	{
	  m_list->Transfer(poke, m_enemyPocket);//transfers to enemy pocket
	  enemyNum++;//increases size of enemy list
	}
    }
  battle = Battle();//sets the outcome of Battle() to battle
  return battle;//returns the outcome
}
