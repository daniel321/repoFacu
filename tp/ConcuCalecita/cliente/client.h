#ifndef CLIENT_H
#define CLIENT_H

#include <sys/types.h>			// getpid()
#include <unistd.h>
#include <sstream>

#include "../common/signals/Handler.h" 
#include "../common/signals/SignalHandler.h" 

#include "../common/memCompartida/MemCompartida.h" 
#include "../common/Constants.h" 	// archivo,code	

#include "../common/cola/ColaEscritura.h"
#include "../common/cola/ColaLectura.h"

#include "LoggerCliente.h"

using namespace std;

class Cliente {

	public:
		// constructor
		Cliente(int presup,bool boleto);	

		// destructor
		~Cliente();	

		// espera a ser atendido y compra el boleto	
		void comprarBoleto();

		// ocurre cuando es atendido (x interrupción)
		// envia al vendedor el dinero disponible y recibe vuelto
		// en caso que el dinero no sea suficiente, no se produce cambio algúno
		// (y el cliente se va a casa...)
		void comunicacionConElVendedor();

		// espera a poder subirse en la calecita
		void subirseALaCalecita();

		// ocurre cuando se sube a la calecita (x interrupción)
		void subidaALaCalecita();

	private:
		MemoriaCompartida<bool> cerroLaCalecita;
		bool tengoBoleto;
		int  cash;
		int  id;

		// el cliente se agrega a si mismo a una cola y espera ser atendido
		void esperarEnLaCola(const char* pathCola,Handler& handler);
};

// constructor
Cliente::Cliente(int presup,bool boleto):cerroLaCalecita(ARCHBOLETERIACERRADA,CODEBOLETERIACERRADA),tengoBoleto(boleto),cash(presup),id(getpid()){
}	

// destructor
Cliente::~Cliente(){
	LoggerCliente::logLlendoseACasa(id);
}	

// el cliente se agrega a si mismo a una cola y espera ser atendido
void Cliente::esperarEnLaCola(const char* pathCola,Handler& handler){
	ColaEscritura canal(pathCola); 
	canal.push(id);

	while((handler.getBandera() != 1) && !cerroLaCalecita.leer())
		sleep(ESPERA);
}

// espera la indicacion del usuario para arrancar a atender
void Cliente::comprarBoleto(){
	if(!tengoBoleto){
		LoggerCliente::logEsperandoParaComprarBoleto(id);
		
		Handler handler(SIGNALCLIENTEVENDEDOR);
		SignalHandler::getInstance()->registrarHandler(SIGNALCLIENTEVENDEDOR,&handler);
	
		esperarEnLaCola(ARCHCOLACOMPRARBOLETOS,handler); 

		if(handler.getBandera()){
			LoggerCliente::logRecibiSenalVendedor(id);
			comunicacionConElVendedor();
		}

	}else{
		LoggerCliente::logYaTeniaBoleto(id);
	}
}

// ocurre cuando es atendido (x interrupción)
// envia al vendedor el dinero disponible y recibe vuelto
// en caso que el dinero no sea suficiente, no se produce cambio algúno
// (y el cliente se va a casa...)
void Cliente::comunicacionConElVendedor(){

	ColaLectura recibir(ARCHCOMUNICACIONCLIENTEVENDEDOR2);
	ColaEscritura enviar(ARCHCOMUNICACIONCLIENTEVENDEDOR);

	sleep(2); // TODO cambiar x semaforo (necesito q se cree el leer antes q se mande algo)
	enviar.push(cash);

	int sobrante = 0;
	do{
		sobrante = recibir.pop();
	}while((sobrante == COLAVACIA) && !cerroLaCalecita.leer());


	if(cerroLaCalecita.leer()){
		LoggerCliente::logNoPudoComprarElBoletoCerroLaBoleteria(id);	
	}else if (sobrante != cash){
		LoggerCliente::logAdquirioElBoleto(id,cash);
		tengoBoleto = true;
	}else{
		LoggerCliente::logNoPudoComprarElBoletoFaltoCash(id,PRECIOBOLETO-sobrante);
	}

	cash = sobrante;
}

// espera a poder subirse en la calecita
void Cliente::subirseALaCalecita(){
	if(tengoBoleto){
		LoggerCliente::logEsperandoParaSubirseALaCalecita(id);

		Handler handler(SIGNALCLIENTECALECITA);
		SignalHandler::getInstance()->registrarHandler(SIGNALCLIENTECALECITA,&handler);

		esperarEnLaCola(ARCHCOLACSUBIRSEALACALECITA,handler); 

		if(handler.getBandera()){
			LoggerCliente::logRecibiSenalCalecita(id);
			subidaALaCalecita();
		}
	}

}

// ocurre cuando se sube a la calecita (x interrupción)
void Cliente::subidaALaCalecita(){
	LoggerCliente::logEnLaCalecita(id);
	tengoBoleto = false;

	Handler handler(SIGNALTERMINOCALECITA);
	SignalHandler::getInstance()->registrarHandler(SIGNALTERMINOCALECITA,&handler);

	while((handler.getBandera() != 1) && !cerroLaCalecita.leer())
		sleep(ESPERA);
}



#endif



















