#ifndef VENDEDOR_H
#define VENDEDOR_H

#include <iostream>
#include <signal.h>					// kill

#include "LoggerVendedor.h"
#include "../common/memCompartida/MemCompartida.h" 
#include "../common/Constants.h" 			// archivoColaComprarBoletos

#include "../common/cola/ColaEscritura.h"
#include "../common/cola/ColaLectura.h"

using namespace std;

class Vendedor {

	public:
		// constructor
		Vendedor();	

		// destructor
		~Vendedor();	

		// atiende a los clientes en orden de llegada 
		void atenderClientes() const;

	private:
		ColaLectura canal;
		MemoriaCompartida<bool> cerroLaCalecita;

		// espera a que aparezca un nuevo cliente y retorna su pid
		int esperarCliente() const;

		// atiende a un cliente
		// envia una señal al cliente para iniciar la interacción
		// luego recibe el dinero por parte de éste, de ser suficiente, le retorna el vuelto
		// si no, le retorna el total
		void atenderCliente(int pid) const;
};

// constructor
Vendedor::Vendedor():canal(ARCHCOLACOMPRARBOLETOS),cerroLaCalecita(ARCHBOLETERIACERRADA,CODEBOLETERIACERRADA){
	cerroLaCalecita.escribir(false);
}	

// destructor
Vendedor::~Vendedor(){
	LoggerVendedor::logCerrando();
}	
	
// atiende a los clientes en orden de llegada 
void Vendedor::atenderClientes() const{
	// TODO borrar (para dar tiempo a los clientes de acumularse en la fila)
	sleep(20);

	do{
		int pid = esperarCliente();

		if(!cerroLaCalecita.leer() && (pid != COLAVACIA))
			atenderCliente(pid);
	}while(!cerroLaCalecita.leer());
}

// espera a que aparezca un nuevo cliente y retorna su pid
int Vendedor::esperarCliente() const{
	int pid=0;
	do{
		pid = canal.pop();
		cout << pid << endl;
	}while((pid == COLAVACIA) && !cerroLaCalecita.leer());
	return pid;
}

// atiende a un cliente
// envia una señal al cliente para iniciar la interacción
// luego recibe el dinero por parte de éste, de ser suficiente, le retorna el vuelto
// si no, le retorna el total
void Vendedor::atenderCliente(int pid) const{
	LoggerVendedor::logAtendiendoA(pid);
	kill(pid,SIGNALCLIENTEVENDEDOR);

	ColaEscritura enviar(ARCHCOMUNICACIONCLIENTEVENDEDOR2);
	ColaLectura recibir(ARCHCOMUNICACIONCLIENTEVENDEDOR);

	int presupuesto = 0;
	do{
		presupuesto = recibir.pop();
	}while((presupuesto == COLAVACIA) && !cerroLaCalecita.leer());

	if (presupuesto >= PRECIOBOLETO)
		enviar.push(presupuesto-PRECIOBOLETO);
	else
		enviar.push(presupuesto);

}
#endif
















