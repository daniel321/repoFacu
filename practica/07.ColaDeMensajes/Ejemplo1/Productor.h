#ifndef PRODUCTOR_H_
#define PRODUCTOR_H_

#include <string>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <errno.h>
#include <unistd.h>
#include <vector>

#include "../Cola.h"
#include "Producto.h"


class Productor {
	private:
		std::string nombre;
		int calcularRandom () const;

	public:
		Productor ( const std::string& nombre );
		~Productor ();
		void producir ( const std::vector<Cola<producto>*>& colas,const int vueltas ) const;
};

#endif /* PRODUCTOR_H_ */
