#include "vendedor.h" 	// Vendedor

int main (int argc, char** argv)
{
	try
	{
		Vendedor vendedor;
		vendedor.atenderClientes();
		return 0;
	}
	catch (std::exception &e)
	{
		std::cout << "Vendedor " << ::getpid() << " : " << e.what() << std::endl;
	}
}



















