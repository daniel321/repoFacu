#ifndef CALECITA_H
#define CALECITA_H

#include <iostream>
#include <ctime>			// clock

#include "commonMemoriaCompartida.h"	// MemoriaCompartida
#include "commonConstantes.h" 		// archivo,code

using namespace std;

class Calecita {

	public:
		// constructor
		Calecita();	

		// destructor
		~Calecita();	

		// espera la indicacion del usuario para arrancar a atender	
		void esperarApertura();

		// espera a que haya cierta cantidad de clientes y realiza una vuelta
		void operar();

	private:
		MemoriaCompartida<bool> abrioLaBoleteria;
		MemoriaCompartida<int> genteEnLaCola;
};

// constructor
Calecita::Calecita():abrioLaBoleteria(archivoAbrioBoleteria,codeAbrioBoleteria),genteEnLaCola(archivoCola,codeCola){
	genteEnLaCola.escribir(0);
}	

// destructor
Calecita::~Calecita(){}	
	
// espera la indicacion del usuario para arrancar a atender
void Calecita::esperarApertura(){
	while(abrioLaBoleteria.leer() == false){}
}

// espera a que haya cierta cantidad de clientes y realiza una vuelta
void Calecita::operar(){
	double tiempoInicial = clock();

	// TODO, sincronizar, atender clientes...
	
	double tiempoActual;
	do{
		tiempoActual = clock();
		if(genteEnLaCola.leer() >= clientesPorVuelta){
			genteEnLaCola.escribir(genteEnLaCola.leer()-clientesPorVuelta);
			tiempoInicial = tiempoActual;
		}
	}while(tiempoActual-tiempoInicial < tiempoMaxDeEsperaSinClientes);
}

#endif
















