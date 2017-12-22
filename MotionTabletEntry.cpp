#include "MotionTabletEntry.h"
#include <iostream>
#include <string>
#include <sstream> 



	MotionTabletEntry::MotionTabletEntry()
	{
		
	}

	void MotionTabletEntry::moveToRoom(Player *user,string choice)
	{
		index = 0;
		bool locked = false;
		this->user = user;
		bool roomExist = false;
		/// find the world in the list
		for (auto line = directions.begin(); line != directions.end(); ++line)
		{

			index++;                              /////// <- used to find the index in vector
			if (line->find(choice) != std::string::npos)
			{
				
				roomExist = true;
				if (listDoorForEachDirection.at(index - 1)->getDoorState() == true)
				{
					getLocation(directions.at(index - 1), locked);  /// <- first check if the door open  then i move ther if it <- for now it works perfectly
					cout << " DOOR OPENED " << endl;
				}
				else
				{
					cout << " the door is locked " << endl;
					locked = true;
					getLocation(directions.at(index - 1), locked);
				}
				
			}
		}

		if (roomExist == false && locked == false)
		{
			cout << " I cant go that direction" << endl;
		}
		
	}

	void MotionTabletEntry::getLocation(string location, bool isLocked)
	{
		string s_Direction_room;
		string s_key_room;
		int extracted_RoomNumber;
		istringstream extract(location);

		extract >> s_Direction_room >> extracted_RoomNumber >> s_key_room;

		if (s_key_room == "" && isLocked == false)
		{
			if (s_Direction_room == "IN" && extracted_RoomNumber == 6)
			{
				cout << " YOU WON " << endl;
				user->setGameOver();
			}
			else
			{
				user->setCurrentRoom(extracted_RoomNumber);
			}
			
		}           
		else if (isLocked == true)
		{
			cout << "The door requires the current key " << s_key_room << endl;
		}
		else
		{
			user->setCurrentRoom(extracted_RoomNumber);
		}
	}

	void MotionTabletEntry::setEXITS(string direction_Exit)
	{
		directions.push_back(direction_Exit);

	}

	void MotionTabletEntry::getDirection()               /// <- used for debug
	{
		for (int i = 0; i < directions.size(); i++)
		{
			cout << " directions at: " << directions.at(i) << endl;
		}
	}
	void MotionTabletEntry::useKey(string keyName, int exit)
	{
		open = user->controlInventoryForItem(keyName);
		if (open == true)
		{
			user->setCurrentRoom(exit);
		
		}
		else
		{
			cout << " I don't have the key for the room " << endl;
		}
	}

	Door* MotionTabletEntry::getDoor(int doorNumber)
	{
		return listDoorForEachDirection.at(doorNumber);
	}

	void MotionTabletEntry::setDoor(Door* doorTobeSet)          /////   <-very important for use of the keys
	{
		listDoorForEachDirection.push_back(doorTobeSet);		///// <- need to implement the return value of this and check user input
	}
	

	void MotionTabletEntry::editExit(string newExit, string oldExit)
	{
		oldDirections = directions;
		index = 0;
		for (auto line = oldDirections.begin(); line != oldDirections.end(); ++line)
		{
			index++;                              /////// <- used to find the index in vector
			if (line->find(oldExit) != std::string::npos)
			{
				oldDirections.at(index - 1) = newExit;
			}
		}

		directions = oldDirections;
	}

	bool MotionTabletEntry::checkForDirection(string exit)
	{
		bool foundExit = false;
		for (auto line = directions.begin(); line != directions.end(); ++line)
		{                             /////// <- used to find the index in vector
			if (line->find(exit) != std::string::npos)
			{
				foundExit = true;
				
			}
		}
		return foundExit;
	}
