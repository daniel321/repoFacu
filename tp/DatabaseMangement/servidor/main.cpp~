#include "servidor.h"
#include "../common/exception/ErrnoWrap.h"
#include "signal.h"
#include "sys/types.h"
#include "sys/wait.h"
#include <iostream>

int main (int argc, char **argv)
{
	try
	{
		int result = fork();
		if (result == -1) throw Common::ErrnoWrap();
		if (result != 0)
		{
			std::cout << "Presione enter para termina la ejecución del servidor." << std::endl;
			std::cin.get();
			kill(result, SigQuit);
			wait(0);
		}
		else
		{
			Servidor servidor;
			servidor.atenderClientes();
		}
		return 0;
	}
	catch (std::exception &e)
	{
		std::cout << "Server " << ::getpid() << " : " << e.what() << std::endl;
	}
}



















