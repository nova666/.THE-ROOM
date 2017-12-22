#ifndef KEY_H
#define KEY_H
#include <iostream>
#include "Object.h"
#include "Door.h"
using namespace std;

class Key :public Object {

public:
	Key(string name, string description);
	//~Key();

	void examine();
	bool open();
	string useWith(Object* otherObjectToInteractWith);
		
};


#endif // !KEY_H

