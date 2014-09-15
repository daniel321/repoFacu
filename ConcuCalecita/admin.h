#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>

#include "commonMemoriaCompartida.h"	// MemoriaCompartida
#include "commonConstantes.h" 		// archivo,code

using namespace std;

class Administrador {

	public:
		// constructor
		Administrador();	

		// destructor
		~Administrador();	

		// intenta consultar la el dinero de la recaudacion de la calecita
		void consultarCaja();

	private:
		MemoriaCompartida<int> ventas;
};

// constructor
Administrador::Administrador():ventas(archivoCaja,codeCaja){}	

// destructor
Administrador::~Administrador(){}	
	
// intenta consultar la el dinero de la recaudacion de la calecita
void Administrador::consultarCaja(){
	// TODO sincronizar
	cout << "se recaudo: " << ventas.leer()*PrecioBoleto << endl;
}

#endif
















