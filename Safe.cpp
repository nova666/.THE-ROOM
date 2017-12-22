#include "Safe.h"
#include <iostream>
#include <string>

Safe::Safe(string name, string description):Object(name,description)
{
	
}

void Safe::examine()
{
	cout << " this is a safe, i wonder what contains " << endl;

}

bool Safe::open()
{
	if (safeDoorState == false)
	{
		do
		{
			cout << " you want to open the safe " << endl;
			cin >> userChoice;
		} while (userChoice != "yes" && userChoice != "no");
		
		if (userChoice == "yes")
		{
			cout << "Insert The combination of digit for the safe " << endl;
			cout << " " << endl;
			cout << " " << endl;
			do
			{
				cout << "Insert Digit 1" << endl;
				cout << " " << endl;
				cin >> digits1ForSafe;
			} while (digits1ForSafe < 0 || digits1ForSafe > 9);
			cout << " " << endl;
			do
			{
				cout << "Insert Digit 2" << endl;
				cout << " " << endl;
				cin >> digits2ForSafe;
			} while (digits2ForSafe < 0 || digits2ForSafe > 9);
			cout << " " << endl;
			do
			{
				cout << "Insert Digit 3" << endl;
				cout << " " << endl;
				cin >> digits3ForSafe;
			} while (digits3ForSafe < 0 || digits3ForSafe > 9);
			cout << " " << endl;
			do
			{
				cout << "Insert Digit 4" << endl;
				cout << " " << endl;
				cin >> digits4ForSafe;
			} while (digits4ForSafe < 0 || digits4ForSafe > 9);
			
			if (digits1ForSafe == 9 && digits2ForSafe == 0 && digits3ForSafe == 3 && digits4ForSafe == 1)
			{
				cout << "Safe opened " << endl;
				return true;
				safeDoorState = true;
			}

			else
			{
				cout << " Access Denied" << endl;
			}
		}
		return false;
	}
	return true;
}


string Safe::useWith(Object*  otherObjectToInteractWith)
{
	return string("safe can't be used with anything");
}