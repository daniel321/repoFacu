#ifndef CLIENT_H
#define CLIENT_H

#include <sys/types.h>					// getpid()
#include <unistd.h>
#include <sstream>

#include "../common/signals/Handler.h" 		
#include "../common/signals/SignalHandler.h" 		// handler para setear bandera con una señal

#include "../common/Constants.h" 			// archivo,code	
#include "../common/fifos/FifoHandler.h"
#include "../common/logger/Logger.h"

const char archLog[]  = "logs/logClientes";

using namespace std;

class Cliente {

	public:
		Cliente(int presup,bool boleto);	
		~Cliente();	

		// espera a ser atendido y compra el boleto	
		void comprarBoleto();

		// ocurre cuando es atendido (x interrupción)
		// envia al vendedor el dinero disponible y recibe vuelto
		// en caso que el dinero no sea suficiente, no se produce cambio algúno
		// (y el cliente se va a casa...)
		void comunicacionConElVendedor();

		// espera a poder subirse en la calecita
		void subirseALaCalesita();

		// ocurre cuando se sube a la calecita (x interrupción)
		void subidaALaCalesita();

		// TODO a ser llamada al recibir una señal indicando que cerro la calecita
		void echar();

	private:
		bool tengoBoleto;
		bool meCerraronLaCalesita;
		int  cash;
		int  id;
		Common::Logger log;

		// el cliente se agrega a si mismo a una cola y espera ser atendido
		void esperarEnLaCola(const char* pathCola,Handler& handler);
};

Cliente::Cliente(int presup,bool boleto)
	:	tengoBoleto(boleto), meCerraronLaCalesita(false), cash(presup), id(getpid()), log(archLog) {}

Cliente::~Cliente()
{
	log << "Cliente " << id << " yendose a casa." << endl;
}	

// el cliente se agrega a si mismo a una cola y espera ser atendido
void Cliente::esperarEnLaCola(const char* pathCola,Handler& handler){
	FifoHandler::escribir(pathCola,id); 

	while((handler.getBandera() != 1) && !meCerraronLaCalesita)
		sleep(ESPERA);
}

// espera la indicacion del usuario para arrancar a atender
void Cliente::comprarBoleto(){
	if(!tengoBoleto && !meCerraronLaCalesita){
		log << "Cliente " << id << " haciendo la cola para comprar boleto." << endl;
		
		Handler handler(SIGNALCLIENTEVENDEDOR);
		SignalHandler::getInstance()->registrarHandler(SIGNALCLIENTEVENDEDOR,&handler);
	
		esperarEnLaCola(ARCHCOLACOMPRARBOLETOS,handler); 

		if(meCerraronLaCalesita){
			log << "Cliente " << id << " no pudo comprar el boleto por que cerro la boleteria." << endl;
		}else{
			if(handler.getBandera()){
				log << "Cliente " << id << " recibio la señal del vendedor." << endl;
				comunicacionConElVendedor();
			}
		}
	}else{
		log << "Cliente " << id << " no hace la cola por tener ya un boleto." << endl;
	}
}

// ocurre cuando es atendido (x interrupción)
// envia al vendedor el dinero disponible y recibe vuelto
// en caso que el dinero no sea suficiente, no se produce cambio algúno
// (y el cliente se va a casa...)
void Cliente::comunicacionConElVendedor(){

	FifoHandler::escribir(ARCHCOMUNICACIONCLIENTEVENDEDOR,cash); 	
	int sobrante = FifoHandler::leer(ARCHCOMUNICACIONCLIENTEVENDEDOR2);

	if (sobrante != cash){
		log << "Cliente " << id << " compró exitosamente el boleto, sobraron " << sobrante << " pesos." << endl;
		tengoBoleto = true;
	}else{
		log << "cliente " << id << " no pudo comprar el boleto por falta de dinero, faltaban "
				<< PRECIOBOLETO-cash << " pesos." << endl;
	}

	cash = sobrante;
}

// espera a poder subirse en la calecita
void Cliente::subirseALaCalesita(){
	if(meCerraronLaCalesita){
		log << "Cliente " << id << " no pudo subirse ya que cerro la calecita." << endl;
	}else{
		if(tengoBoleto){
			log << "cliente " << id << " haciendo la cola para subisre a la calecita." << endl;

			Handler handler(SIGNALCLIENTECALECITA);
			SignalHandler::getInstance()->registrarHandler(SIGNALCLIENTECALECITA,&handler);
	
			esperarEnLaCola(ARCHCOLACSUBIRSEALACALECITA,handler); 

			if(handler.getBandera() && !meCerraronLaCalesita){
				log << "Cliente " << id << " entro en la calecita." << endl;
				subidaALaCalesita();
			}
		}
	}
}

// ocurre cuando se sube a la calecita (x interrupción)
void Cliente::subidaALaCalesita(){
	tengoBoleto = false;

	Handler handler(SIGNALTERMINOCALECITA);
	SignalHandler::getInstance()->registrarHandler(SIGNALTERMINOCALECITA,&handler);

	while(handler.getBandera() != 1)
		sleep(ESPERA);
}

// TODO a ser llamada al recibir una señal indicando que cerro la calecita
void Cliente::echar(){
	meCerraronLaCalesita = true;
}

#endif



















