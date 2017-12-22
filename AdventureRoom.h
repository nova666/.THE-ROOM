#pragma once
#ifndef ADVENTUREROOM_H
#define ADVENTUREROOM_H
#include "Object.h"
#include <string>
#include <vector>
#include "Player.h"
#include <iostream>
#include <Windows.h>
#include "MotionTabletEntry.h"

using namespace std;

class MotionTabletEntry;

class AdventureRoom {
	private:
	int roomNumber;
	string roomName;
	vector<string> roomDescription;
	Object* objectinRoom;
	vector<Object*> objectsInRoom;
	vector<string> nameObjectsInRoom;  
	bool roomVisit = false;
	int directionChosen;
	//int roomcreated;
	vector<MotionTabletEntry*> listDirectionsMap;     
public:
	AdventureRoom(int roomNumber, string roomName, vector<string> roomDescription);
	~AdventureRoom();
	int getRoomNumber();
	void getRoomDescription();
	string getRoomName();
	void setDirectionsMap(vector<MotionTabletEntry*> listMap);     	
	void getValueDirection(Player *user, string choice);			
	void setObjectInRoom(Object* objectobeset);
	void getObjectInRoom();
	void takeItemFromRoom(string itemTotake, Player* user);
	int getNumberItemsInRoom();
	void setRoomDescription(vector<string> newRoomdescription);
	void setRoomVisited();
};
#endif // !ADVENTUREROOM_H





