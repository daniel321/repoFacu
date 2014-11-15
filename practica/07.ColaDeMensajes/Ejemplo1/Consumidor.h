#ifndef CONSUMIDOR_H_
#define CONSUMIDOR_H_

#include <string>
#include <string.h>
#include <iostream>
#include <errno.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>

#include "../Cola.h"
#include "Producto.h"


class Consumidor {
	private:
		std::string nombre;

	public:
		Consumidor ( const std::string& nombre );
		~Consumidor ();
		void consumir ( const Cola<producto>& cola,const int vueltas ) const;
};

#endif /* CONSUMIDOR_H_ */
