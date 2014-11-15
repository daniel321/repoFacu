#include "Consumidor.h"

Consumidor :: Consumidor ( const std::string& nombre ) : nombre(nombre) {
	std::cout << "Consumidor [" << this->nombre << "] creado con process id = " << getpid () << std::endl;
}

Consumidor :: ~Consumidor () {
}

void Consumidor :: consumir ( const Cola<producto>& cola,const int vueltas ) const {

	for ( int i=0;i<vueltas;i++ ) {
		sleep ( 1 );

		// se lee el producto de la cola
		producto prod;
		int resultado = cola.leer ( TIPO_PRODUCTO,&prod );

		if ( resultado < 0 )
			std::cout << "Error de lectura en la cola: " << strerror(errno) << std::endl;
		else
			std::cout << "El consumidor [" << this->nombre << "] lee el producto " << prod.numeroRandom << std::endl;
	}

}
