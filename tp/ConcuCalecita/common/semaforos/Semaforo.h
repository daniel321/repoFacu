#ifndef SEMAFORO_H_
#define SEMAFORO_H_

#include <string>

class Semaforo {

private:
	int id;
	int cantidad;
public:
	Semaforo ( const std::string& nombre, const char projId, const int cantidad);
	void inicializar (const int val) const;
	void wait (const int num) const;
	void signal (const int num) const;
	 /**
	  * Elimina el set de semaforos a nivel OS
	  */
	void eliminar () const;
};

#endif /* SEMAFORO_H_ */
