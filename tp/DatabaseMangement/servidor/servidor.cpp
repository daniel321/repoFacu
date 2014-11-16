#include "servidor.h"

#include <iostream>			// cout
#include <string.h>			// strncpy

using namespace std;

Servidor::Servidor():colaRequests(ARCHI_COLA_REQUESTS,LETRA_REQUESTS),colaResponses(ARCHI_COLA_RESPONSES,LETRA_RESPONSES),atendiendo(true){
}

Servidor::~Servidor(){
	colaRequests.destruir();
	colaResponses.destruir();
	//TODO terminar server y clientes
}


void Servidor::atenderClientes(){
	do{
		int cantLeidos = colaRequests.leer(0,&req);
		if(cantLeidos > 0){
			imprimirRequest();

			if(req.leo){
				int pid = req.mtype;
				bool pudoLeer = leerDeLaBaseDeDatos();
		
				if(!pudoLeer)
					armarRespuestaDummy(pid);
	
				imprimirRspuesta();
				const response responseToSend = resp;
				colaResponses.escribir( responseToSend );
			}else{
				escribirEnLaBaseDeDatos();
			}
		}
	}while(atendiendo);
}


void Servidor::pararDeAtender(){
	atendiendo = false;
}

bool Servidor::leerDeLaBaseDeDatos(){
	//TODO leer de la base de datos y guardar campos en "resp"
	return false;
}

void Servidor::escribirEnLaBaseDeDatos(){
	//TODO escribir en la base de datos a partir de "req"
	//TODO imprimir algo o indicar que se escribio bien
}

void Servidor::armarRespuestaDummy(long mtype){
	strncpy(resp.nombre, NOMBRE_DUMMY, tamNombre);
	strncpy(resp.direccion, DIR_DUMMY, tamDir);
	strncpy(resp.telefono, TEL_DUMMY, tamTel);
	resp.mtype = mtype;
}


void Servidor::armarRespuesta(char nombre[tamNombre], char direccion[tamDir], char telefono[tamTel],long mtype){
	strncpy(resp.nombre, nombre, tamNombre);
	strncpy(resp.direccion, direccion, tamDir);
	strncpy(resp.telefono, telefono, tamTel);
	resp.mtype = mtype;
}


void Servidor::imprimirRequest(){
	cout << endl;
	cout << "Request recibida por el server: " << endl;
	cout << "Nombre: " << req.nombre << endl;
	cout << "Direccion: " << req.direccion << endl;
	cout << "Telefono: " << req.telefono << endl;
	cout << "Lectura: " << req.leo << endl;
	cout << "Tipo: " << req.mtype << endl << endl;
}

void Servidor::imprimirRspuesta(){
	cout << endl;
	cout << "Respuesta enviada por el server: " << endl;
	cout << "Nombre: " << resp.nombre << endl;
	cout << "Direccion: " << resp.direccion << endl;
	cout << "Telefono: " << resp.telefono << endl;
	cout << "Tipo: " << resp.mtype << endl << endl;
}







