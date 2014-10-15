#include "Control.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <sys/types.h>
#include <sys/wait.h>

#include "../common/exception/ErrnoWrap.h"
#include "../common/Constants.h"

Control::Control() {}

Control::~Control() {}

void Control::correr()
{
	while (true)
	{
		std::cout << "a. Lanzar procesos base." << std::endl;
		std::cout << "b. Lanzar clientes." << std::endl;
		std::cout << "c. Esperar finalización de clientes." << std::endl;
		std::cout << "d. Cerrar procesos base." << std::endl;
		std::cout << "e. Salir." << std::endl << std::endl;
		char opcion;
		std::cin >> opcion;
		switch (opcion)
		{
			case 'a':
				lanzarProcesos();
				break;
			case 'b':
				lanzarClientes();
				break;
			case 'c':
				esperarClientes();
				break;
			case 'd':
				cerrarProcesos();
				break;
			case 'e':
				return;
			default:
				std::cout << "Opcion invalida." << std::endl;
				break;
		}
		std::cout << std::endl;
	}
}

void Control::lanzarProcesos()
{
	if (pidsProcesos.size() > 0)
	{
		std::cout << "Ya fueron lanzados" << std::endl;
		return;
	}
	int result;
	result = fork();
	if (result == -1) throw Common::ErrnoWrap();
	if (result == 0)
	{
		result = execl("admin.exe", 0);
		if (result == -1) throw Common::ErrnoWrap();
	}
	pidsProcesos.push_back(result);
	result = fork();
	if (result == -1) throw Common::ErrnoWrap();
	if (result == 0)
	{
		result = execl("caja.exe", 0);
		if (result == -1) throw Common::ErrnoWrap();
	}
	pidsProcesos.push_back(result);
	result = fork();
	if (result == -1) throw Common::ErrnoWrap();
	if (result == 0)
	{
		result = execl("vendedor.exe", 0);
		if (result == -1) throw Common::ErrnoWrap();
	}
	pidsProcesos.push_back(result);
	result = fork();
	if (result == -1) throw Common::ErrnoWrap();
	if (result == 0)
	{
		result = execl("calesita.exe", 0);
		if (result == -1) throw Common::ErrnoWrap();
	}
	pidsProcesos.push_back(result);
	std::cout << "Procesos lanzados exitosamente" << std::endl;
	return;
}

void Control::lanzarClientes()
{
	int cuantos,pMin,pMax;
	std::cout << "Ingrese cuantos desea lanzar:" << std::endl;
	std::cin >> cuantos;
	std::cout << "Ingrese su dinero minimo:" << std::endl;
	std::cin >> pMin;
	std::cout << "Ingrese su dinero maximo:" << std::endl;
	std::cin >> pMax;

	int varianza = pMax-pMin;
	int result;
	srand(time(NULL));
	for (int i = 0; i < cuantos; ++i)
	{
		int monto = pMin + rand()%varianza;
		result = fork();
		if (result == -1) throw Common::ErrnoWrap("e1");
		if (result == 0)
		{
			result = execl("client.exe", "client.exe", intToStr(monto).c_str(), 0);
			if (result == -1) throw Common::ErrnoWrap("e2");
		}
		pidsClientes.push_back(result);
	}
}

void Control::esperarClientes()
{
	std::cout << "Esperando..." << std::endl;
	int status;
	while (!pidsClientes.empty())
	{
		int pid = pidsClientes.back();
		waitpid(pid, &status, 0);
		pidsClientes.pop_back();
	}
	std::cout << "Clientes terminados exitosamente" << std::endl;
}

void Control::cerrarProcesos()
{
	std::cout << "Cerrando..." << std::endl;
	int status;
	while (!pidsProcesos.empty())
	{
		int pid = pidsProcesos.back();
		kill(pid, SigQuit);
		waitpid(pid, &status, 0);
		pidsProcesos.pop_back();
	}
	std::cout << "Procesos cerrados exitosamente" << std::endl;
}

std::string Control::intToStr(int i)
{
	std::stringstream s;
	s << i;
	return s.str();
}
