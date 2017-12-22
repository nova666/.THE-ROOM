#pragma once
#include <iostream>
#include <Windows.h>

using namespace std;

class Object
{
	
	string objectName;
	string description;
	public:
	//virtual ~Object();
	Object(string itemName, string descriptionItem)
	{
		this->objectName = itemName;
		this->description = descriptionItem;
	}
	string getObjectDescription()
	{
		return description;
	}
	string getObjectName()
	{
		return objectName;
	}
	virtual void examine() = 0;
	virtual bool open() = 0;
	virtual string useWith(Object*  otherObjectToInteractWith) = 0;


};

