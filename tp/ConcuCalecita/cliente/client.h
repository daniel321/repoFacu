#ifndef CLIENT_H
#define CLIENT_H

#include <sys/types.h>					// getpid()
#include <unistd.h>
#include <sstream>

#include "LoggerCliente.h"				// logs

#include "../common/signals/Handler.h" 		
#include "../common/signals/SignalHandler.h" 		// handler para setear bandera con una señal

#include "../common/Constants.h" 			// archivo,code	
#include "../common/fifos/FifoHandler.h"		// fifos

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

		// TODO a ser llamada al recibir una señal indicando que cerro la calecita
		void echar();

	private:
		bool tengoBoleto;
		bool meCerraronLaCalecita;
		int  cash;
		int  id;

		// el cliente se agrega a si mismo a una cola y espera ser atendido
		void esperarEnLaCola(const char* pathCola,Handler& handler);
};

// constructor
Cliente::Cliente(int presup,bool boleto):tengoBoleto(boleto),meCerraronLaCalecita(false),cash(presup),id(getpid()){
}	

// destructor
Cliente::~Cliente(){
	LoggerCliente::logLlendoseACasa(id);
}	

// el cliente se agrega a si mismo a una cola y espera ser atendido
void Cliente::esperarEnLaCola(const char* pathCola,Handler& handler){
	FifoHandler::escribir(pathCola,id); 

	while((handler.getBandera() != 1) && !meCerraronLaCalecita)
		sleep(ESPERA);
}

// espera la indicacion del usuario para arrancar a atender
void Cliente::comprarBoleto(){
	if(!tengoBoleto && !meCerraronLaCalecita){
		LoggerCliente::logEsperandoParaComprarBoleto(id);
		
		Handler handler(SIGNALCLIENTEVENDEDOR);
		SignalHandler::getInstance()->registrarHandler(SIGNALCLIENTEVENDEDOR,&handler);
	
		esperarEnLaCola(ARCHCOLACOMPRARBOLETOS,handler); 

		if(meCerraronLaCalecita){
			LoggerCliente::logNoPudoComprarElBoletoCerroLaBoleteria(id);
		}else{
			if(handler.getBandera()){
				LoggerCliente::logRecibiSenalVendedor(id);
				comunicacionConElVendedor();
			}
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

	FifoHandler::escribir(ARCHCOMUNICACIONCLIENTEVENDEDOR,cash); 	
	int sobrante = FifoHandler::leer(ARCHCOMUNICACIONCLIENTEVENDEDOR2);

	if (sobrante != cash){
		LoggerCliente::logAdquirioElBoleto(id,sobrante);
		tengoBoleto = true;
	}else{
		LoggerCliente::logNoPudoComprarElBoletoFaltoCash(id,PRECIOBOLETO-cash);
	}

	cash = sobrante;
}

// espera a poder subirse en la calecita
void Cliente::subirseALaCalecita(){
	if(meCerraronLaCalecita){
		LoggerCliente::logNoPudoSubirseCerroLaCalecita(id);
	}else{
		if(tengoBoleto){
			LoggerCliente::logEsperandoParaSubirseALaCalecita(id);

			Handler handler(SIGNALCLIENTECALECITA);
			SignalHandler::getInstance()->registrarHandler(SIGNALCLIENTECALECITA,&handler);
	
			esperarEnLaCola(ARCHCOLACSUBIRSEALACALECITA,handler); 

			if(handler.getBandera() && !meCerraronLaCalecita){
				LoggerCliente::logRecibiSenalCalecita(id);
				subidaALaCalecita();
			}
		}
	}
}

// ocurre cuando se sube a la calecita (x interrupción)
void Cliente::subidaALaCalecita(){
	tengoBoleto = false;

	Handler handler(SIGNALTERMINOCALECITA);
	SignalHandler::getInstance()->registrarHandler(SIGNALTERMINOCALECITA,&handler);

	while(handler.getBandera() != 1)
		sleep(ESPERA);
}

// TODO a ser llamada al recibir una señal indicando que cerro la calecita
void Cliente::echar(){
	meCerraronLaCalecita = true;
}

#endif



















