#include "Caja.h" 	// caja
#include <stdlib.h>	// atoi

int main (int argc, char** argv) {
	int dinero = 0;
	if(argc > 1)
		dinero = atoi(argv[0]);

	Caja caja(dinero);
	caja.esperarModificaciones();

	return 0;
}



















