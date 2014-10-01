#ifndef CALECITA_H
#define CALECITA_H

#include <list>
#include <ctime>					// clock
#include <signal.h>					// kill

#include "LoggerCalecita.h"				// logger
#include "../common/Constants.h" 			// archivo,code
#include "../common/fifos/FifoHandler.h"		// fifos
#include "../common/fifos/FifoLectura.h"		// fifos

using namespace std;

class Calecita {

	public:
		// constructor
		Calecita();	

		// destructor
		~Calecita();	

		// espera a que haya cierta cantidad de clientes y realiza una vuelta
		void operar();

		// TODO a ser llamada al recibir una señal para cerrar
		// por parte del administrador de la calecita
		void cerrar();

	private:
		FifoLectura colaParaEntrar;
		list<int> pids;
		bool abierto;

		// espera a que aparezca cierta cantidad de clientes para poder arrancar la calecita
		void esperarClientes();

		// da una vuelta e indica a todos los clientes de la calecita que la vuelta transcurrio
		void darVuelta();

		// TODO a ser llamado por un timeout
		void arrancarVueltaPrematuramente();
};

// constructor
Calecita::Calecita():colaParaEntrar(ARCHCOLACSUBIRSEALACALECITA),abierto(true){
	colaParaEntrar.abrir();
}	

// destructor
Calecita::~Calecita(){
	LoggerCalecita::logCerrando();
}	

// espera a que haya cierta cantidad de clientes y realiza una vuelta
void Calecita::operar(){
	do{
		LoggerCalecita::logEsperandoGente();
		esperarClientes();

		// TODO reset timeout

		LoggerCalecita::logDandoUnaVuelta(pids.size());
		darVuelta();
		LoggerCalecita::logVueltaFinalizada();
	}while(abierto);

	if(pids.size() > 0){
		LoggerCalecita::logDandoUnaVuelta(pids.size());
		darVuelta();
		LoggerCalecita::logVueltaFinalizada();
	}

}

// espera a que aparezca cierta cantidad de clientes para poder arrancar la calecita
void Calecita::esperarClientes(){
	do{
		int pid = FifoHandler::leer(colaParaEntrar);

		if(pid != 0) {
			kill(pid,SIGNALCLIENTECALECITA);
			pids.push_back(pid);
		}
	}while((pids.size() < CLIENTESPORVUELTA) && abierto);
}

// TODO a ser llamado por un timeout
void Calecita::arrancarVueltaPrematuramente(){
	darVuelta();
}

// da una vuelta e indica a todos los clientes de la calecita que la vuelta transcurrio
void Calecita::darVuelta(){
	sleep(TIEMPODEVUELTA);
	
	for (list<int>::const_iterator iterator = pids.begin(); iterator != pids.end(); ++iterator) 
		kill(*iterator,SIGNALTERMINOCALECITA);
	pids.clear();
}

// TODO a ser llamada al recibir una señal para cerrar
// por parte del administrador de la calecita
void Calecita::cerrar(){
	abierto = false;
	// TODO notificar gente en la cola
}

#endif
















