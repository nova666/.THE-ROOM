#pragma once
#include "Object.h"
#include "Door.h"
#include <iostream>
using namespace std;

class CrowBar :public Object{

public:

	CrowBar(string name, string description);
	void examine();
	bool open();
	string useWith(Object* otherObjectToInteractWith);
	bool useCrowBar(string target);

	
};

