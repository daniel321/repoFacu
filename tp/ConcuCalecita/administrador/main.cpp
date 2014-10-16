#include "admin.h" 	// Administrador

#include <iostream>

int main (int argc, char** argv)
{
	try
	{
		Administrador admin;
		admin.consultarCaja();
		return 0;
	}
	catch (std::exception &e)
	{
		std::cout << "Administrador " << ::getpid() << " : " << e.what() << std::endl;
	}
}



















