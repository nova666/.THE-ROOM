#include "Key.h"

using namespace std;

Key::Key(string name, string description):Object(name,description)
{

}

void Key::examine()
{
	
	 if (getObjectName() == "steel key")
	{
		cout << "This is a normal key" << endl;
		
	}
	else if (getObjectName() == "red emblem")
	{
		
		cout << "This is a key with a red symbol on it/n the symbol represents a flame crest" << endl;
	}
	else if(getObjectName() == "gold key")
	{
		cout << "key with a sun on it" << endl;
	}
	else if (getObjectName() == "CROWBAR")
	{
		cout << " a crowbar made in metal useful to lift things" << endl;
	}
	
}

bool Key::open()
{
	cout << " Nothing happens " << endl;
	return false;
}

string Key::useWith(Object* otherObjectToInteractWith)
{
	
	Door* door = dynamic_cast<Door*>(otherObjectToInteractWith);

	if (door->getDoorState() == true)
	{
		cout << " door already open" << endl;
	}
	else if (getObjectName() == "steel key" && door->getObjectName() == "door")
	{
		door->setDoorOpen();  /// main problem here is that the parameter is an instance of door but is received as Object
		cout << "door opened " << endl;
	}
	else if (getObjectName() == "red emblem" && door->getObjectName() == "flamesymbol door")
	{
		door->setDoorOpen();  /// main problem here is that the parameter is an instance of door but is received as Object
		cout << "door opened " << endl;
	}
	else if (getObjectName() == "steel key" && door->getObjectName() == "glass door")
	{
		door->setDoorOpen();  /// main problem here is that the parameter is an instance of door but is received as Object
		cout << "door opened " << endl;
	}
	else if (getObjectName() == "gold key" && door->getObjectName() == "metal door")
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
