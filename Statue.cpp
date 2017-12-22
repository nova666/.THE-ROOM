#include "Statue.h"
#include <iostream>

using namespace std;

	Statue::Statue(string name, string description):Object(name, description)
	{
		
	}

	void Statue::examine()
	{
		if (getObjectName() == "devil")
		{
			cout << "-- I have the key, but do you belive me remember im the devil --" << endl;
			cout << " I see the number 9 on his head" << endl;
			cout << " " << endl;
			cout << "There is a button on the chest of the statue" << endl;


		}
		else if(getObjectName() == "angel")
		{
			cout << " -- The devil don't have the key, but i do have the key --" << endl;
			cout << " I see the number 0 on his head" << endl;
			cout << " " << endl;
			cout << "There is a Button on the chest of the statue" << endl;
		}
		else if (getObjectName() == "blind")
		{
			cout << " -- I don't know if i have the key, im blind -- " << endl;
			cout << " I see the number 3 on his head" << endl;
			cout << " " << endl;
			cout << "There is a Button on the chest of the statue" << endl;
			
		}
		else
		{
			cout << " -- I do have the key --" << endl;
			cout << " I see the number 1 on his head" << endl;
			cout << " " << endl;
			cout << "There is a Button on the chest of the statue" << endl;
		}
	}

	void Statue::pushButton(Player* user)
	{
		if (getObjectName() == "devil")
		{
			do
			{
				cout << " You want to activate the button on the chest of the statue?" << endl;
				cin >> userChoice;
			} while (userChoice != "yes" && userChoice != "no");
			
			if (userChoice == "yes")
			{
				activate = false;
				rightChoice = true;
			}
			
		}
		else if (getObjectName() == "devil")
		{
			do
			{
				cout << " You want to activate the button on the chest of the statue?" << endl;
				cin >> userChoice;
			} while (userChoice != "yes" && userChoice != "no");

			if (userChoice == "yes")
			{
				activate = true;
			}
			
		}
		else if (getObjectName() == "blind")
		{
			do
			{
				cout << " You want to activate the button on the chest of the statue?" << endl;
				cin >> userChoice;
			} while (userChoice != "yes" && userChoice != "no");

			if (userChoice == "yes")
			{
				activate = true;
			}
			
		}
		else
		{
			do
			{
				cout << " You want to activate the button on the chest of the statue?" << endl;
				cin >> userChoice;
			} while (userChoice != "yes" && userChoice != "no");

			if (userChoice == "yes")
			{
				activate = true;
			}
			
		}

		if (activate == true)
		{
			newHP = user->getHp() - 30;
			user->setHp(newHP);
			cout << "A knife has been shot from the mouth of the statue, you been hit " << endl;
			int newscore = user->getScore() - 50;
			user->setScore(newscore);
			Sleep(1250);
		}
		if (activate == false && rightChoice == true)
		{
			cout << "A key droped from the statue mouth, i took the key" << endl;
			keyfromStatue = new Key("steel key", "Key received from the statue");
			user->setItemInInventory(keyfromStatue);
			Sleep(2000);
		}

	}

	bool Statue::open()
	{
		return false;
	}

	string Statue::useWith(Object*  otherObjectToInteractWith)
	{
		return string(" statue cannot be used with anything ");
	}


