#include "calesita.h" 	// Calecita
#include <cstdlib> // Atoi

/**
 * Argumentos
 * 1 : Cantidad de asientos (entero > 0)
 * 2 : Duración de la vuelta, en segundos
 */
int main (int argc, char** argv)
{
	if(argc > 1) Calesita::NumeroAsiendos = atoi(argv[1]);
	if(argc > 2) Calesita::TiempoDeVuelta = atoi(argv[2]);
	try
	{
		Calesita calesita;
		calesita.operar();
		return 0;
	}
	catch (std::exception &e)
	{
		std::cout << "Calesita " << ::getpid() << " : " << e.what() << std::endl;
	}
}



















