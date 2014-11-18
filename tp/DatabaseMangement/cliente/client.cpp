#include "client.h"

#include <iostream>			// std::cout
#include <unistd.h>			// getpid
#include <string.h>			// strncpy

Cliente::Cliente():colaRequests(ARCHI_COLA_REQUESTS,LETRA_REQUESTS),colaResponses(ARCHI_COLA_RESPONSES,LETRA_RESPONSES){
}

Cliente::~Cliente()
{
}

void Cliente::consultarBaseDeDatos(const std::string &nombre, const std::string &direccion, const std::string &telefono)
{
	colaRequests.escribir( armarRequest(nombre,direccion,telefono,true) );
	respInicial cantidadDeMatches;
	colaResponses.leer(getpid(), &cantidadDeMatches);
	std::cout << cantidadDeMatches.matches << " matches." << std::endl;
	for(int i=0 ; i < cantidadDeMatches.matches; ++i )
	{
		response r;
		colaResponses.leer(getpid(),&r);
		std::cout << Registro(r.reg) << std::endl;
	}
}

void Cliente::escribirEnBaseDeDatos(const std::string &nombre, const std::string &direccion, const std::string &telefono)
{
	colaRequests.escribir( armarRequest(nombre,direccion,telefono,false) );
}

request Cliente::armarRequest(const std::string &nombre, const std::string &direccion, const std::string &telefono, bool leo)
{
	request req;
	strncpy(req.reg.nombre, nombre.c_str(), tamNombre);
	strncpy(req.reg.direccion, direccion.c_str(), tamDir);
	strncpy(req.reg.telefono, telefono.c_str(), tamTel);
	req.leo = leo;
	req.mtype = getpid();
	return req;
}

/*
void Cliente::imprimirRequest(){
	std::cout << std::endl;
	std::cout << "Request enviada por el cliente: " << std::endl;
	std::cout << "Nombre: " << req.reg.nombre << std::endl;
	std::cout << "Direccion: " << req.reg.direccion << std::endl;
	std::cout << "Telefono: " << req.reg.telefono << std::endl;
	std::cout << "Lectura: " << req.leo << std::endl;
	std::cout << "Tipo: " << req.mtype << std::endl << std::endl;
}

void Cliente::imprimirRspuesta(int i)
{
	std::cout << std::endl;
	std::cout << "Respuesta recibida por el cliente: " << std::endl;
	std::cout << "Nombre: " << resp[i].reg.nombre << std::endl;
	std::cout << "Direccion: " << resp[i].reg.direccion << std::endl;
	std::cout << "Telefono: " << resp[i].reg.telefono << std::endl;
	std::cout << "Tipo: " << resp[i].mtype << std::endl << std::endl;
}

void Cliente::imprimirRspuestas(){
	int matches = cantidadDeMatches.matches;

	std::cout << "Cantidad de respuestas recibidas por el cliente: " << matches << std::endl;

	if(matches != resp.size())
		std::cout << "ERROR : RESPUESTAS MAL SETEADAS " << std::endl;

	for(int i=0; i<matches && i<resp.size() ; i++)
		imprimirRspuesta(i);
}
*/











