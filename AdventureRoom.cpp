#include "AdventureRoom.h"

AdventureRoom::AdventureRoom(int roomNumber, string roomName, vector<string> roomDescription)
{
	this->roomName = roomName;
	
	this->roomNumber = roomNumber;

	this->roomDescription = roomDescription;

}

int AdventureRoom::getRoomNumber()
{
	return roomNumber;
}
void AdventureRoom::getRoomDescription()
{
	
	for (int i = 0; i < roomDescription.size(); i++)
	{
		cout << roomDescription.at(i) << endl;
			
	}
}

string AdventureRoom::getRoomName()
{
	return roomName;
}

void AdventureRoom::setDirectionsMap(vector<MotionTabletEntry*> listMap)
{
	this->listDirectionsMap = listMap;
}

void AdventureRoom::getValueDirection(Player *user, string choice)               //// <- main responsible function for movement
{
	listDirectionsMap.at(user->getCurrentLocation())->moveToRoom(user, choice);
}


///// set the object in the room

void AdventureRoom::setObjectInRoom(Object* objectToBeSet)
{
	objectsInRoom.push_back(objectToBeSet);      /// <- set list of objects in the room 
	for (int i = 0; i < objectsInRoom.size(); i++)
	{
		nameObjectsInRoom.push_back(objectsInRoom.at(i)->getObjectName());
	}
	
	
}

void AdventureRoom::getObjectInRoom()
{
	
	if (objectsInRoom.size() == 0)
	{
		cout << " There is nothing useful here " << endl;
	}
	else
	{
		for (int i = 0; i < objectsInRoom.size(); i++)
		{
			cout << "Objects i can see in ther room are : " << "|" << objectsInRoom.at(0)->getObjectName() << "|" << endl;
			
		}

		
	}
	
}

void AdventureRoom::takeItemFromRoom(string itemTotake, Player* user)
{
	int index = 0;
	for (auto line = nameObjectsInRoom.begin(); line != nameObjectsInRoom.end(); ++line)
	{
		index++;
		if (line->find(itemTotake) != std::string::npos)
		{
			if (objectsInRoom.at(index - 1)->getObjectName() == "DEVIL")
			{
				cout << "Statue too BIG to be placed in inventory" << endl;
			}
			else if(objectsInRoom.at(index - 1)->getObjectName() == "SAFE")
			{
				cout << "Safe too heavy to be placed in inventory" << endl;
			}
			else
			{
				cout << "ITEM ADDED TO INVENTORY" << endl;   /// <- need to extract the number 
															 ///cout << " The direction and room is : " << directions.at(index - 1) << endl
				user->setItemInInventory(objectsInRoom.at(index - 1));

				objectsInRoom.erase(objectsInRoom.begin() + (index - 1));
			}
			
		}
	}
}

int AdventureRoom::getNumberItemsInRoom()
{
	int numberItemsInLocation = objectsInRoom.size();

	return numberItemsInLocation;
}

void AdventureRoom::setRoomDescription(vector<string> newRoomDescription)
{
	roomDescription = newRoomDescription;
}

void AdventureRoom::setRoomVisited()
{

	this->roomVisit = true;
}




