#include "vendedor.h"

#include <iostream>
#include <signal.h>					// kill
#include "../common/fifos/FifoHandler.h"
#include "../common/logger/LogStreamBuf.h"
#include "../common/signals/SignalHandler.h"
#include "../common/Constants.h"
#include "../common/exception/InterruptException.h"

const char archLog[] = "logs/logVendedor";

Vendedor::Vendedor(int precioBoleto) : colaParaComprarBoleto(ArchColaBoletos), antiEof(ArchColaBoletos),
		precioBoleto(precioBoleto),log(new Common::LogStreamBuf(archLog))
{
	try
	{
		colaParaComprarBoleto.abrir();
		antiEof.abrir();
	}
	catch (Common::InterruptException &e)
	{
	}
}

Vendedor::~Vendedor(){
	log << "Cerrando." << std::endl;
	colaParaComprarBoleto.cerrar();
	antiEof.cerrar();
	colaParaComprarBoleto.eliminar();
}

void Vendedor::atenderClientes()
{
	while(!hayQueSalir())
	{
		try
		{
			int pid = FifoHandler::leer(colaParaComprarBoleto);
			if(!hayQueSalir() && (pid != 0)) atenderCliente(pid);
		}
		catch (Common::InterruptException &e)
		{

		}
	};
}

void Vendedor::atenderCliente(int pid){
	log << "Atendiendo al cliente " << pid << "." << std::endl;
	kill(pid,SigClienteVendedor);

	int presupuesto = FifoHandler::leer(ARCHCOMUNICACIONCLIENTEVENDEDOR, true);

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
