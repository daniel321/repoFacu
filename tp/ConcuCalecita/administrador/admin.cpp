#include "admin.h"

#include "../common/logger/LogStreamBuf.h"
#include "../common/Constants.h"
#include "../common/fifos/FifoHandler.h"
#include "../common/exception/InterruptException.h"
#include <cstdlib>

const char archLog[] = "logs/logAdmin";

Administrador::Administrador() : log(new Common::LogStreamBuf(archLog)),
		pedirConsulta(ArchGenteEsperandoParaUsarCaja), leerConsulta(ArchCajaAdmin)
{
	srand(getpid());
}

#include <iostream>
void Administrador::consultarCaja()
{
	while (!hayQueSalir())
	{
		try
		{
			pedirConsulta.abrir();
			FifoHandler::escribir(pedirConsulta,QuieroConsultarCaja);
			sleep(1+rand()%10);
			leerConsulta.abrir();
			int caja = FifoHandler::leer(leerConsulta);
			log << "El administrador consulto la caja, habían: " << caja << "$." << std::endl;
		}
		catch (Common::InterruptException &e)
		{

		}
	}
}
