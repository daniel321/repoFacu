#include "calesita.h" 	// Calecita
#include <cstdlib> // Atoi

/**
 * Argumentos
 * 1 : Cantidad de asientos
 * 2 : Duración de la vuelta, en segundos
 */
#include <iostream>
#include "../common/Asientos.h"
int main (int argc, char** argv)
{
	int numeroAsientos = 5;
	int tiempoVuelta = 3;
	if(argc > 1) numeroAsientos = atoi(argv[1]);
	if(argc > 2) tiempoVuelta = atoi(argv[2]);
	try
	{
		Calesita calesita(numeroAsientos, tiempoVuelta);
		calesita.operar();
		return 0;
	}
	catch (std::exception &e)
	{
		std::cout << "Calesita " << ::getpid() << " : " << e.what() << std::endl;
	}
}



















