#include <iostream.h>

void kvadrat(int&, int&);
void kube(int&, int&);
void bytt(int&, int&);
void endreVerdiar(int&, int&);

typedef void (* VPF)(int&, int&);
void printVerdiar(VPF, int&, int&);

enum BOOL {FALSE, TRUE };

class Dog{
public:
	void Bark(){cout << "Woof!\n"; }
};

class Cat{};

void main()
{
	BOOL slutt = FALSE;
	int x = 2;
	int y = 3;

	const lengde = 4;

	VPF pFuncArray[lengde];
		
	for(int i = 0; i < lengde; i++)
	{
		cout << "(1)Kvadrer, (2)Opphoey i tredje, "
			<< "(3)Bytt om verdiar, (4)Endre verdiar: ";
		int valg;
		cin >> valg;

		switch(valg)
		{
		case 1: pFuncArray[i] = kvadrat; break;
		case 2: pFuncArray[i] = kube; break;
		case 3: pFuncArray[i] = bytt; break;
		case 4: pFuncArray[i] = endreVerdiar; break;
		default: i--; break;
		}
	}

	for(i = 0; i < lengde; i++)
	{
		printVerdiar(pFuncArray[i],x,y);
	}
}

void kvadrat(int & x, int & y)
{
	cout << "Kvadrerer...\n";
	x *= x;
	y *= y;
}
void kube(int & x, int & y)
{
	cout << "Opphoyer i 3. potens...\n";
	int temp = x;
	x *= x;
	x *= temp;
	
	temp = y;
	y *= y;
	y *= temp;
}
void bytt(int & x,int & y)
{
	cout << "Bytter om på tala...\n";
	int temp = x;
	x = y;
	y = temp;
}
void endreVerdiar(int & x, int & y)
{
	cout << "Ny verdi for x: ";
	cin >> x; 
	cout << "Ny verdi for y: ";
	cin >> y; 
}

void printVerdiar(VPF vpf, int & x, int & y)
{
	cout << "x: " << x << ", y: " << y << endl;
	vpf(x,y);
	cout << "x: " << x << ", y: " << y << endl;

}










