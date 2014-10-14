#ifndef MEMCMPRAW_H_
#define MEMCMPRAW_H_

#include "../semaforos/Semaforo.h"

/**
 * Clase que modela memoria compartida
 * Nota importante, la clase funciona estilo smart pointer, si ningun proceso tiene referencia, se borra del OS
 * Asi que tener cuidado con cosas del estilo crearla con un proceso y luego cerrar ese proceso
 */
class MemCmpRaw
{

private:
	int shmId;
	void* ptrDatos;
	size_t tam;
	int cantidadProcesosAdosados() const;
	void crear ( const char* archivo,const char letra, const size_t tam );
	void liberar ();
public:
	MemCmpRaw ( const char*,const char letra, const size_t tam);
	MemCmpRaw ( const MemCmpRaw& origen );
	MemCmpRaw& operator= ( const MemCmpRaw& origen );
	~MemCmpRaw();

	/**
	 * Setea el valor del segmento de memoria a 0
	 */
	void reset();
	/**
	 * Escribe sobre la mem compartida a partir del offset tam bytes de la data
	 */
	void escribir (const int offset, void * data, size_t tam);
	/**
	 * Lee sobre la mem compartida a partir del offset tam bytes y los copia en dest.
	 */
	void leer (const int offset, void * dest, size_t tam) const;
};

#endif /* MEMCMPRAW_H_ */
