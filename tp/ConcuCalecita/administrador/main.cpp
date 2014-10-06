#include "admin.h" 	// Administrador

#include <iostream>

int main (int argc, char** argv)
{
	try
	{
		Administrador admin;
		admin.consultarCaja();
		admin.cerrarCalesita();
		return 0;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}



















