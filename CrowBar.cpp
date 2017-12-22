#include "CrowBar.h"


CrowBar::CrowBar(string name, string description):Object(name,description)
{
}

void CrowBar::examine()
{
	cout << " a new metal crowbar, looks has been used recently " << endl;

}

bool CrowBar::open()
{
	cout << " Nothing happens " << endl;
	return false;
}

string CrowBar::useWith(Object* otherObjectToInteractWith)
{

	Door* door = dynamic_cast<Door*>(otherObjectToInteractWith);

	if (door->getDoorState() == true)
	{
		cout << " door already open" << endl;
	}
	else if (door->getObjectName() == "door" || door->getObjectName() == "glass door" && door->getDoorState() == false)
	{
		door->setDoorOpen();  /// main problem here is that the parameter is an instance of door but is received as Object
		cout << "door opened " << endl;
	}
	else
	{
		cout << " key doesn't work here" << endl;
	}
	return string("opened");

}

bool CrowBar::useCrowBar(string target)
{
	bool exitFound = false;
	if (target == "floor")
	{
		cout << " using the crwowBar On the Floor i found an a tunnel  " << endl;
		cout << " i wonder if it will get me outof here " << endl;
		exitFound = true;
	}

	return exitFound;
}


