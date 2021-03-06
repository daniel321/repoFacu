#include "client.h"
#include <iostream>

int main (int argc, char** argv)
{
	try
		{
		Cliente cliente;
		while (true)
		{
			std::cout << "1. Guardar registro." << std::endl;
			std::cout << "2. Consultar." << std::endl;
			std::cout << "3. Salir." << std::endl;
			char opcion;
			std::cin >> opcion;
			switch(opcion)
			{
				case '1':
				case '2':
				{
					std::string nombre;
					std::string dir;
					std::string tel;
					std::cout << "Ingrese nombre (o *):" << std::endl;
					std::cin.ignore();
					std::getline(std::cin, nombre);
					std::cout << "Ingrese direccion (o *):" << std::endl;
					std::getline(std::cin, dir);
					std::cout << "Ingrese telefono (o *):" << std::endl;
					std::getline(std::cin, tel);
					if (opcion == '1')
							cliente.escribirEnBaseDeDatos(nombre, dir, tel);
					if (opcion == '2')
							cliente.consultarBaseDeDatos(nombre, dir, tel);
					break;
				}
				case '3':
					return 0;
					break;
			}
		}
		return 0;
	}
	catch (std::exception &e)
	{
		std::cout << "Cliente " << ::getpid() << " : " << e.what() << std::endl;
	}
}












