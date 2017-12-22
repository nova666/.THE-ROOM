#pragma once
#ifndef ADVENTURE_H
#define ADVENTURE_H
#include <iostream>
#include "Player.h"
#include "AdventureRoom.h"
#include "Object.h"
#include <fstream>
#include <cstdlib>
#include "MotionTabletEntry.h"
#include "Key.h"
#include "Door.h"
#include "Statue.h"
#include "Safe.h"
#include "CrowBar.h"
#include <conio.h>
#include <algorithm>
#define std_con_out GetStdHandle(STD_OUTPUT_HANDLE)

class Adventure {
	Player *user;
	int room;
	string roomName;
	vector<string> descriptionFromFile;
	string description;
	string object;
	string userInput;
	string verbsInSystem[6];
	vector<string> verbKnowByTheSystem;
	enum concol;
	bool gameOver;
	int userChoice;
#pragma region organizing the data

	                                  /// defining Directions for MotionTablet list
	string direction_Exits = " ";
	vector<string> lines;         //// <- used for structuring the data from the file
	bool connectionsSet = false;
	bool numberRoomSet = false;
	int n_lastRoomCreated = 0;
	int numberRoomInMap = 5;
	bool setDescription = false;  //// <-
	AdventureRoom* roomObj;
	Safe* safeBox;
	CrowBar* crowBar;
	bool safeOpened = false;
	bool itemReceiveFromSafe = false;
	//int indexInput;
	vector<AdventureRoom*> listRooms;
	vector<string> newDesciptionRoom;
	//// Hold Exits Object and Lists
	MotionTabletEntry* exitsForRooms;
	vector<MotionTabletEntry*> listDirectionInMotionTablet;  // <=  doesn't work anynmore
	vector<Door*> listOfDoorsRoom1;
	vector<Door*> listOfDoorsRoom2;
	vector<Door*> listOfDoorsRoom3;
	vector<Door*> listOfDoorsRoom4;
	vector<Door*> listOfDoorsRoom5;
	vector<Door*> tempContainerList;
	vector<Key*> listOfKeys;
	vector<Statue*> listOfStatues;
#pragma endregion

	

public:
	Adventure();
	~Adventure();
	void guiStatistics(Player *user);
	void guiDescription(Player *user);
	void readRoom(ifstream& roomFile);
	void checkWordsInSystem(string userInput);
	void gameOverScreen();
	void goOtherRoom(Player* user);
	void lookForItems(Player *user);
	void takeItem();
	void checkInventory();
	void help();
	void createItems_Doors();
	void examineRoom();
	void safeButtonPressed();
	void loadNewDescriptions();
	void setcolor(concol textcol, concol backcol);
	void dropObject();
	
};
#endif // !ADVENTURE_H

