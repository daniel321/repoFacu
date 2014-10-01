#ifndef ADMIN_H
#define ADMIN_H

#include "../common/Constants.h" 			// archivo,code
#include "LoggerAdmin.h"	 			// logger
#include "../common/fifos/FifoHandler.h"		// fifos

using namespace std;

class Administrador {

	public:
		// constructor
		Administrador();	

		// destructor
		~Administrador();	

		// intenta consultar la el dinero de la recaudacion de la calecita
		void consultarCaja();

		// cierra la calecita
		void CerrarCalecita();

};

// constructor
Administrador::Administrador(){}	

// destructor
Administrador::~Administrador(){}	
	
// intenta consultar la el dinero de la recaudacion de la calecita
void Administrador::consultarCaja(){
	FifoHandler::escribir(ARCHGENTEESPERANDOUSARLACAJA,QUIEROCONSULTARCAJA);
	sleep(1);
	int caja = FifoHandler::leer(ARCHCAJAADMIN);
	LoggerAdmin::logCaja(caja);
}

// TODO cierra la calecita
void Administrador::CerrarCalecita(){
	LoggerAdmin::logCerrar();
}

#endif
















