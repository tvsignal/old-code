#include <iostream.h>

#define DEBUG
#define OG(x,y) cout << #x << " og " << #y << endl;
#define SPM(x) spm ## x

#ifndef DEBUG
	#define ASSERT(x,l)
#else
	#define ASSERT(x,l) \
			if(!(x)) \
			{ \
				cout << "Feil!! Assert(" << #x << ", " << l << ")" \
				<< " feila\n" \
				<< "i fila Preprocessor.cpp.\n"; \
			}
#endif

void main()
{
	char * spmTo;
	int x = 5;
	cout << "Foerste assert: \n";
	ASSERT(x==5,1);
	cout << "Andre assert: \n";
	ASSERT(x!=5,2);

	OG(du, jeg);

	SPM(To) = "Hvem spilte gudfaren i 'Gudfaren'?";
	cout << SPM(To) << endl;
}