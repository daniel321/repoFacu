#ifndef ADMIN_H
#define ADMIN_H

#include "../common/Constants.h"
#include "../common/logger/Logger.h"
#include "../common/fifos/FifoHandler.h"

const char archLog[] = "logs/logAdmin";

class Administrador
{
	public:
		Administrador () : log(archLog) {}
		/**
		 * Intenta consultar la el dinero de la recaudacion de la calecita
		 */
		void consultarCaja();

		/**
		 * Cierra la calesita???
		 * TODO: Revisar como manejar estas cuestiones
		 */
		void cerrarCalesita();

	private:
		Common::Logger log;

};
	
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

#endif
















