#ifndef ADMIN_H
#define ADMIN_H

#include "../common/logger/Logger.h"

class Administrador
{
	public:
		Administrador ();
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

#endif
















