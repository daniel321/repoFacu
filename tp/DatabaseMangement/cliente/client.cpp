#include "client.h"

#include <iostream>			// cout
#include <unistd.h>			// getpid
#include <string.h>			// strncpy

using namespace std;

Cliente::Cliente():colaRequests(ARCHI_COLA_REQUESTS,LETRA_REQUESTS),colaResponses(ARCHI_COLA_RESPONSES,LETRA_RESPONSES){
}

Cliente::~Cliente(){
	//TODO terminar server y clientes
}

void Cliente::consultarBaseDeDatos(char nombre[tamNombre], char direccion[tamDir], char telefono[tamTel]){
	armarRequest(nombre,direccion,telefono,true);

	imprimirRequest();
	const request requestToSend = req;
	colaRequests.escribir( requestToSend );

	colaResponses.leer(getpid(),&resp);
	imprimirRspuesta();
	// TODO hacer algo con lo que leyo....
}

void Cliente::escribirEnBaseDeDatos(char nombre[tamNombre], char direccion[tamDir], char telefono[tamTel]){
	armarRequest(nombre,direccion,telefono,false);

	imprimirRequest();
	const request requestToSend = req;
	colaRequests.escribir( requestToSend );
}

void Cliente::armarRequest(char nombre[tamNombre], char direccion[tamDir],char telefono[tamTel],bool leo){
	strncpy(req.nombre, nombre, tamNombre);
	strncpy(req.direccion, direccion, tamDir);
	strncpy(req.telefono, telefono, tamTel);
	req.leo = leo;
	req.mtype = getpid();
}

void Cliente::imprimirRequest(){
	cout << endl;
	cout << "Request enviada por el cliente: " << endl;
	cout << "Nombre: " << req.nombre << endl;
	cout << "Direccion: " << req.direccion << endl;
	cout << "Telefono: " << req.telefono << endl;
	cout << "Lectura: " << req.leo << endl;
	cout << "Tipo: " << req.mtype << endl << endl;
}

void Cliente::imprimirRspuesta(){
	cout << endl;
	cout << "Respuesta recibida por el cliente: " << endl;
	cout << "Nombre: " << resp.nombre << endl;
	cout << "Direccion: " << resp.direccion << endl;
	cout << "Telefono: " << resp.telefono << endl;
	cout << "Tipo: " << resp.mtype << endl << endl;
}














