#pragma once
#ifndef MOTIONTABLETENTRY_H
#define MOTIONTABLETENTRY_H
#include "AdventureRoom.h"
#include "Player.h"
#include "Door.h"

//class AdventureRoom;

class MotionTabletEntry {

	int currentRoom;
	Player* user;
	vector<string> directions;
	string userChoice;
	int index; // <- used to  keep track on the list of available directions
	bool open;
	vector<Door*> listDoorForEachDirection;
	vector<string> oldDirections;

public:
#pragma region basic constructor and destructor
	MotionTabletEntry();
	~MotionTabletEntry();
#pragma endregion
	void moveToRoom(Player *user, string choice);
	void setEXITS(string direction_Exit);
	void getLocation(string location, bool islocked);
	void getDirection();
	void useKey(string keyName, int exit);
	void setDoor(Door* doorTobeSet);
	Door* getDoor(int doorNumber);
	void editExit(string newExit, string oldExit);
	bool checkForDirection(string exit);
};
#endif // !MOTIONTABLETENTRY_H
