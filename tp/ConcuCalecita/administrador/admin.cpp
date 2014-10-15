#include "admin.h"

#include "../common/logger/LogStreamBuf.h"
#include "../common/Constants.h"
#include "../common/fifos/FifoHandler.h"

const char archLog[] = "logs/logAdmin";

Administrador::Administrador() : log(new Common::LogStreamBuf(archLog)) {}

void Administrador::consultarCaja(){
	FifoHandler::escribir(ArchGenteEsperandoParaUsarCaja,QuieroConsultarCaja);
	sleep(1);
	int caja = FifoHandler::leer(ArchCajaAdmin);
	log << "El administrador consulto la caja, habían: " << caja << "$." << std::endl;
}
