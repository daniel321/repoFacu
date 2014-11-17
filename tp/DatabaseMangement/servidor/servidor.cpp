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
				int cantMatches = leerDeLaBaseDeDatos();

				enviarRespuestas(cantMatches,pid);
				imprimirRspuestas();
			}else{
				escribirEnLaBaseDeDatos();
			}
		}
	}while(atendiendo);
}


void Servidor::enviarRespuestas(int cantMatches,int pid){
	armarCantDeMatches(cantMatches,pid);
	colaResponses.escribir( cantidadDeMatches );

	int matches = cantidadDeMatches.matches;
	for(int i=0; i<matches && i<resp.size() ; i++){
		const response responseToSend = resp[i];
		colaResponses.escribir( responseToSend );
	}
}

void Servidor::pararDeAtender(){
	atendiendo = false;
}

int Servidor::leerDeLaBaseDeDatos(){
	int pid = req.mtype;
	resp.clear(); // borro respuesta vieja


	armarRespuestaDummy(pid);
	armarRespuestaDummy(pid);
	armarRespuestaDummy(pid);
	//TODO leer de la base de datos y guardar campos en "resp" y retornar la cant de respuestas

	return 3;
}

void Servidor::escribirEnLaBaseDeDatos(){
	//TODO escribir en la base de datos a partir de "req"
	//TODO imprimir algo o indicar que se escribio bien
}

void Servidor::armarRespuestaDummy(long mtype){
	response r;

	strncpy(r.nombre, NOMBRE_DUMMY, tamNombre);
	strncpy(r.direccion, DIR_DUMMY, tamDir);
	strncpy(r.telefono, TEL_DUMMY, tamTel);
	r.mtype = mtype;

	resp.push_back(r);
}

void Servidor::armarRespuesta(char nombre[tamNombre], char direccion[tamDir], char telefono[tamTel],long mtype){
	response r;	

	strncpy(r.nombre, nombre, tamNombre);
	strncpy(r.direccion, direccion, tamDir);
	strncpy(r.telefono, telefono, tamTel);
	r.mtype = mtype;

	resp.push_back(r);
}

void Servidor::armarCantDeMatches(int matches,long mtype){
	cantidadDeMatches.mtype = mtype;
	cantidadDeMatches.matches = matches;
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

void Servidor::imprimirRspuestas(){
	int matches = cantidadDeMatches.matches;

	cout << "Cantidad de respuestas enviadas por el server : " << matches << endl;

	if(matches != resp.size())
		cout << "ERROR : RESPUESTAS MAL SETEADAS " << endl;
	
	for(int i=0; i<matches && i<resp.size() ; i++)
		imprimirRspuesta(i);
}

void Servidor::imprimirRspuesta(int i){
	cout << endl;
	cout << "Respuesta " << i << " : " << endl;
	cout << "Nombre: " << resp[i].nombre << endl;
	cout << "Direccion: " << resp[i].direccion << endl;
	cout << "Telefono: " << resp[i].telefono << endl;
	cout << "Tipo: " << resp[i].mtype << endl << endl;
}







