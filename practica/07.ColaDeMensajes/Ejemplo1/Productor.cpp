#include "Productor.h"

Productor :: Productor ( const std::string& nombre ) : nombre(nombre) {
}

Productor :: ~Productor () {
}

void Productor :: producir ( const std::vector<Cola<producto>*>& colas,const int vueltas ) const {

	producto prod;
	prod.mtype = TIPO_PRODUCTO;

	for ( int j=0;j<vueltas;j++ ) {
		sleep ( 5 );
		prod.numeroRandom = this->calcularRandom ();

		std::vector<Cola<producto>*>::const_iterator it;

		for ( it=colas.begin();it!=colas.end();it++ ) {
			int resultado = (*it)->escribir ( prod );

			if ( resultado < 0 )
				std::cout << "Error de escritura en la cola: " << strerror(errno) << std::endl;
			else
				std::cout << "El productor [" << this->nombre << "] produce " << prod.numeroRandom << std::endl;
		}
	}
}

int Productor :: calcularRandom () const {
	srand ( time(NULL) );
	int resultado = rand() % 100;
	return resultado;
}
