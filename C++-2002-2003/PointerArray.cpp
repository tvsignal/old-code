//Listing 11.6 An array of pointers to objects

#include <iostream.h>

class Cat
{
public:
	Cat() { itsAge = 1; itsWeight = 5; }	//default constructor
	~Cat() { cout << "Destructor!\n"; }	 							//destructor
	int getAge() const { return itsAge; }
	int getWeight() const { return itsWeight; }
	void setAge(int age) { itsAge = age; }

private:
	int itsAge;
	int itsWeight;

};

void main()
{
	Cat * family = new Cat[5];
	int i;
	Cat * pCat;

	for(i=0; i < 5; i++)
	{
		pCat = new Cat;
		pCat->setAge(2*i+1);
		family[i] = *pCat;
		delete pCat;
	}

	for (i=0; i < 5; i++)
		cout << "Cat #" << i+1 << ": " << family[i].getAge() << endl;
	
	cout << family->getAge() << endl; //family[0] sin alder
	family++;
	cout << family->getAge() << endl; //family[1] sin alder
	family--;
	
	delete [] family;

}


