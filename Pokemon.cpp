/*****************************************
 ** File:    Pokemon.cpp
 ** Project: CMSC 202 Project 3, Spring 2020, Covid-19 Era
 ** Author:  Dave Benton
 ** Date:    3/26/2020
 ** Section: 42
 ** E-mail:  dbenton2@umbc.edu
 ** Description: C++ file for the pokemon node class. Each node is a pokemon
 **              Each node has a name, type, index and health.
*****************************************/

#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <fstream>
#include "Pokemon.h"

using namespace std;


// Name: Pokemon
// Desc - Default Constructor
// Preconditions - None
// Postconditions - Creates Pokemon with default values
Pokemon::Pokemon()
{
  m_name = "";
  m_index = 0;
  m_type = "";
  m_strong = "";
  m_health = MAX_HEALTH;
  m_next = nullptr;
}


// Name: Pokemon(int, string, string, string)
// Desc - Overloaded Constructor
// Preconditions - Have index, name, type, and what the Pokemon is strong against
// Postconditions - Creates Pokemon using passed values
Pokemon::Pokemon(int index, string name, string type, string strong)
{
  m_name = name;
  m_index = index;
  m_type = type;
  m_strong = strong;
  m_health = MAX_HEALTH;
  m_next = nullptr;
}

// Name: GetNext
// Desc - Returns pointer to the next pokemon
// Preconditions - Pokemon exists
// Postconditions - Returns pointer to next pokemon in linked list
Pokemon* Pokemon::GetNext()
{
  return m_next;
}


// Name: GetName
// Desc - Returns Name
// Preconditions - Pokemon exists
// Postconditions - Returns name of Pokemon
string Pokemon::GetName()
{
  return m_name;
}


// Name: GetIndex
// Desc - Returns index
// Preconditions - Pokemon exists
// Postconditions - Returns index of Pokemon
int Pokemon::GetIndex()
{
  return m_index;
}


// Name: GetType
// Desc - Returns type
// Preconditions - Pokemon exists
// Postconditions - Returns type of Pokemon
string Pokemon::GetType()
{
  return m_type;
}


// Name: GetHealth
// Desc - Returns health
// Preconditions - Pokemon exists
// Postconditions - Returns health of Pokemon
int Pokemon::GetHealth()
{
  return m_health;
}


// Name: GetStrong
// Desc - Returns type of Pokemon this Pokemon is strong against
// Preconditions - Pokemon exists
// Postconditions - Returns type of Pokemon this Pokemon is strong against
string Pokemon::GetStrong()
{
  return m_strong;
}


// Name: SetHealth
// Desc - Sets health of pokemon
// Preconditions - Pokemon exists
// Postconditions - Updates health of Pokemon
void Pokemon::SetHealth(int health)
{
  m_health = m_health + health;//setup like this so I can use -ints to just add
}


// Name: SetNext
// Desc - Sets the pointer to the next Pokemon in the list
// Preconditions - Pokemon exists
// Postconditions - Sets the pointer to the next Pokemon
void Pokemon::SetNext(Pokemon* pokemon)
{
  m_next = pokemon;
}


// Name: Overloaded << Operator
// Desc - Allows us to cout a Pokemon object
// Preconditions - Pokemon exists
// Postconditions - When a Pokemon object is cout, shows name, health, and type
ostream &operator<<( ostream &output, Pokemon &P)
{
  output << P.GetName() << "(" << P.GetType()<<" : "<< P.GetHealth() << " health)" << endl;
}
