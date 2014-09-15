#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>

#include "commonMemoriaCompartida.h"	// MemoriaCompartida
#include "commonConstantes.h" 		// archivo,code	

using namespace std;

class Cliente {

	public:
		// constructor
		Cliente(int presup);	

		// destructor
		~Cliente();	

		// espera a que abra la calecita
		void esperarApertura();

		// espera a ser atendido y compra el boleto	
		void comprarBoleto();

		// espera a poder subirse en la calecita
		void subirseALaCalecita();

	private:
		MemoriaCompartida<bool> abrioLaBoleteria;
		MemoriaCompartida<int> ventas;
		MemoriaCompartida<int> genteEnLaCola;

		bool tengoBoleto;
		int  cash;
};

// constructor
Cliente::Cliente(int presup):abrioLaBoleteria(archivoAbrioBoleteria,codeAbrioBoleteria),ventas(archivoCaja,codeCaja),genteEnLaCola(archivoCola,codeCola),tengoBoleto(false),cash(presup){}	

// destructor
Cliente::~Cliente(){}	
	
// espera a que abra la calecita
void Cliente::esperarApertura(){
	while(abrioLaBoleteria.leer() == false){}
}

// espera la indicacion del usuario para arrancar a atender
void Cliente::comprarBoleto(){

	// TODO sincronizar, pasar al lado del vendedor, validar boleto de alguna forma...
	if(cash >= PrecioBoleto){
		ventas.escribir(ventas.leer()+1);
		cash-= PrecioBoleto;
		tengoBoleto = true;
	}else{
		cout << "No me alcanza, solo tengo: " << cash << endl;
	}
}

// espera a poder subirse en la calecita
void Cliente::subirseALaCalecita(){
	// TODO, esperar a subirse...
	genteEnLaCola.escribir(genteEnLaCola.leer()+1);
}

#endif



















