#include "admin.h" 	// Administrador

#include <iostream>
#include <cstdlib>

int main (int argc, char** argv)
{
	try
	{
		srand(getpid());
		Administrador admin;
		while (true)
		{
			admin.consultarCaja();
			sleep(1+rand()%10);
		}
		return 0;
	}
	catch (std::exception &e)
	{
		std::cout << "Administrador " << ::getpid() << " : " << e.what() << std::endl;
	}
}



















