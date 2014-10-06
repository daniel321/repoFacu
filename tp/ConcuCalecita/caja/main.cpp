#include "Caja.h" 	// caja
#include <stdlib.h>	// atoi
#include <iostream>

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
		std::cout << e.what() << std::endl;
	}
}



















