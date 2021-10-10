/*****************************************
 ** File:    PokemonList.cpp
 ** Project: CMSC 202 Project 3, Spring 2020, Covid-19 Era
 ** Author:  Dave Benton
 ** Date:    3/28/2020
 ** Section: 42
 ** E-mail:  dbenton2@umbc.edu
 ** Description: C++ file for the linked list class. Each node is a pokemon
 **              Each node has a name, type, index and health.
*****************************************/

#include <iostream>
#include <string>
#include "PokemonList.h"
using namespace std;


// Name: PokemonList
// Desc - Default constructor for the PokemonList (linked list)
// Preconditions - None
// Postconditions - Creates an empty PokemonList (linked list)
PokemonList::PokemonList()
{
  
  m_head = nullptr;//sets m_head = nullptr so insertEnd can begin properly
  m_size = 0;//sets size to 0 so the size is properly incremented
}


// Name: ~PokemonList
// Desc - Destructor for the PokemonList (linked list)
// Preconditions - None
// Postconditions - Clears out a PokemonList (linked list)
PokemonList::~PokemonList()
{
  Pokemon *curr = m_head;//sets a temp value to the head
  while(curr != nullptr)//iterates to the end where the head = nullptr
    {
      m_head = curr;//sets m_head to the temp
      curr = curr ->GetNext();//sets the temp to it's next
      delete m_head;//deletes the "temp"
      m_head = nullptr;//sets it to nullptr
    }
  m_size = 0;//sets size back to 0
}


// Name: InsertEnd
// Desc - Inserts an already dynamically allocated Pokemon to end of linked list
// Preconditions - PokemonList already created
// Postconditions - The passed Pokemon appears at the end of the list
void PokemonList::InsertEnd(Pokemon *pokemon)
{
  Pokemon *temp = m_head;//sets a temp value to the head
  if (m_head == nullptr)//if the list is empty
    {
      m_head = pokemon;//m_head is now the first pokemon
      m_size = 1;//size of list is one
    }
  else
    {
      while(temp->GetNext() != nullptr)//while the list is not empty
	{
	  temp = temp->GetNext();//the temp is now it's next value
	}
      temp->SetNext(pokemon);//temp's next get's set to link everything
      m_size++;//size increases
    }
}


// Name: Display
// Desc - Iterates over PokemonList and displays each Pokemon formatted as in output
// Preconditions - PokemonList already created and has Pokemon
// Postconditions - Displayed Pokemon information
void PokemonList::Display()
{
  if(m_size == 0)//if the list is empty
    {
      cout << "The linked list is empty" << endl;
    }
  else
    {
      Pokemon *temp = m_head;//creates a temp that is now the head
      while(temp != nullptr)//until we reach the end
	{
	  cout << "Index: " << left << setw(4) << temp->GetIndex() <<" Name: "
	       << left << setw(10) << temp->GetName() << " Type: " << left <<
	    setw(8) << temp->GetType() << " Health: " << left<<setw(4)
	       <<temp->GetHealth()<< endl;//displays the current pokemon's index, name, type, and health
	  temp=temp->GetNext();//moves to the next pokemon
	}
    }
}


// Name: Transfer
// Desc - Searches for a Pokemon with a specific index. If found,
// creates a new Pokemon and copies it into the PokemonList passed in
// Preconditions - int is the index of the desired Pokemon and
// PokemonList is the destination
// Postconditions - Adds new Pokemon to the destination list and removes it from
// the source
void PokemonList::Transfer(int index, PokemonList* newPokemonList)
{
  Pokemon *temp = m_head;//sets a temp value to the head
  while(temp != nullptr)//while we don't reach the end of the list
    {
      if(temp->GetIndex() == index)//if the temp's index is the user's choice
	{
	  //next line creates a "new" pokemon from temp's info
	  Pokemon *newPokemon = new Pokemon(temp->GetIndex(), temp->GetName(),
					    temp->GetType(), temp->GetStrong());
	  newPokemonList->InsertEnd(newPokemon);//uses InsertEnd to add it to the
	                                        //user or enemy pocket
	  Remove(temp->GetIndex());//removes it from the big m_list
	}
      temp = temp->GetNext();//moves to the next in the list
    }
}


// Name: Remove (int)
// Desc - Searches for a Pokemon with a specific index. If found,
// removes it from the linked list
// Preconditions - int is the index of the desired Pokemon
// Postconditions - Removes Pokemon from linked list
void PokemonList::Remove(int index)
{
  Pokemon *temp = m_head;//creates a first temp value at head
  Pokemon *newTemp = m_head;//creates another temp value at head for linking
  if (index == temp->GetIndex())//if it is the head
    {
      m_head=newTemp->GetNext();//head is now the one after it
      delete temp;//deletes the head value
      temp = nullptr;//sets to nullptr 
      m_size--;//decrements size
    }
  else
    {
      //next line runs until the end of the list or we find the pokemon
      while(newTemp != nullptr && newTemp->GetIndex() != index)
	{
	  temp = newTemp;//sets temp as the head
	  newTemp = newTemp->GetNext();//sets newTemp as the next value
	}
      if(newTemp == nullptr)//if it's the end
	{ 
	  cout << "Invalid" << endl;//informs of invalid
	  return;//ends function
	}
      temp->SetNext(newTemp->GetNext());//sets temp's next to the next's next
      delete newTemp;//deletes new temp to manage mem
      newTemp = nullptr;//sets to nullptr
      m_size--;//decrements size
	 
    }
}


// Name: GetSize
// Desc - Returns the size of the linked list
// Preconditions - PokemonList is populated with Pokemon
// Postconditions - Returns the size of the linked list
int PokemonList::GetSize()
{
  return m_size;//used to access a linked lists size
}


// Name: GetHead
// Desc - Returns the Pokemon at the head of the linked list
// Preconditions - PokemonList is populated with Pokemon
// Postconditions - Returns the Pokemon at the head of the linked list
Pokemon* PokemonList::GetHead()
{
  return m_head;//used to access a lists head(beginning)
}


// Name: Attack(PokemonList)
// Desc - Passes an enemy pocket to the user's pocket to attack
// User always attacks the enemy Pokemon in this game
// Preconditions - This list is populated and enemy list is populated
// Postconditions - Does damage to the user Pokemon and enemy Pokemon
// and updates their health. Returns 2 if enemy Pokemon is less than 0
// Returns 2 if user's health is less than 0 else returns 0.
int PokemonList::Attack(PokemonList* enemyPocket)
{
  //I remember having trouble with this function, might be a mess
  int usrHealth = m_head->GetHealth();//gets user head's health
  int enmHealth = enemyPocket->m_head->GetHealth();//gets enemy head's health
  while(usrHealth > 0 && enmHealth > 0)//while neither head has fainted
    {
      int usrHealth = m_head->GetHealth();//gets their healths again to update loop
      int enmHealth = enemyPocket->m_head->GetHealth();
      if(m_head->GetStrong() == enemyPocket->m_head->GetType())//if user strong attacks
	{
	  enemyPocket->GetHead()->SetHealth(-STRONG_DAMAGE);//does damage to enemy head
	  cout << "CPU's pokemon took " <<STRONG_DAMAGE<< " damage" << endl;//outputs how much
	  enmHealth = enemyPocket->GetHead()->GetHealth();//updates enemy health for loop/return
	}
      else//for a regular attack
	{
	  enemyPocket->GetHead()->SetHealth(-DAMAGE2ENEMY);//does damage to enemy head
	  cout << "CPU's pokemon took "<<DAMAGE2ENEMY<<" damage" << endl;//outputs how much
	  enmHealth = enemyPocket->GetHead()->GetHealth();//updates health for loop/return
	}
      if(enmHealth < 1)//if enemy fainted
        {
          cout << "CPU's pokemon has been defeated" << endl;//informs user
          return 2;//ends function and returns enemy head fainted
        }
      if(enemyPocket->m_head->GetStrong() == m_head->GetType())//if enemy strong attacks
	{
	  m_head->SetHealth(-STRONG_DAMAGE);//does damage to user head
	  cout << "Your pokemon took "<<STRONG_DAMAGE<<" damage" << endl;//updates user
	  usrHealth = m_head->GetHealth();//updates health for loop and return
	}
      else//for a regular attack
	{
	  m_head->SetHealth(-DAMAGE2USER);//does damage to user head
	  cout << "Your pokemon took "<<DAMAGE2USER<<" damage" << endl;//informs user
          usrHealth = m_head->GetHealth();//updates health for loop
	}
      if (usrHealth < 1)//if user head fainted
	{
	  cout << "Your pokemon has been defeated" << endl;//informs user
	  return 1;//returns user fainted
	}
      else//if neither faints
	{
	  return 0;//returns 0 for neither fainting
	}
    }
}


// Name: SwapPokemon
// Desc - Allows user to move a Pokemon from any position into the first position
// Special cases: Empty list, Pokemon chosen at m_head or choice doesn't exist
// Preconditions - Linked list is populated
// Postconditions - User selects a Pokemon and it is moved into the first position
void PokemonList::SwapPokemon()
{
  Pokemon *prev = m_head;//creates a temp of the head
  Pokemon *curr = m_head;//creates another for linking
  int index;//initializes field for user choice
  cout<<"Which Pokemon would you like to choose? (Enter the index#)"<<endl;//gets user choice
  Display();//displays current list, whether m_list or m_userPocket
  cin >> index;//sets index to choice
  while (Exist(index) == false)//if that pokemon does not exist
    {
      cout << "That index does not exist, Enter a valid choice:";//reprompts
      cin >> index;//sets index again
    }
  if (index == m_head->GetIndex())//if their choice is the head
    {
      cout << "Choice is the Head" <<endl;//informs user
      cout << "You changed your pokemon to: " << *m_head;//informs of their new head
      return;//returns nothing because it should end here
    }
  //if not the head
  while(curr != nullptr)//iterates to the end
    {
      if(index == curr->GetIndex())//once we find the user's choice
	{
	  prev->SetNext(curr->GetNext());//sets the previous next to the current next
	  curr->SetNext(m_head);//sets current next to the head
	  m_head = curr;//sets head to the current
	}
      prev = curr;//sets previous to current
      curr = curr->GetNext();//current is now it's next
    }
  cout << "You changed your pokemon to: " << *m_head;//informs the user of their choice
}


// Name: Exist(int)
// Desc - Iterates through linked list looking for a specific index of a Pokemon
// Preconditions - PokemonList is populated with Pokemon
// Postconditions - Returns true if found else false
bool PokemonList::Exist(int index)
{
  Pokemon *temp = m_head;//creates a temp at the head
  while(temp != nullptr)//iterates to the end
    {
      if(temp->GetIndex() == index)//if the index is found
	{
	  return true;//returns true
	}
      temp = temp->GetNext();//moves to the next in the list
    }
  return false;//if never found, returns false/
}
