#ifdef EJEMPLO_2

#include <iostream>
#include <sstream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "Ejemplo2/Cliente.h"
#include "Ejemplo2/Servidor.h"
#include "Ejemplo2/Mensajes.h"

using namespace std;

int main () {

	static const int CANTIDAD_INTERCAMBIOS = 3;

	int processId = fork ();

	if ( processId == 0 ) {

		// servidor
		Servidor servidor ( "main2.cc",'a' );

		for ( int i=0;i<CANTIDAD_INTERCAMBIOS;i++ ) {
			cout << "Servidor: esperando peticiones" << endl;
			servidor.recibirPeticion ();
			cout << "Servidor: peticion recibida: " << servidor.getPeticionRecibida().texto << endl;
			servidor.procesarPeticion ();
			cout << "Servidor: peticion procesada - enviando respuesta: " << servidor.getRespuesta().texto << endl;
			servidor.responderPeticion ();
			cout << "Servidor: respuesta enviada" << endl << endl;
		}

		return 0;

	} else {

		// cliente
		Cliente cliente ( "main2.cc",'a' );

		for ( int i=0;i<CANTIDAD_INTERCAMBIOS;i++ ) {
			cin.get ();

			// se arma el texto del mensaje
			std::stringstream peticion;
			peticion << "Peticion " << (i+1) << " del cliente";

			// se envia el mensaje al servidor
			mensaje rta = cliente.enviarPeticion ( i+1,peticion.str() );
			cout << "Cliente: respuesta recibida = (ID = " << rta.id << ") - " << rta.texto << endl;
		}

		wait ( NULL );

		return 0;
	}
}

#endif

