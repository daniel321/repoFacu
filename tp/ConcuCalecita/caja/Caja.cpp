#include "Caja.h"

#include "../common/Constants.h" 			// archivoColaComprarBoletos
#include "../common/fifos/FifoHandler.h"

Caja::Caja(int cajaInicial):caja(cajaInicial),colaParaConsultarCaja(ARCHGENTEESPERANDOUSARLACAJA),abierto(true){
	colaParaConsultarCaja.abrir();
}

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

void Caja :: responderAVendedor(){
	caja += PRECIOBOLETO;
	FifoHandler::escribir(ARCHCAJAVENDEDOR,caja);
}

void Caja :: responderAAdmin(){
	FifoHandler::escribir(ARCHCAJAADMIN,caja);
}

// TODO a ser llamada al recibir una señal para cerrar
// por parte del administrador de la calecita
void Caja::cerrar(){
	abierto = false;
}


