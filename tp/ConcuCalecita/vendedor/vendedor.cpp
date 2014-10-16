#include "vendedor.h"

#include <iostream>
#include <signal.h>					// kill
#include "../common/fifos/FifoHandler.h"
#include "../common/logger/LogStreamBuf.h"
#include "../common/Constants.h"

const char archLog[] = "logs/logVendedor";

Vendedor::Vendedor(int precioBoleto) : colaParaComprarBoleto(ArchColaBoletos), antiEof(ArchColaBoletos),
		abierto(true),	precioBoleto(precioBoleto),log(new Common::LogStreamBuf(archLog))
{
	colaParaComprarBoleto.abrir();
	antiEof.abrir();
}

Vendedor::~Vendedor(){
	log << "Cerrando las persianas." << std::endl;
}

void Vendedor::atenderClientes()
{

	do{
		int pid = FifoHandler::leer(colaParaComprarBoleto);

		if(abierto && (pid != 0))
			atenderCliente(pid);	// TODO parece haber un problema cuando se vacia
	}while(abierto);			// intenta atender 2 veces al último cliente...
}

void Vendedor::atenderCliente(int pid){
	log << "Atendiendo al cliente " << pid << "." << std::endl;
	kill(pid,SigClienteVendedor);

	int presupuesto = FifoHandler::leer(ARCHCOMUNICACIONCLIENTEVENDEDOR);

	if (presupuesto >= precioBoleto){
		int caja = incrementarCaja();
		log << "El cliente " << pid << " ha comprado un boleto. Dinero en la caja: " << caja << "." << std::endl;
		FifoHandler::escribir(ARCHCOMUNICACIONCLIENTEVENDEDOR2,presupuesto-precioBoleto);
	}else{
		log << "El cliente " << pid << " no poseia suficiente dinero para pagar el boleto" << std::endl;
		FifoHandler::escribir(ARCHCOMUNICACIONCLIENTEVENDEDOR2,presupuesto);
	}
}

int Vendedor::incrementarCaja(){
	FifoHandler::escribir(ArchGenteEsperandoParaUsarCaja,precioBoleto);
	return FifoHandler::leer(ArchaCajaVendedor);
//	caja+= PRECIOBOLETO;
}

void Vendedor::cerrar(){
	abierto = false;
	// TODO notificar gente en la cola
}
