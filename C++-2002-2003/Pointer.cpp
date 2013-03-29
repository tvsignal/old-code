typedef unsigned short int USHORT;
#include <iostream.h>

void gangMedTo(int * pointer);
void gangMedTo(int tal);

void gangMedTo(int * pointer)
{
	*pointer = *pointer * 2;
}

void gangMedTo(int tal)
{
	tal = tal * 2;
}

void main()
{
	USHORT * pInt = new USHORT;
	cout << "*pInt: " << *pInt << endl;
	
	cout << "*pInt = 10;"<<endl;
	*pInt = 10;

	cout << "*pInt: " << *pInt << endl;
	delete pInt;
	pInt = 0;

	long * pLong = new long;
	*pLong = 90000;
	cout << "*pLong: " << *pLong << endl;

	pInt = new USHORT(20);	

	cout << "*pInt: " << *pInt << endl;
	cout << "*pLong: " << *pLong << endl;
	delete pLong;

	int*pTal = new int(3);
	cout << endl << "*pTal: " << *pTal << endl;
	cout << "gangMedTo(pTal);..." << endl;
	gangMedTo(pTal);
	cout << "*pTal: " << *pTal << endl;
	
	int tal = 3;
	cout << endl << "tal: " << tal << endl;
	cout << "gangMedTo(tal);..." << endl;
	gangMedTo(tal);
	cout << "tal: " << tal << endl;
	

}