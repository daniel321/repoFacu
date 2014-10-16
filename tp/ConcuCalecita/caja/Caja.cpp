#include "Caja.h"

#include "../common/Constants.h" 			// archivoColaComprarBoletos
#include "../common/fifos/FifoHandler.h"
#include "../common/exception/InterruptException.h"

Caja::Caja(int cajaInicial):caja(cajaInicial),colaParaConsultarCaja(ArchGenteEsperandoParaUsarCaja),
			fifoRespustaVendedor(ArchaCajaVendedor), fifoRespuestaAdministrador(ArchCajaAdmin)
{
	try
	{
		colaParaConsultarCaja.abrir();
	}
	catch (Common::InterruptException &e)
	{
	}
}

Caja::~Caja()
{
	colaParaConsultarCaja.cerrar();
	colaParaConsultarCaja.eliminar();
	fifoRespustaVendedor.cerrar();
	fifoRespustaVendedor.eliminar();
	fifoRespuestaAdministrador.cerrar();
	fifoRespuestaAdministrador.eliminar();
}

void Caja::esperarModificaciones()
{
	try
	{
		while(!hayQueSalir())
		{
			int consulta = FifoHandler::leer(colaParaConsultarCaja);
			if(consulta == QuieroConsultarCaja)
				responderAAdmin();
			else
				responderAVendedor(consulta);
		}
	}
	catch (Common::InterruptException &e)
	{
	}
}

void Caja :: responderAVendedor(int ganancia){
	caja += ganancia;
	fifoRespustaVendedor.abrir();
	FifoHandler::escribir(fifoRespustaVendedor,caja);
}

void Caja :: responderAAdmin(){
	fifoRespuestaAdministrador.abrir();
	FifoHandler::escribir(fifoRespuestaAdministrador,caja);
}
