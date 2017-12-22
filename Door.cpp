#include "Door.h"

Door::Door(bool open_close, string description, string nameDoor) :Object(nameDoor, description)
{
	this->openState = open_close;
}
bool Door::getDoorState()
{
	return open();
}
void Door::examine()
{
	if (getObjectName() == "glass door")
	{
		cout << "This door has a glass window on top doesn't look too hard to destroy it " << endl;
	}
	else if (getObjectName() == "metal door")
	{
		cout << " This door is made in metal, looks impossible to force, \n in the middle of the door there is symbol looks like a sun,  " << endl;
	}
	else
	{
		cout << " normal door made in wood " << endl;
	}
}

bool Door::open()
{
	return openState;
}


 string Door::useWith(Object*  otherObjectToInteractWith)
{
	return string("is a door i can't use it with anything");
}



void Door::setDoorOpen()
{
	openState = true;
}

