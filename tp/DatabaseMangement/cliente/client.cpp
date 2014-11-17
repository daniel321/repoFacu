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

void Cliente::consultarBaseDeDatos(const std::string &nombre, const std::string &direccion, const std::string &telefono){
	armarRequest(nombre,direccion,telefono,true);

	imprimirRequest();
	const request requestToSend = req;
	colaRequests.escribir( requestToSend );

	colaResponses.leer(getpid(),&resp);
	imprimirRspuesta();
	// TODO hacer algo con lo que leyo....
}

void Cliente::escribirEnBaseDeDatos(const std::string &nombre, const std::string &direccion, const std::string &telefono)
{
	armarRequest(nombre,direccion,telefono,false);

	imprimirRequest();
	const request requestToSend = req;
	colaRequests.escribir( requestToSend );
}

void Cliente::armarRequest(const std::string &nombre, const std::string &direccion, const std::string &telefono, bool leo)
{
	strncpy(req.reg.nombre, nombre.c_str(), tamNombre);
	strncpy(req.reg.direccion, direccion.c_str(), tamDir);
	strncpy(req.reg.telefono, telefono.c_str(), tamTel);
	req.leo = leo;
	req.mtype = getpid();
}

void Cliente::imprimirRequest(){
	cout << endl;
	cout << "Request enviada por el cliente: " << endl;
	cout << "Nombre: " << req.reg.nombre << endl;
	cout << "Direccion: " << req.reg.direccion << endl;
	cout << "Telefono: " << req.reg.telefono << endl;
	cout << "Lectura: " << req.leo << endl;
	cout << "Tipo: " << req.mtype << endl << endl;
}

void Cliente::imprimirRspuesta(){
	cout << endl;
	cout << "Respuesta recibida por el cliente: " << endl;
	cout << "Nombre: " << resp.reg.nombre << endl;
	cout << "Direccion: " << resp.reg.direccion << endl;
	cout << "Telefono: " << resp.reg.telefono << endl;
	cout << "Tipo: " << resp.mtype << endl << endl;
}














