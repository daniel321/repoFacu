#ifndef CALECITA_H
#define CALECITA_H

#include <list>
#include <ctime>					// clock
#include <signal.h>					// kill

#include "LoggerCalecita.h"
#include "../common/memCompartida/MemCompartida.h" 
#include "../common/Constants.h" 			// archivo,code

#include "../common/cola/ColaEscritura.h"
#include "../common/cola/ColaLectura.h"

using namespace std;

class Calecita {

	public:
		// constructor
		Calecita();	

		// destructor
		~Calecita();	

		// espera a que haya cierta cantidad de clientes y realiza una vuelta
		void operar();

	private:
		ColaLectura canal;
		MemoriaCompartida<bool> cerroLaCalecita;
		list<int> pids;

		// espera a que aparezca cierta cantidad de clientes para poder arrancar la calecita
		void esperarClientes();

		// da una vuelta e indica a todos los clientes de la calecita que la vuelta transcurrio
		void darVuelta();

		// TODO a ser llamado por un timeout
		void arrancarVueltaPrematuramente();
};

// constructor
Calecita::Calecita():canal(ARCHCOLACSUBIRSEALACALECITA),cerroLaCalecita(ARCHBOLETERIACERRADA,CODEBOLETERIACERRADA){
	cerroLaCalecita.escribir(false);
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
		
		if(!cerroLaCalecita.leer()){
			LoggerCalecita::logDandoUnaVuelta(pids.size());
			darVuelta();
			LoggerCalecita::logVueltaFinalizada();
		}
	}while(!cerroLaCalecita.leer());

	if(pids.size() > 0){
		LoggerCalecita::logDandoUnaVuelta(pids.size());
		darVuelta();
		LoggerCalecita::logVueltaFinalizada();
	}

}

// espera a que aparezca cierta cantidad de clientes para poder arrancar la calecita
void Calecita::esperarClientes(){
	do{
		int pid = canal.pop();

		if(pid != COLAVACIA) {
			kill(pid,SIGNALCLIENTECALECITA);
			pids.push_back(pid);
		}
	}while((pids.size() < CLIENTESPORVUELTA) && !cerroLaCalecita.leer());
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

#endif















