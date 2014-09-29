#ifndef ADMIN_H
#define ADMIN_H

#include "../common/memCompartida/MemCompartida.h"
#include "../common/Constants.h" // archivo,code

using namespace std;

class Administrador {

	public:
		// constructor
		Administrador();	

		// destructor
		~Administrador();	

		// intenta consultar la el dinero de la recaudacion de la calecita
		void consultarCaja();

		// cierra la calecita
		void CerrarCalecita();
	private:
		MemoriaCompartida<bool> cerroLaCalecita;

};

// constructor
Administrador::Administrador():cerroLaCalecita(ARCHBOLETERIACERRADA,CODEBOLETERIACERRADA){
	cerroLaCalecita.escribir(false);
}	

// destructor
Administrador::~Administrador(){
//	cerroLaCalecita.liberar();
}	
	
// intenta consultar la el dinero de la recaudacion de la calecita
void Administrador::consultarCaja(){}

// cierra la calecita
void Administrador::CerrarCalecita(){
	cerroLaCalecita.escribir(true);
}

#endif
















