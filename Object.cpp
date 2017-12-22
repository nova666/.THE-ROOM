#include "Object.h"
#include <iostream>


Object::Object(string objectName)
{
	this->objectName = objectName;
}

string Object::getObjectDescription()
{
	return objectName;
}
virtual Object::~Object()
{
}
