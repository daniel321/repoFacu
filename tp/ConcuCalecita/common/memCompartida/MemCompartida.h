#ifndef MemoriaCompartida_H_
#define MemoriaCompartida_H_

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string>
#include <string.h>
#include <iostream>
#include <errno.h>
#include "../exception/ErrnoWrap.h"

/**
 * Clase que modela memoria compartida
 * Nota importante, la clase funciona estilo smart pointer, si ningun proceso tiene referencia, se borra del OS
 * Asi que tener cuidado con cosas del estilo crearla con un proceso y luego cerrar ese proceso
 */
template <class T> class MemoriaCompartida {

private:
	int shmId;
	T* ptrDatos;
	int cantidadProcesosAdosados() const;
public:
	MemoriaCompartida ();
	void crear ( const std::string& archivo,const char letra);
	MemoriaCompartida ( const std::string& archivo,const char letra );
	MemoriaCompartida ( const MemoriaCompartida& origen );
	~MemoriaCompartida ();
	MemoriaCompartida<T>& operator= ( const MemoriaCompartida& origen );
	void escribir ( const T& dato );
	T leer () const;
};

template <class T> MemoriaCompartida<T>::MemoriaCompartida ():shmId(0),ptrDatos(NULL) {
}

template <class T> void MemoriaCompartida<T>::crear ( const std::string& archivo,const char letra ) {
	key_t clave = ftok ( archivo.c_str(),letra );
	if (clave == -1) throw Common::ErrnoWrap();

	this->shmId = shmget ( clave,sizeof(T),0666|IPC_CREAT );
	if (this->shmId == -1) throw Common::ErrnoWrap();

	void* tmpPtr = shmat ( this->shmId,NULL,0 );
	if (tmpPtr == (void*) -1) throw Common::ErrnoWrap();

	this->ptrDatos = static_cast<T*> (tmpPtr);
}

template <class T> MemoriaCompartida<T>::MemoriaCompartida ( const std::string& archivo,const char letra ):shmId(0),ptrDatos(NULL) {
	crear(archivo, letra);
}

template <class T> MemoriaCompartida<T>::MemoriaCompartida ( const MemoriaCompartida& origen ):shmId(origen.shmId) {
	void* tmpPtr = shmat ( origen.shmId,NULL,0 );
	if ( tmpPtr == (void*) -1 ) throw Common::ErrnoWrap();
	this->ptrDatos = static_cast<T*> (tmpPtr);
}

template <class T> MemoriaCompartida<T>::~MemoriaCompartida () {
	int retorno = shmdt ( (void *) this->ptrDatos );
	if (retorno == -1) throw Common::ErrnoWrap();
	int procAdosados = this->cantidadProcesosAdosados ();
	if ( procAdosados == 0 ) {
		retorno = shmctl ( this->shmId,IPC_RMID,NULL );
		if (retorno == -1) throw Common::ErrnoWrap();
	}
}

template <class T> MemoriaCompartida<T>& MemoriaCompartida<T>::operator= ( const MemoriaCompartida& origen ) {
	this->shmId = origen.shmId;
	void* tmpPtr = shmat ( this->shmId,NULL,0 );
	if ( tmpPtr == (void*) -1 ) throw Common::ErrnoWrap();
	this->ptrDatos = static_cast<T*> (tmpPtr);
	return *this;
}

template <class T> void MemoriaCompartida<T>::escribir ( const T& dato ) {
	*(this->ptrDatos) = dato;
}

template <class T> T MemoriaCompartida<T>::leer() const {
	return *(this->ptrDatos);
}

template <class T> int MemoriaCompartida<T> :: cantidadProcesosAdosados () const {
	shmid_ds estado;
	int retorno = shmctl ( this->shmId,IPC_STAT,&estado );
	if (retorno == -1) throw Common::ErrnoWrap();
	return estado.shm_nattch;
}

#endif

