#ifdef EJEMPLO_1

#include <unistd.h>
#include <errno.h>
#include <sstream>
#include <string>
#include <vector>

#include "Cola.h"
#include "Ejemplo1/Productor.h"
#include "Ejemplo1/Consumidor.h"
#include "Ejemplo1/Producto.h"


int main () {

	static const int CANTIDAD_CONSUMIDORES = 3;
	static const int VUELTAS = 3;
	static const std::string ARCHIVO = "main1.cc";

	for ( int i=0;i<CANTIDAD_CONSUMIDORES;i++ ) {

		int pid = fork ();

		if ( pid == 0 ) {
			std::stringstream nombre;
			nombre << "Consumidor " << (i+1);

			Cola<producto> cola ( ARCHIVO,i );

			Consumidor consumidor ( nombre.str() );
			consumidor.consumir ( cola,VUELTAS );
			return 0;
		}
	}

	std::vector<Cola<producto>*> colas;

	for ( int i=0;i<CANTIDAD_CONSUMIDORES;i++ ) {
		colas.push_back ( new Cola<producto>(ARCHIVO,i) );
	}

	Productor productor ( "Productor" );
	productor.producir ( colas,VUELTAS );

	for ( int i=0;i<CANTIDAD_CONSUMIDORES;i++ ) {
		int resultado = colas[i]->destruir();

		if ( resultado < 0 )
			perror ( strerror(errno) );

		delete ( colas[i] );
	}

	return 0;
}

#endif
