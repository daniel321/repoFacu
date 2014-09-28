#ifndef CLIENT_H
#define CLIENT_H

#include <sys/types.h>			// getpid()
#include <unistd.h>
#include <sstream>

#include "../common/MemCompartida.h" 
#include "../common/Constants.h" 	// archivo,code	
#include "../cola/ColaEscritura.h"
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

		// TODO, ocurre cuando es atendido (x interrupción)
		void comunicacionConElVendedor();

		// espera a poder subirse en la calecita
		void subirseALaCalecita();

		// TODO, ocurre cuando se sube a la calecita (x interrupción)
		void subidaALaCalecita();

	private:
		MemoriaCompartida<bool> cerroLaCalecita;
		bool tengoBoleto;
		bool esperando;
		int  cash;
		int  id;

		// el cliente se agrega a si mismo a una cola y espera ser atendido
		void esperarEnLaCola(const char* pathCola);
};

// constructor
Cliente::Cliente(int presup,bool boleto):cerroLaCalecita(ARCHBOLETERIACERRADA,CODEBOLETERIACERRADA),tengoBoleto(boleto),cash(presup),id(getpid()){
}	

// destructor
Cliente::~Cliente(){
	LoggerCliente::logLlendoseACasa(id);
}	

// el cliente se agrega a si mismo a una cola y espera ser atendido
void Cliente::esperarEnLaCola(const char* pathCola){
	ColaEscritura canal(pathCola); 
	canal.push(id);

	esperando = true;
	while(esperando && !cerroLaCalecita.leer())
		sleep(ESPERA);
}

// espera la indicacion del usuario para arrancar a atender
void Cliente::comprarBoleto(){
	if(!tengoBoleto){
		LoggerCliente::logEsperandoParaComprarBoleto(id);
		esperarEnLaCola(ARCHCOLACOMPRARBOLETOS); 

		if(tengoBoleto){
			LoggerCliente::logAdquirioElBoleto(id,cash);
		}else{ 
			if(cerroLaCalecita.leer())
				LoggerCliente::logNoPudoComprarElBoletoCerroLaBoleteria(id);			
			else
				LoggerCliente::logNoPudoComprarElBoletoFaltoCash(id,PRECIOBOLETO-cash);
		}
	}else{
		LoggerCliente::logYaTeniaBoleto(id);
	}
}

// TODO, ocurre cuando es atendido (x interrupción)
void Cliente::comunicacionConElVendedor(){
	if (cash >= PRECIOBOLETO){
		tengoBoleto = true;
		cash -= PRECIOBOLETO;
	}
}

// espera a poder subirse en la calecita
void Cliente::subirseALaCalecita(){
	if(tengoBoleto){
		LoggerCliente::logEsperandoParaSubirseALaCalecita(id);
		esperarEnLaCola(ARCHCOLACSUBIRSEALACALECITA); 
	}

}

// TODO, ocurre cuando se sube a la calecita (x interrupción)
void Cliente::subidaALaCalecita(){
	LoggerCliente::logEnLaCalecita(id);
	tengoBoleto = false;

	//TODO avisarle al cliente cuando termina la vuelta
	esperando = true;
	while(esperando && !cerroLaCalecita.leer())
		sleep(ESPERA);
}



#endif



















