#ifndef SAFE_H
#define SAFE_H
#include "Object.h"
#include <iostream>

using namespace std;


class Safe : public Object {


	int securityNumber;
	bool safeDoorState = false;
	string userChoice;
	int digits1ForSafe = 0;
	int digits2ForSafe = 0;
	int digits3ForSafe = 0;
	int digits4ForSafe = 0;
	public:
	Safe(string name, string description);

	void examine();
	bool open();
	string useWith(Object*  otherObjectToInteractWith);



};
#endif // !SAFE_H

