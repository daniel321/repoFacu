#include "vendedor.h"

#include <iostream>
#include <signal.h>					// kill
#include "../common/fifos/FifoHandler.h"
#include "../common/logger/LogStreamBuf.h"
#include "../common/Constants.h"

const char archLog[] = "logs/logVendedor";

Vendedor::Vendedor() : colaParaComprarBoleto(ARCHCOLACOMPRARBOLETOS), abierto(true),
		log(new Common::LogStreamBuf(archLog))
{
	colaParaComprarBoleto.abrir();
}

Vendedor::~Vendedor(){
	log << "Cerrando las persianas." << std::endl;
}

void Vendedor::atenderClientes(){
	// TODO borrar (para dar tiempo a los clientes de acumularse en la fila)
	sleep(5);

	do{
		int pid = FifoHandler::leer(colaParaComprarBoleto);

		if(abierto && (pid != 0))
			atenderCliente(pid);	// TODO parece haber un problema cuando se vacia
	}while(abierto);			// intenta atender 2 veces al último cliente...
}

void Vendedor::atenderCliente(int pid){
	log << "Atendiendo al cliente " << pid << "." << std::endl;
	kill(pid,SIGNALCLIENTEVENDEDOR);

	int presupuesto = FifoHandler::leer(ARCHCOMUNICACIONCLIENTEVENDEDOR);

	if (presupuesto >= PRECIOBOLETO){
		int caja = incrementarCaja();
		log << "El cliente " << pid << " ha comprado un boleto. Dinero en la caja: " << caja << "." << std::endl;
		FifoHandler::escribir(ARCHCOMUNICACIONCLIENTEVENDEDOR2,presupuesto-PRECIOBOLETO);
	}else{
		log << "El cliente " << pid << " no poseia suficiente dinero para pagar el boleto" << std::endl;
		FifoHandler::escribir(ARCHCOMUNICACIONCLIENTEVENDEDOR2,presupuesto);
	}
}

int Vendedor::incrementarCaja(){
	FifoHandler::escribir(ARCHGENTEESPERANDOUSARLACAJA,PRECIOBOLETO);
	return FifoHandler::leer(ARCHCAJAVENDEDOR);
//	caja+= PRECIOBOLETO;
}

void Vendedor::cerrar(){
	abierto = false;
	// TODO notificar gente en la cola
}
