#include <iostream.h>
	
enum TYPE {SALT, FERSK};

class Fisk
{
private:
	TYPE type;
public:
	TYPE hentType(){return type;}
	void settType(TYPE sort)
	{
		cout << "Setter type...\n";
		type = sort;		
	}

	Fisk();
	Fisk(TYPE sort);
	Fisk(Fisk&);
	~Fisk();
};
	
	Fisk::Fisk()
	{
		type = SALT;
		cout << "Fiskekonstruktor\n";
	}

	Fisk::Fisk(TYPE sort)
	{
		type = sort;
		cout << "Fiskekonstruktor\n";
	}

	Fisk::~Fisk()
	{
		cout << "Fiskedestruktor\n";
	}

	Fisk::Fisk(Fisk&)
	{
		cout << "Fisk sin kopikonstruktor\n";
	}

void bytt(int& tal1, int& tal2);
Fisk dummy(Fisk fisken);
Fisk& lagFisk(Fisk &rEnFisk);

void main()
{
	int a = 3;
	int b = 4;
	cout << "a: " << a << " b: " << b << endl;
	cout << "bytt(a,b)..." << endl;
	bytt(a,b);
	cout << "a: " << a << " b: " << b << endl;
	

	Fisk abbor(SALT);
	dummy(abbor);

	Fisk* pAbbor = &abbor;
	Fisk& rAbbor = abbor;

	cout << "\npAbbor\trAbbor\n";
	cout << pAbbor->hentType() << "\t" << rAbbor.hentType() << endl;

	pAbbor->settType(FERSK);
	cout << pAbbor->hentType() << "\t" << rAbbor.hentType() << endl;

	rAbbor.settType(SALT);
	cout << pAbbor->hentType() << "\t" << rAbbor.hentType() << endl;

	Fisk &enFisk = lagFisk();

	cout << "Deklarerer ein fisk...\n";
	Fisk enFisk;

	cout << "Initialiserer ein fisk vha lagFisk()...\n";
	enFisk = lagFisk(enFisk);
	cout << "enFisk sin type: ";
	
	switch(enFisk.hentType()){
		case 0:
			cout << "SALT\n";break;
		case 1:
			cout << "FERSK\n";break;
		default:
			cout << "Illegal type.\n";break;
	}
	
	cout << "Main er ferdig. enFisk likeså.\n";

}

void bytt(int& tal1, int& tal2)
{	
	int temp = tal1;
	tal1 = tal2;
	tal2 = temp;
}

Fisk dummy(Fisk fisken)
{
	return fisken;	
}

Fisk& lagFisk(Fisk &rEnFisk)
{
	cout << "I lagFisk(Fisk &rEnFisk). Oppretter ein pointer pFisk "
		<< "til eit objekt på heap'en.\n";
	Fisk *pFisk = new Fisk(FERSK);
	cout << "Lar rEnFisk referere til pFisk sin verdi.\n";
	rEnFisk = *pFisk;
	cout << "Returnerer rEnFisk som referanse.\n";
	return rEnFisk;
}