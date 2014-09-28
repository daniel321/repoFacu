#ifndef VENDEDOR_H
#define VENDEDOR_H

#include <iostream>

#include "LoggerVendedor.h"
#include "../common/MemCompartida.h" 
#include "../common/Constants.h" 		// archivoColaComprarBoletos
#include "../cola/ColaLectura.h"

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

		// TODO atiende a un cliente
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
		if(!cerroLaCalecita.leer())
			atenderCliente(pid);
	}while(!cerroLaCalecita.leer());
}

// espera a que aparezca un nuevo cliente y retorna su pid
int Vendedor::esperarCliente() const{
	int pid=0;
	do{
		pid = canal.pop();
	}while((pid == 0) && !cerroLaCalecita.leer());
	return pid;
}

// TODO atiende a un cliente
void Vendedor::atenderCliente(int pid) const{
	LoggerVendedor::logAtendiendoA(pid);
}

#endif
















