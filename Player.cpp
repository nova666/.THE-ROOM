#include "Player.h"
#include "Object.h"
#include <iostream>

//using namespace std;
Player::Player() {
	this->name = "Unknown";
	this->playerHP = 100;
	currentRoom = 0;
	stepsMade = 0;
}

/// this the function callsed to display items in the inventory
void Player::toString() {
	if (itemsInInventory.size() == 0)
	{
		cout << "I have nothing with me " << endl;
	}
	else
	{
		for (int i = 0; i < itemsInInventory.size(); i++)
		{
			cout << "|| Item n " << i + 1 << " | " << itemsInInventory.at(i)->getObjectName() << " ||" << endl;
		}
	}
	
	
}

vector<Object*> Player::getItemsInInventory()
{
	return itemsInInventory;
}

void Player::getInventory() {

	return toString();
}


void Player::setName(string newName) {

	this->name = newName;
}

void Player::setItemInInventory(Object* itemToStore)
{
if (itemToStore->getObjectName() == "CROWBAR")
{
	setEnableCrow(true);
}

if (itemsInInventory.size() < 5)
{
	itemsInInventory.push_back(itemToStore);
}
else
{
	cout << " I can't take anymore " << endl;
}

}

string Player::getName()
{
	return name;
}

void Player::setHp(int newHp)
{
	playerHP = newHp;
	if (playerHP <= 0)
	{
		setGameOver();
	}
}

int Player::getHp()
{
	return playerHP;
}
int Player::getCurrentLocation()
{
	return currentRoom;
}

void Player::setCurrentRoom(int newRoom)
{
	currentRoom = newRoom - 1;
	stepsMade++;
	int userNewscore = score - 10;
	score = userNewscore;
}

int Player::getSteps()
{
	return stepsMade;
}

bool Player::controlInventoryForItem(string item)
{
	for (int i = 0; i < itemsInInventory.size(); i++)
	{

		if (itemsInInventory.at(i)->getObjectName() == item)
		{

			indexLastItemControlled = i;
			return true;
		}
	}
	return false;
}        /////==== <=== used before to enable the usee of the key for the door

void Player::getDescriptionOfitem(int indexItem)   // <=== i better change this function
{
	itemsInInventory.at(indexItem)->examine();
}

void Player::setEnableCrow(bool enable)
{
	crowbarCollected = enable;
}

bool Player::getCrowBarStatus()
{
	return crowbarCollected;
}

Object* Player::removeItemfromInventory()
{
	Object* itemTOBeRemoved = itemsInInventory.at(indexLastItemControlled);
	itemsInInventory.erase(itemsInInventory.begin() + (indexLastItemControlled));

	return itemTOBeRemoved;
}

int Player::getScore()
{
	return score;
}

void Player::setScore(int score)
{
	this->score = score;
}

bool Player::getGameOver()
{
	return GAMEOVER;
}
void Player::setGameOver()
{
	GAMEOVER = true;
}

//// stilll need to add the motion 
