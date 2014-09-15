#include "client.h" 	// Cliente
#include <stdlib.h>	// atoi

int main (int argc, char** argv) {

	int presupuesto;
	if(argc >= 0){
		presupuesto = atoi(argv[1]);
		
		Cliente cliente(presupuesto);
		cliente.esperarApertura();
		cliente.comprarBoleto();
		cliente.subirseALaCalecita();
	}

	return 0;
}












