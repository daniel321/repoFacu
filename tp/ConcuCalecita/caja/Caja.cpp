#include "Caja.h"

#include "../common/Constants.h" 			// archivoColaComprarBoletos
#include "../common/fifos/FifoHandler.h"

Caja::Caja(int cajaInicial):caja(cajaInicial),colaParaConsultarCaja(ArchGenteEsperandoParaUsarCaja),abierto(true){
	colaParaConsultarCaja.abrir();
}

void Caja::esperarModificaciones(){
	do{
		int consulta = FifoHandler::leer(colaParaConsultarCaja);
		if(consulta == QuieroConsultarCaja){
			responderAAdmin();
		}else{
			responderAVendedor(consulta);
		}
	}while(abierto);
}

void Caja :: responderAVendedor(int ganancia){
	caja += ganancia;
	FifoHandler::escribir(ArchaCajaVendedor,caja);
}

void Caja :: responderAAdmin(){
	FifoHandler::escribir(ArchCajaAdmin,caja);
}

// TODO a ser llamada al recibir una señal para cerrar
// por parte del administrador de la calecita
void Caja::cerrar(){
	abierto = false;
}


