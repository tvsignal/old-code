#include <iostream.h>

void main()
{
	for (int counter = 0; counter < 5; counter++)
	{
		cout << counter << endl;
	}

	//cout << counter << endl;

	int test;
	cout << "Skriv eit tal mellom 1 og 9: ";
	cin >> test;

	switch(test)
	{
		case 1: cout << "Ein, ja." << endl; break;
		default: cout << "Default." << endl; break;
		case 2: cout << "To, ja." << endl; break;
	}
	


}