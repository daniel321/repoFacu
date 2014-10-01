#ifndef VENDEDOR_H
#define VENDEDOR_H

#include "../common/Constants.h" 			// archivoColaComprarBoletos

#include "../common/fifos/FifoHandler.h"		// fifos
#include "../common/fifos/FifoLectura.h"		// fifos

class Caja {

	public:
		// constructor
		Caja(int cajaInicial);	

		// destructor
		~Caja();	

		// atiende a los que necesitan cosultar o modificar la caja
		void esperarModificaciones();

		// TODO a ser llamada al recibir una señal para cerrar
		// por parte del administrador de la calecita
		void cerrar();

	private:
		int caja;
		FifoLectura colaParaConsultarCaja;
		bool abierto;

		// incrementa la caja en un boleto vendido
		// y notifica de la nueva caja al vendedor
		void responderAVendedor();

		// notifica el valor de la caja al administrador
		void responderAAdmin();

};

// constructor
Caja::Caja(int cajaInicial):caja(cajaInicial),colaParaConsultarCaja(ARCHGENTEESPERANDOUSARLACAJA),abierto(true){
	colaParaConsultarCaja.abrir();
}	

// destructor
Caja::~Caja(){
}	
	
// atiende a los que necesitan cosultar o modificar la caja
void Caja::esperarModificaciones(){
	do{
		int consulta = FifoHandler::leer(colaParaConsultarCaja);
		if(consulta == QUIEROCONSULTARCAJA){
			responderAAdmin();
		}else{
			responderAVendedor();
		}
	}while(abierto);
}

// incrementa la caja en un boleto vendido
// y notifica de la nueva caja al vendedor
void Caja :: responderAVendedor(){
	caja += PRECIOBOLETO;
	FifoHandler::escribir(ARCHCAJAVENDEDOR,caja);
}

// notifica el valor de la caja al administrador
void Caja :: responderAAdmin(){
	FifoHandler::escribir(ARCHCAJAADMIN,caja);
}


// TODO a ser llamada al recibir una señal para cerrar
// por parte del administrador de la calecita
void Caja::cerrar(){
	abierto = false;
}

#endif
















