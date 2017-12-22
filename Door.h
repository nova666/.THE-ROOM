#ifndef DOOR_H
#define DOOR_H
#include <iostream>
#include "Object.h"
using namespace std;

class Door:public Object {

	bool openState;

public:
	Door(bool open_close, string description, string nameDoor);
	bool getDoorState();

	void examine();
	bool open();
	void setDoorOpen();
	string useWith(Object* otherObjectToInteractWith);


};
#endif // !DOOR_H

