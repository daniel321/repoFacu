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

	colaResponses.leer(getpid(),&cantidadDeMatches);

	int matches = cantidadDeMatches.matches;
	for(int i=0 ; i<matches ; i++ ){
		response r;
		colaResponses.leer(getpid(),&r);  // considerar ir guardandolos en una lista o algo
		resp.push_back(r);
	}

	imprimirRspuestas();
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

void Cliente::imprimirRspuesta(int i){
	cout << endl;
	cout << "Respuesta " << i << " : " << endl;
	cout << "Nombre: " << resp[i].nombre << endl;
	cout << "Direccion: " << resp[i].direccion << endl;
	cout << "Telefono: " << resp[i].telefono << endl;
	cout << "Tipo: " << resp[i].mtype << endl << endl;
}

void Cliente::imprimirRspuestas(){
	int matches = cantidadDeMatches.matches;

	cout << "Cantidad de respuestas recibidas por el cliente: " << matches << endl;

	if(matches != resp.size())
		cout << "ERROR : RESPUESTAS MAL SETEADAS " << endl;

	for(int i=0; i<matches && i<resp.size() ; i++)
		imprimirRspuesta(i);
}












