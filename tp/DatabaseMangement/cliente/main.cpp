#include "client.h" 	// Cliente
#include <stdlib.h>	// atoi

static const int ERROR = 1;
static const int OK = 0;

/**
 * Arguemtnos esperados:
 * 1 - Nombre
 * 2 - Direccion
 * 3 - Teléfono
 * 4 - Si lee (1) o escribe (0)
 */

int main (int argc, char** argv){
	if (argc <= 4){
		return ERROR;	
	}

	Cliente cliente;

	if(atoi(argv[4]) == 1){
		cliente.consultarBaseDeDatos(argv[1],argv[2],argv[3]);
	}else{
		cliente.escribirEnBaseDeDatos(argv[1],argv[2],argv[3]);	
	}

	return OK;
}












