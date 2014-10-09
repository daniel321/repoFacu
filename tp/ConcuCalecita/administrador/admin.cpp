#include "admin.h"

#include "../common/logger/LogStreamBuf.h"
#include "../common/Constants.h"
#include "../common/fifos/FifoHandler.h"

const char archLog[] = "logs/logAdmin";

Administrador::Administrador() : log(new Common::LogStreamBuf(archLog)) {}

void Administrador::consultarCaja(){
	FifoHandler::escribir(ARCHGENTEESPERANDOUSARLACAJA,QUIEROCONSULTARCAJA);
	sleep(1);
	int caja = FifoHandler::leer(ARCHCAJAADMIN);
	log << "El administrador consulto la caja, habían: " << caja << "$." << std::endl;
}

void Administrador::cerrarCalesita()
{
	log << "El administrador dio la orden de cerrar la calecita." << std::endl;
}


