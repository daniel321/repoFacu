#include "client.h" 	// Cliente
#include <stdlib.h>	// atoi

#include "../common/exception/ErrnoWrap.h"
/**
 * Arguemtnos esperados:
 * 1 - Dinero
 * 2 - Si ya tiene boleto
 */
int main (int argc, char** argv)
{
	try
	{
		int presupuesto = 0;
		if(argc > 1)
			presupuesto = atoi(argv[1]);

		bool tieneBoleto = false;
		if(argc > 2)
			tieneBoleto = (atoi(argv[2]) != 0);
	
		Cliente cliente(presupuesto,tieneBoleto);
		cliente.comprarBoleto();
		cliente.subirseALaCalesita();

		return 0;
	}
	catch (std::exception &e)
	{
		std::cout << "Cliente " << ::getpid() << " : " << e.what() << std::endl;
	}
}












