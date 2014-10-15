#include "Caja.h" 	// caja
#include <stdlib.h>	// atoi
#include <iostream>

/**
 * Argumento: Dinero inicial de la caja
 */
int main (int argc, char** argv)
{
	try
	{
		int dinero = 0;
		if(argc > 1)
			dinero = atoi(argv[0]);

		Caja caja(dinero);
		caja.esperarModificaciones();

		return 0;
	}
	catch (std::exception &e)
	{
		std::cout << "Caja " << ::getpid() << " : " << e.what() << std::endl;
	}
}



















