#include "calesita.h" 	// Calecita

int main (int argc, char** argv)
{
	try
	{
		Calesita calesita;
		calesita.operar();
		return 0;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}



















