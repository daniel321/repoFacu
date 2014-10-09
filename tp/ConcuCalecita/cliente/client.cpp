#include "client.h"

#include <sys/types.h>					// getpid()
#include <unistd.h>
#include <sstream>

#include "../common/signals/SignalHandler.h" 		// handler para setear bandera con una señal

#include "../common/Constants.h" 			// archivo,code
#include "../common/fifos/FifoHandler.h"
#include "../common/logger/LogStreamBufSinc.h"

const char archLog[]  = "logs/logClientes";

Cliente::Cliente(int presup,bool boleto)
	:	tengoBoleto(boleto), meCerraronLaCalesita(false), cash(presup),
	 	id(getpid()), log(new Common::LogStreamBufSinc(archLog)) {}

Cliente::~Cliente()
{
	log << "Cliente " << id << " yendose a casa." << std::endl;
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
		log << "Cliente " << id << " haciendo la cola para comprar boleto." << std::endl;

		Handler handler(SIGNALCLIENTEVENDEDOR);
		SignalHandler::getInstance()->registrarHandler(SIGNALCLIENTEVENDEDOR,&handler);

		esperarEnLaCola(ARCHCOLACOMPRARBOLETOS,handler);

		if(meCerraronLaCalesita){
			log << "Cliente " << id << " no pudo comprar el boleto por que cerro la boleteria." << std::endl;
		}else{
			if(handler.getBandera()){
				log << "Cliente " << id << " recibio la señal del vendedor." << std::endl;
				comunicacionConElVendedor();
			}
		}
	}else{
		log << "Cliente " << id << " no hace la cola por tener ya un boleto." << std::endl;
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
		log << "Cliente " << id << " compró exitosamente el boleto, sobraron " << sobrante << " pesos." << std::endl;
		tengoBoleto = true;
	}else{
		log << "cliente " << id << " no pudo comprar el boleto por falta de dinero, faltaban "
				<< PRECIOBOLETO-cash << " pesos." << std::endl;
	}

	cash = sobrante;
}

// espera a poder subirse en la calecita
void Cliente::subirseALaCalesita(){
	if(meCerraronLaCalesita){
		log << "Cliente " << id << " no pudo subirse ya que cerro la calecita." << std::endl;
	}else{
		if(tengoBoleto){
			log << "cliente " << id << " haciendo la cola para subisre a la calecita." << std::endl;

			Handler handler(SIGNALCLIENTECALECITA);
			SignalHandler::getInstance()->registrarHandler(SIGNALCLIENTECALECITA,&handler);

			esperarEnLaCola(ARCHCOLACSUBIRSEALACALECITA,handler);

			if(handler.getBandera() && !meCerraronLaCalesita){
				log << "Cliente " << id << " entro en la calecita." << std::endl;
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
