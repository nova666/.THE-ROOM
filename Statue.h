#pragma once
#ifndef STATUE_H
#define STATUE_H
#include "Object.h"
#include <iostream>
#include <string>
#include "Player.h"

class Statue : public Object {

	bool choiceMade;
	string name;
	string userChoice;
	int choice = 0;
	string description;
	bool activate = false;
	bool rightChoice = false;
	int newHP = 0;
	Object* keyfromStatue;

	public:
		Statue(string name, string description);

		void examine();
		bool open();
		string useWith(Object*  otherObjectToInteractWith);
		void pushButton(Player* user);
};
#endif // !STATUE_H
