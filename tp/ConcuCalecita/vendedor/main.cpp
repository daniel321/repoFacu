#include "vendedor.h"
#include <stdlib.h>	// atoi

int main (int argc, char** argv)
{
	try
	{
		int precioBoleto = 40;
		if(argc > 1) precioBoleto = atoi(argv[1]);

		Vendedor vendedor(precioBoleto);
		vendedor.atenderClientes();
		return 0;
	}
	catch (std::exception &e)
	{
		std::cout << "Vendedor " << ::getpid() << " : " << e.what() << std::endl;
	}
}



















