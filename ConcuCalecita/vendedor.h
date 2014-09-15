#ifndef VENDEDOR_H
#define VENDEDOR_H

#include <iostream>

#include "commonMemoriaCompartida.h"	// MemoriaCompartida
#include "commonConstantes.h" 		// archivo,code

using namespace std;

class Vendedor {

	public:
		// constructor
		Vendedor();	

		// destructor
		~Vendedor();	

		// espera la indicacion del usuario para arrancar a atender	
		void esperarApertura();

		// atiende a los clientes en orden de llegada 
		void atenderClientes();

	private:
		MemoriaCompartida<bool> abrioLaBoleteria;
		MemoriaCompartida<int> ventas;
};

// constructor
Vendedor::Vendedor():abrioLaBoleteria(archivoAbrioBoleteria,codeAbrioBoleteria),ventas(archivoCaja,codeCaja){
	abrioLaBoleteria.escribir(false);
	ventas.escribir(0);
}	

// destructor
Vendedor::~Vendedor(){}	
	
// espera la indicacion del usuario para arrancar a atender
void Vendedor::esperarApertura(){
	string input;
	do{
		cout << "arranco? (s/n) ";
		getline(cin,input);
	}while(input == "n");
	
	cout << "abriendo...";
	abrioLaBoleteria.escribir(true);
}

// atiende a los clientes en orden de llegada 
void Vendedor::atenderClientes(){
	string input;
	do{
		//TODO atender a medida que llegan

		cout << "termino? (s/n) ";
		getline(cin,input);
	}while(input == "n");
}

#endif
















