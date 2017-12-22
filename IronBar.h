#ifndef IRONBAR_H
#define IRONBAR_H
#include <iostream>
#include "Object.h"
using namespace std;

class IronBar :public Object {


public:
	IronBar(string name, string description);
	void examine();
	bool open();
	string useWith(Object* otherObjectToInteractWith);

};


#endif // !IRONBAR_H

