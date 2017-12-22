#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include "Object.h"
#include "Key.h"
#include <string>
#include <vector>

using namespace std;

class Player {
	vector<Object*>itemsInInventory; /// <- doesn't accept the key object
	int playerHP;
	string name;
	string userName;
	int currentRoom;
	int stepsMade;
	int score = 1000;
	int indexLastItemControlled = 0;
	bool crowbarCollected = false;
	bool GAMEOVER = false;
public:
	Player();
	~Player();
	void getInventory(); 
	void setName(string newName);
	void toString();
	int getCurrentLocation();
	void setItemInInventory(Object* itemToStore);
	void setCurrentRoom(int newRoom);
	string getName();
	int getHp();
	int getSteps();
	bool controlInventoryForItem(string item);
	void getDescriptionOfitem(int indexItem);
	vector<Object*> getItemsInInventory();
	void setHp(int newHp);
	void setEnableCrow(bool enable);
	bool getCrowBarStatus();
	Object* removeItemfromInventory();
	int getScore();
	void setScore(int score);
	bool getGameOver();
	void setGameOver();
	/// needs to be applied later when motionTabletEntry

private:

};

/*

void setItemInInventory(Object* Inventory[]);

void setScore();  /// needs to be applied later when motionTabletEntry

*/
#endif // !PLAYER_H
