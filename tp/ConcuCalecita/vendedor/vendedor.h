#ifndef VENDEDOR_H
#define VENDEDOR_H

#include <iostream>
#include <signal.h>					// kill

#include "LoggerVendedor.h"
#include "../common/Constants.h" 			// archivoColaComprarBoletos

#include "../common/fifos/FifoHandler.h"		// fifos
#include "../common/fifos/FifoLectura.h"		// fifos

using namespace std;

class Vendedor {

	public:
		// constructor
		Vendedor();	

		// destructor
		~Vendedor();	

		// atiende a los clientes en orden de llegada 
		void atenderClientes();

		// TODO a ser llamada al recibir una señal para cerrar
		// por parte del administrador de la calecita
		void cerrar();

	private:
		FifoLectura colaParaComprarBoleto;
		bool abierto;

		// incrementa la caja en "precio"
		int incrementarCaja();

		// atiende a un cliente
		// envia una señal al cliente para iniciar la interacción
		// luego recibe el dinero por parte de éste, de ser suficiente, le retorna el vuelto
		// si no, le retorna el total
		void atenderCliente(int pid);
};

// constructor
Vendedor::Vendedor():colaParaComprarBoleto(ARCHCOLACOMPRARBOLETOS),abierto(true){
	colaParaComprarBoleto.abrir();
}	

// destructor
Vendedor::~Vendedor(){
	LoggerVendedor::logCerrando();
}	
	
// atiende a los clientes en orden de llegada 
void Vendedor::atenderClientes(){
	// TODO borrar (para dar tiempo a los clientes de acumularse en la fila)
	sleep(20);

	do{
		int pid = FifoHandler::leer(colaParaComprarBoleto);

		if(abierto && (pid != 0))
			atenderCliente(pid);	// TODO parece haber un problema cuando se vacia
	}while(abierto);			// intenta atender 2 veces al último cliente...
}

// atiende a un cliente
// envia una señal al cliente para iniciar la interacción
// luego recibe el dinero por parte de éste, de ser suficiente, le retorna el vuelto
// si no, le retorna el total
void Vendedor::atenderCliente(int pid){
	LoggerVendedor::logAtendiendoA(pid);
	kill(pid,SIGNALCLIENTEVENDEDOR);

	int presupuesto = FifoHandler::leer(ARCHCOMUNICACIONCLIENTEVENDEDOR);

	if (presupuesto >= PRECIOBOLETO){
		int caja = incrementarCaja();
		LoggerVendedor::logAtendido(pid,caja);
		FifoHandler::escribir(ARCHCOMUNICACIONCLIENTEVENDEDOR2,presupuesto-PRECIOBOLETO); 	
	}else{
		LoggerVendedor::logNoLeAlcanzaba(pid);
		FifoHandler::escribir(ARCHCOMUNICACIONCLIENTEVENDEDOR2,presupuesto); 	
	}
}

// incrementa la caja en "precio"
int Vendedor::incrementarCaja(){
	FifoHandler::escribir(ARCHGENTEESPERANDOUSARLACAJA,PRECIOBOLETO);
	return FifoHandler::leer(ARCHCAJAVENDEDOR);
}

// TODO a ser llamada al recibir una señal para cerrar
// por parte del administrador de la calecita
void Vendedor::cerrar(){
	abierto = false;
	// TODO notificar gente en la cola
}

#endif
















