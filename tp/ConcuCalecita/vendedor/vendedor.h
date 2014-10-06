#ifndef VENDEDOR_H
#define VENDEDOR_H

#include <iostream>
#include <signal.h>					// kill

#include "../common/fifos/FifoHandler.h"
#include "../common/fifos/FifoLectura.h"
#include "../common/logger/Logger.h"
#include "../common/logger/LogStreamBuf.h"
#include "../common/Constants.h"

const char archLog[] = "logs/logVendedor";

using namespace std;

class Vendedor {

	public:
		Vendedor();	
		~Vendedor();	

		// atiende a los clientes en orden de llegada 
		void atenderClientes();

		// TODO a ser llamada al recibir una señal para cerrar
		// por parte del administrador de la calecita
		void cerrar();

	private:
		FifoLectura colaParaComprarBoleto;
		bool abierto;
		Common::Logger log;

		// incrementa la caja en "precio"
		int incrementarCaja();

		// atiende a un cliente
		// envia una señal al cliente para iniciar la interacción
		// luego recibe el dinero por parte de éste, de ser suficiente, le retorna el vuelto
		// si no, le retorna el total
		void atenderCliente(int pid);
};

// constructor
Vendedor::Vendedor() : colaParaComprarBoleto(ARCHCOLACOMPRARBOLETOS), abierto(true),
		log(new Common::LogStreamBuf(archLog))
{
	colaParaComprarBoleto.abrir();
}	

// destructor
Vendedor::~Vendedor(){
	log << "Cerrando las persianas." << endl;
}	
	
// atiende a los clientes en orden de llegada 
void Vendedor::atenderClientes(){
	// TODO borrar (para dar tiempo a los clientes de acumularse en la fila)
	sleep(5);

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
	log << "Atendiendo al cliente " << pid << "." << endl;
	kill(pid,SIGNALCLIENTEVENDEDOR);

	int presupuesto = FifoHandler::leer(ARCHCOMUNICACIONCLIENTEVENDEDOR);

	if (presupuesto >= PRECIOBOLETO){
		int caja = incrementarCaja();
		log << "El cliente " << pid << " ha comprado un boleto. Dinero en la caja: " << caja << "." << endl;
		FifoHandler::escribir(ARCHCOMUNICACIONCLIENTEVENDEDOR2,presupuesto-PRECIOBOLETO); 	
	}else{
		log << "El cliente " << pid << " no poseia suficiente dinero para pagar el boleto" << endl;
		FifoHandler::escribir(ARCHCOMUNICACIONCLIENTEVENDEDOR2,presupuesto); 	
	}
}

//int caja = 0;
// incrementa la caja en "precio"
int Vendedor::incrementarCaja(){
	FifoHandler::escribir(ARCHGENTEESPERANDOUSARLACAJA,PRECIOBOLETO);
	return FifoHandler::leer(ARCHCAJAVENDEDOR);
//	caja+= PRECIOBOLETO;
}

// TODO a ser llamada al recibir una señal para cerrar
// por parte del administrador de la calecita
void Vendedor::cerrar(){
	abierto = false;
	// TODO notificar gente en la cola
}

#endif
















