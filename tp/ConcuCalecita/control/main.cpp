#include <sys/types.h>
#include <unistd.h>
#include <iostream>

#include "Control.h"

int main (int argc, char** argv)
{
	try
	{
		Control control;
		control.correr();
		return 0;
	}
	catch (std::exception &e)
	{
		std::cout << "Control " << ::getpid() << " : " << e.what() << std::endl;
	}
}


