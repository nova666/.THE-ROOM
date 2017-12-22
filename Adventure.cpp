#include <iostream>
#include <stdlib.h> 
#include <Windows.h>
#include "Adventure.h"



enum Adventure::concol // enumeration type
{
	black = 0,
	dark_blue = 1,
	dark_green = 2,
	dark_aqua, dark_cyan = 3,
	dark_red = 4,
	dark_purple = 5, dark_pink = 5, dark_magenta = 5,
	dark_yellow = 6,
	dark_white = 7,
	gray = 8,
	blue = 9,
	green = 10,
	aqua = 11, cyan = 11,
	red = 12,
	purple = 13, pink = 13, magenta = 13,
	yellow = 14,
	white = 15
};


void Adventure::setcolor(concol textcol, concol backcol)
{
	// Combine the two 4-bit numbers into a single 8-bit number
	// If backcol is abcd in binary, and textcol is efgh, the result is abcdefgh
	unsigned short wAttributes = (backcol << 4) | textcol;
	// set the attributes for the console
	SetConsoleTextAttribute(std_con_out, wAttributes);
}

	Adventure::Adventure()
	{
		/// staring the game loading txt
		ifstream adventureFile;
		adventureFile.open("roomFile.txt", ios::in);

		ifstream& roomFile = adventureFile;

		readRoom(roomFile);
		system("cls");
		for (int i = 0; i < listRooms.size(); i++)
		{
			listRooms.at(i)->setDirectionsMap(listDirectionInMotionTablet);
		}																////< -need to pass more lists to other rooms
		
		user = new Player();
		
		guiDescription(user);
		guiStatistics(user);

		system("cls");
		
		do
		{
			cout << "                                 My Name Is :" << endl;
			
			cin >> userInput;
		} while (userInput == "0");
		transform(userInput.begin(), userInput.end(), userInput.begin(), ::toupper);
		Sleep(1500);
		user->setName(userInput);
		guiDescription(user);
		guiStatistics(user);

		setcolor(red, white);
		do
		{
			system("cls");
			
			guiStatistics(user);
			guiDescription(user);
			if (listDirectionInMotionTablet.at(user->getCurrentLocation())->checkForDirection("FORCED") == false && user->getGameOver() == false)
			{
				setcolor(white, blue);
				cout << " What you want me to do" << endl;
				cin >> userInput;
				checkWordsInSystem(userInput);
				
			}
			else if (user->getGameOver() == true)
			{
				userChoice = 10;
			}
			else
			{
				userChoice = 9;
				int userhp = user->getHp() - 20;
				user->setHp(userhp);
				int usernewScore = user->getScore() - 25;
				user->setScore(usernewScore);
			}
			switch (userChoice)
			{
			case 0:
				gameOver = false;
				break;
			case 1:
				// help
				
				help();
				break;
			case 2:
				
				lookForItems(user);
				break;
			case 3:
				// inventory
				
				checkInventory();
				break;
			case 4:
				
				takeItem();
				// take
				break;
			case 5:
				
				goOtherRoom(user);
				break;
			case 6:
				examineRoom();
				break;
			case 7:
				dropObject();
				break;
			case 8:
				safeButtonPressed();  // << used here for quick walkthrouh
				break;
			case 9:
				/// FORCED Move
				listRooms.at(user->getCurrentLocation())->getValueDirection(user, "FORCED");
				Sleep(1500);  //// <= herer the sleep function works fine
				system("cls");
				guiStatistics(user);
				guiDescription(user);
			case 10:
				cout << " COMPLIMENTS YOU COMPLETED THE GAME " << endl;
				cout << "  " << endl;
				cout << " THANKS FOR PLAYING " << endl;
				Sleep(3000);
				gameOver = false;
			default:
				cout << " i don't understand" << endl;
				break;
			}
			setcolor(red, white);

		} while (userChoice != 0);

		system("cls");
		if (gameOver == false)
		{
		gameOverScreen();
		}
	}

	void Adventure::checkWordsInSystem(string userInput)
	{
		transform(userInput.begin(), userInput.end(), userInput.begin(), ::toupper);
		userChoice = -1;
		if (userInput == "QUIT")
		{
			userChoice = 0;
		}
		if (userInput == "HELP")
		{
			userChoice = 1;
		}
		if (userInput == "LOOK")
		{
			userChoice = 2;
		}
		if (userInput == "INVENTORY")
		{
			userChoice = 3;
		}
		if (userInput == "TAKE")
		{
			userChoice = 4;
		}
		if (userInput == "MOVE")
		{
			userChoice = 5;
		}
		if (userInput == "EXAMINE")
		{
			userChoice = 6;
		}
		if(userInput == "DROP")
		{
			userChoice = 7;
		}
		if (userInput == "BUTTON")
		{
			userChoice = 8;
		}
	}

	void Adventure::gameOverScreen()
	{
		
			system("cls");
			cout << "================================================================================" << endl;
			cout << "================================================================================" << endl;
			cout << "================================================================================" << endl;
			cout << "================================================================================" << endl;
			cout << "================================================================================" << endl;
			cout << "================================================================================" << endl;
			cout << "================================= GAME OVER ==================================== " << endl;
			cout << "================================================================================" << endl;
			cout << "================================================================================" << endl;
			cout << "================================================================================" << endl;
			cout << "================================================================================" << endl;
			cout << "================================================================================" << endl;
			
		
	}

	void Adventure::readRoom(ifstream& roomFile)
	{
		/// check for error
		if (roomFile.fail()) {
			cerr << "Error opening file" << endl;
			exit(1);
		}

		///// importing data.file
		while (roomFile.good())
		{
			string line;
			getline(roomFile, line);
			cout << line << endl;
			lines.push_back(line);
		}

		///// testing organizing the data

		for (int a = 0; a < numberRoomInMap; a++)
		{
			exitsForRooms = new MotionTabletEntry();
			
			for (int i = 0; i < lines.size() - 1; i++)   ///go through the entire script minus last line
			{
				
				if (atoi(lines[i].c_str()) == a + 1)
				{
					
					room = atoi(lines[i].c_str());

					n_lastRoomCreated = atoi(lines[i].c_str()); //// Identify number of room beong created in the bulk of code
					numberRoomSet = true;
				}

				else if (lines[i + 1] == "/////" && numberRoomSet == true)   /// name of the room
				{
					roomName = lines[i];
					
				}
				else if ((lines[i] == "/////" || lines[i] == "*****" || lines[i] == "=*=*=" || lines[i] == "=====") && numberRoomSet == true)
				{
					
					if (lines[i] == "/////")
					{
						setDescription = true;
					}
					else if (lines[i] == "*****")
					{
						setDescription = false;
					}
					else if (lines[i] == "=*=*=")
					{
						connectionsSet = true;
					}
					else if (lines[i] == "=====")
					{
						numberRoomSet = false;
						connectionsSet = false;
						
						cout << "reading in file complete" << endl;
						
					}
				}
				else if (setDescription == true && numberRoomSet == true)
				{
					descriptionFromFile.push_back(lines[i]);
					    //// <= delete later
				}
				else if (connectionsSet == true && numberRoomSet == true)
				{
					
					direction_Exits = lines[i];
					exitsForRooms->setEXITS(direction_Exits);
				}

			}
			
			roomObj = new AdventureRoom(room, roomName, descriptionFromFile);
			listRooms.push_back(roomObj);
			
			listDirectionInMotionTablet.push_back(exitsForRooms);
			
			numberRoomSet = false;
			description = " ";

			descriptionFromFile.clear();

		}
		

		createItems_Doors();

		for (int i = 0; i < listRooms.size(); i++)
		{

			listRooms.at(i)->setDirectionsMap(listDirectionInMotionTablet);
					
		}
		

		int y = 0;
		for (int i = 0; i < listOfDoorsRoom1.size(); i++)              /// <-create door for each connection
		{
			listDirectionInMotionTablet.at(y)->setDoor(listOfDoorsRoom1.at(i));
		}
		y++;
		for (int i = 0; i < listOfDoorsRoom2.size(); i++)              /// <-create door for each connection
		{
			listDirectionInMotionTablet.at(y)->setDoor(listOfDoorsRoom2.at(i));
		}
		y++;
		for (int i = 0; i < listOfDoorsRoom3.size(); i++)              /// <-create door for each connection
		{
			listDirectionInMotionTablet.at(y)->setDoor(listOfDoorsRoom3.at(i));
		}
		y++;
		for (int i = 0; i < listOfDoorsRoom4.size(); i++)              /// <-create door for each connection
		{
			listDirectionInMotionTablet.at(y)->setDoor(listOfDoorsRoom4.at(i));
		}
		y++;
		for (int i = 0; i < listOfDoorsRoom5.size(); i++)              /// <-create door for each connection
		{
			listDirectionInMotionTablet.at(y)->setDoor(listOfDoorsRoom5.at(i));
		}

		safeBox = new Safe("safe", "Old looking safe");
		crowBar = new CrowBar("CROWBAR", "metal crowbar");
		listRooms.at(3)->setObjectInRoom(safeBox);
		listRooms.at(2)->setObjectInRoom(crowBar);
		listRooms.at(0)->setObjectInRoom(listOfStatues.at(0));
		listRooms.at(1)->setObjectInRoom(listOfKeys.at(0)); //<<--- trying to set items in room // setup a normal key in this room
		listRooms.at(4)->setObjectInRoom(listOfKeys.at(1));


	

		cout << "////////////////" << endl;
	}

	void Adventure::createItems_Doors()
	{
		///// Setting doors for exits
		///1stroom
		Door* woodenDoor = new Door(true, "normal door made with wood", "door");           //// <- east   <- door not open
		listOfDoorsRoom1.push_back(woodenDoor);
		Door* glassDoor = new Door(false, "normal door made with glass", "door");      /// <-  west
		listOfDoorsRoom1.push_back(glassDoor);
		Door* woodenDoor2 = new Door(false, "door made with glassed window", "glass door");   /// <- north
		listOfDoorsRoom1.push_back(woodenDoor2);
		Door* woodenDoor3 = new Door(true, "normal door made with wood", "door");           /// <- south
		listOfDoorsRoom1.push_back(woodenDoor3);
		

		///2nd room
		Door* woodenDoor4 = new Door(true, "normal door made with wood", "wooden Door");
		listOfDoorsRoom2.push_back(woodenDoor4);

		/// 3d room
		Door* woodenDoor5 = new Door(true, "normal door made with wood", "wooden Door");
		listOfDoorsRoom3.push_back(woodenDoor5);

		// 4th room
		Door* woodenDoor6 = new Door(true, "door made with glassed window", "glass doorr");
		listOfDoorsRoom4.push_back(woodenDoor6);

		// 5th room
		Door* woodenDoor7 = new Door(true, "normal door made with wood", "wooden Door");
		listOfDoorsRoom5.push_back(woodenDoor7);

		// Keys
		Key* normalKey = new Key("steel key", "normal key");
		listOfKeys.push_back(normalKey);
		
		Key* redKey = new Key("red emblem", "red key");
		listOfKeys.push_back(redKey);
		//Statue
		
		Statue* devil = new Statue("devil", "statue devil");
		listOfStatues.push_back(devil);
		Statue* angel = new Statue("angel", "statue representing the angel");
		listOfStatues.push_back(angel);
		Statue* blind = new Statue("blind", "statue representing the blind");
		listOfStatues.push_back(blind);
		Statue* kid = new Statue("kid", "statue representing the kid");
		listOfStatues.push_back(kid);
	}

	void Adventure::goOtherRoom(Player* user)
	{
		cout << "Which Direction Should i Go" << endl;
		cin >> userInput;
		transform(userInput.begin(), userInput.end(), userInput.begin(), ::toupper);
		
		listRooms.at(user->getCurrentLocation())->getValueDirection(user, userInput);
		Sleep(2000);     /// <= time is good for pause the system
	}

	void Adventure::guiStatistics(Player *user) {
		setcolor(dark_yellow, white);

		cout << "================================================================================" << endl;
		cout << "Name : " << user->getName() << "  |==|==|==|==|==| " << "Hp " << user->getHp() << "/100" << " |Player Score| : " <<user->getScore() << endl;
		cout << "|| Location :" << "|| " << listRooms.at(user->getCurrentLocation())->getRoomName() << " ||" << endl;
		cout << "================================================================================" << endl;
		cout << "currentplayer room number " << user->getCurrentLocation() + 1 << " Steps : " << user->getSteps() << endl;
		cout << "================================================================================" << endl;
		setcolor(red, white);
	}

	void Adventure::lookForItems(Player *user)
	{
		
		listRooms.at(user->getCurrentLocation())->getRoomDescription();
		Sleep(1500);
		
	}

	void Adventure::guiDescription(Player *user) {
		setcolor(dark_blue, white);
		cout << "================================================================================" << endl;
		listRooms.at(user->getCurrentLocation())->getRoomDescription();
		cout << "================================================================================" << endl;
		setcolor(red, white);
	}

	void Adventure::takeItem()
	{
		lookForItems(user);
		if (listRooms.at(user->getCurrentLocation())->getNumberItemsInRoom() > 0)
		{
			listRooms.at(user->getCurrentLocation())->getObjectInRoom();
			cout << "What I should Take??" << endl;
			cin >> userInput;
			transform(userInput.begin(), userInput.end(), userInput.begin(), ::toupper);
			listRooms.at(user->getCurrentLocation())->takeItemFromRoom(userInput, user);
			Sleep(1500);
		}
		
	}

	void Adventure::checkInventory()
	{
		int actualRoom = user->getCurrentLocation() + 1;
		if (actualRoom == 1)
		{
			tempContainerList = listOfDoorsRoom1;
		}
		else if (actualRoom == 2)
		{
			tempContainerList = listOfDoorsRoom2;
		}
		else if (actualRoom == 3)
		{
			tempContainerList = listOfDoorsRoom3;
		}
		else if (actualRoom == 4)
		{
			tempContainerList = listOfDoorsRoom4;
		}
		else
		{
			tempContainerList = listOfDoorsRoom5;
		}

		int numberItem;
		int indexDoorPosition;
		vector<Object*> currentInventory = user->getItemsInInventory();
		cout << "|=================== INVENTORY ===================" << endl;
		cout << " " << endl;
		user->getInventory();       //// <- up to here works
		Sleep(1500);
		if (currentInventory.size() > 0)
		{
			cout << " " << endl;
			cout << "What i can do now " << endl;
			cout << "|  use |" << endl;
			cout << "| examine | " << endl;
			cin >> userInput;
			transform(userInput.begin(), userInput.end(), userInput.begin(), ::toupper);
			if (userInput == "USE")          //// <=== for now only use works
			{
				numberItem = 0;
				do
				{
					cout << "Enter of number of the item to use " << endl;
					cin >> numberItem;
				} while (numberItem < 0 || numberItem > currentInventory.size());

				if (currentInventory.at(numberItem - 1)->getObjectName() == "steel key")
				{
					int numbeerDoors = 0;
					for (int i = 0; i < tempContainerList.size(); i++)
					{
						numbeerDoors++;
						cout << "Door N: " << " " << i + 1 << " " << tempContainerList.at(i)->getObjectName() << endl;
					}

					do
					{
						cout << "Enter which door to use" << endl;
						cin >> indexDoorPosition;
						while (!cin)
						{
							cout << "That was not a valid value! ";
							cin.clear();
							cin.ignore();
							cout << " " << endl;
							cin >> indexDoorPosition;
						}
						
					} while (indexDoorPosition <= 0 || indexDoorPosition > tempContainerList.size());

					currentInventory.at(numberItem - 1)->useWith(listDirectionInMotionTablet.at(user->getCurrentLocation())->getDoor(indexDoorPosition - 1));
				}
				else if (currentInventory.at(numberItem - 1)->getObjectName() == "gold key")
				{
					int numbeerDoors = 0;
					for (int i = 0; i < tempContainerList.size(); i++)
					{
						numbeerDoors++;
						cout << "Door N " << i + 1 << tempContainerList.at(i)->getObjectName() << endl;
					}

					do
					{
						cout << "Enter wich door to use" << endl;
						cin >> indexDoorPosition;
						while (!cin)
						{

							cout << "That was not a valid value!";
							cin.clear();
							cin.ignore();
							cout << " " << endl;
							cin >> indexDoorPosition;
						}
					
					} while (indexDoorPosition <= 0 || indexDoorPosition > tempContainerList.size());

					currentInventory.at(numberItem - 1)->useWith(listDirectionInMotionTablet.at(user->getCurrentLocation())->getDoor(indexDoorPosition - 1));
				}
				else if(currentInventory.at(numberItem - 1)->getObjectName() == "CROWBAR")
				{
					for (int i = 0; i < tempContainerList.size(); i++)
					{
						
						cout << "Door N " << i + 1 << tempContainerList.at(i)->getObjectName() << endl;
					}

					do
					{
						cout << "Enter which door to use" << endl;
						cin >> indexDoorPosition;
						while (!cin)
						{

							cout << "That was not a valid value!";
							cin.clear();
							cin.ignore();
							cout << " " << endl;
							cin >> indexDoorPosition;
						}
					} while (indexDoorPosition <= 0 || indexDoorPosition > tempContainerList.size());

					currentInventory.at(numberItem - 1)->useWith(listDirectionInMotionTablet.at(user->getCurrentLocation())->getDoor(indexDoorPosition - 1));
				}
				else
				{
					cout << "i have no useful item at the moment " << endl;
				}
				Sleep(2500);
				
			}
			if (userInput == "EXAMINE")
			{
				numberItem = 0;
				do
				{
					cout << "Enter number of the item to examine " << endl;
					cin >> numberItem;
					while (!cin)
					{

						cout << "That was not a valid value!";
						cin.clear();
						cin.ignore();
						cout << " " << endl;
						cin >> indexDoorPosition;
					}
					
				} while (numberItem <= 0 || numberItem > currentInventory.size());
				
				currentInventory.at(numberItem - 1)->examine();
				Sleep(2500);
			}
		}

	}
		
	void Adventure::help()
	{
		cout << "==============================================================================" << endl;
		cout << " Enter | Move | to allow the player to decide wich direction to move, if is possible " << endl;
		cout << "==============================================================================" << endl;
		cout << " Enter | Take | and enter the name of the object thus wish to take" << endl;
		cout << "==============================================================================" << endl;
		cout << " Enter | Look | to look around the room for hints " << endl;
		cout << "==============================================================================" << endl;
		cout << " Enter | Inventory | to look at own inventory " << endl;
		cout << "==============================================================================" << endl;
		cout << " Enter | Drop | to drop an item from the Inventory " << endl;
		cout << "==============================================================================" << endl;
		cout << " Enter | Examine | to examine the place and see if there is something to interact with " << endl;
		cout << "==============================================================================" << endl;
		cout << " Enter | Quit | to leave the game " << endl;
		cout << "==============================================================================" << endl;
	}
	void Adventure::examineRoom()
	{
		int actualRoom = user->getCurrentLocation() + 1;
		cout << " what you want to examine in the room " << endl;
		cin >> userInput;
		transform(userInput.begin(), userInput.end(), userInput.begin(), ::toupper);
		int indexPosition = 0;
		if (actualRoom == 1)
		{
			tempContainerList = listOfDoorsRoom1;
		}
		else if (actualRoom == 2)
		{
			tempContainerList = listOfDoorsRoom2;
		}
		else if (actualRoom == 3)
		{
			tempContainerList = listOfDoorsRoom3;
		}
		else if (actualRoom == 4)
		{
			tempContainerList = listOfDoorsRoom4;
		}
		else
		{
			tempContainerList = listOfDoorsRoom5;
		}
		if (userInput == "DOORS")
		{
			for (int i = 0; i < tempContainerList.size(); i++)
			{
				
				cout << "Door N " << " " << i + 1 << tempContainerList.at(i)->getObjectName() << endl;
				cout << " " << endl;
			}

			do
			{
				cout << "Enter number of door to examine" << endl;
				cin >> indexPosition;
				while (!cin)
				{

					cout << "That was not a valid value!";
					cin.clear();
					cin.ignore();
					cout << " " << endl;
					cin >> indexPosition;;
				}
				
			} while (indexPosition <= 0 || indexPosition > tempContainerList.size());

			listDirectionInMotionTablet.at(user->getCurrentLocation())->getDoor(indexPosition - 1)->examine();
			Sleep(1500);
			if (listDirectionInMotionTablet.at(user->getCurrentLocation())->getDoor(indexPosition - 1)->getObjectName() == "glass door")
			{
				cout << "you wanna try destroy the small window??  " << endl;
				cin >> userInput;
				transform(userInput.begin(), userInput.end(), userInput.begin(), ::toupper);
				if (userInput == "YES")
				{
					int userHP = user->getHp() - 20;
					user->setHp(userHP);
					int usernewScore = user->getScore() - 50;
					user->setScore(usernewScore);
					cout << "you cut yourself, trying to destroy the door bare hands" << endl;
					Sleep(1500);
				}
			}
		}
		else if (user->getCurrentLocation() + 1 == 1 && userInput == "STATUES")
		{
			for (int i = 0; i < listOfStatues.size(); i++)
			{

				cout << "Statue N " << i + 1 << " " << listOfStatues.at(i)->getObjectName() << endl;
				cout << " " << endl;
			}

			do
			{
				cout << "Enter number of statue you want examine" << endl;
				cin >> indexPosition;
				while (!cin)
				{

					cout << "That was not a valid value!";
					cin.clear();
					cin.ignore();
					cout << " " << endl;
					cin >> indexPosition;;
				}
			} while (indexPosition <= 0 || indexPosition > listOfStatues.size());
			listOfStatues.at(indexPosition - 1)->examine();
			listOfStatues.at(indexPosition - 1)->pushButton(user);
		}
		else if (user->getCurrentLocation() + 1 == 4 && userInput == "SAFE")
		{
			safeBox->examine();
			safeOpened = safeBox->open();
			if (safeOpened == true && itemReceiveFromSafe == false)
			{
				Key* goldenKey = new Key("gold key", "key with a sun on it");
				user->setItemInInventory(goldenKey);
				itemReceiveFromSafe = true;
				cout << " i just found a key inside the safe. i gonna store in the inventory " << endl;
				Sleep(1500);
				cout << " i can see a botton on the buttom of the safe " << endl;
			}
			if (safeOpened == true && itemReceiveFromSafe == true)
			{
				
				do
				{
					cout << "wanna press it" << endl;
					cin >> userInput;
					transform(userInput.begin(), userInput.end(), userInput.begin(), ::toupper);
				} while (userInput != "YES" && userInput != "NO");

				if(userInput == "YES")
				{
					safeButtonPressed();
				}

			}

		}
		else if (user->getCurrentLocation() + 1 == 5 && userInput == "FLOOR")
		{
			cout << "on the floor there are some marks areund a squared area. like something has move that area " << endl;
			Sleep(1000);
			if (user->getCrowBarStatus() == true)
			{
				cout << " what you wanna use" << endl;
				cin >> userInput;
				transform(userInput.begin(), userInput.end(), userInput.begin(), ::toupper);
				if (userInput == "CROWBAR")
				{
					cout << "the crowbar does fit perfeclty at the edges of the area " << endl;
					cout << "THE ARE HAS BEEN LIFTED " << endl;
					cout << " i Just found a new door under the floor" << endl;
					listDirectionInMotionTablet.at(user->getCurrentLocation())->setEXITS("IN 6");
					cout << " " << endl;
					listDirectionInMotionTablet.at(user->getCurrentLocation())->getDirection();
					Door* finalDoor = new Door(false, "door made in metal", "metal door");
					listOfDoorsRoom5.push_back(finalDoor);
					listDirectionInMotionTablet.at(user->getCurrentLocation())->setDoor(finalDoor);
					Sleep(2500);

				}
			}
			
		}

		else
		{
			cout << " i don't understand " << endl;
			Sleep(2000);
		}
	}

	void Adventure::safeButtonPressed()
	{
		if (listDirectionInMotionTablet.at(1)->checkForDirection("FORCED") == true)
		{
			
			listDirectionInMotionTablet.at(1)->editExit("WEST 1", "FORCED");
			cout << "i just heard a stange noise coming from the other room " << endl;
			Sleep(2000);
			loadNewDescriptions();
			
		}
		listRooms.at(1)->setRoomDescription(newDesciptionRoom);
		
	}

	void Adventure::loadNewDescriptions()
	{
		string line1 = "The gas that escaped did clear, now i can safely examine this room";
		newDesciptionRoom.push_back(line1);
		string line2 = "at the centre of the room i see table with some food";
		newDesciptionRoom.push_back(line2);
	}

	void Adventure::dropObject()
	{
		vector<Object*> currentInventory = user->getItemsInInventory();
		if (currentInventory.size() > 0)
		{
			cout << "insert item you want to drop: " << endl;
			cin >> userInput;
			if (user->controlInventoryForItem(userInput) == true)
			{
				Object* objectDropped = user->removeItemfromInventory();
				listRooms.at(user->getCurrentLocation())->setObjectInRoom(objectDropped);
			}
		}
		else
		{
			cout << "There is nothing to drop " << endl;
		}
		Sleep(2000);
		
	}
