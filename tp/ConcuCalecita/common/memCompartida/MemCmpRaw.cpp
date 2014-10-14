#include "MemCmpRaw.h"

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "../exception/ErrnoWrap.h"
#include <cstring> //memcpy

MemCmpRaw::MemCmpRaw (const char* archivo, const char letra, const size_t tam)
	: shmId(0),ptrDatos(NULL)
{
	crear(archivo, letra, tam);
	this->tam = tam;
}

void MemCmpRaw::crear ( const char* archivo,const char letra, const size_t tam )
{
	this->tam = tam;
	key_t clave = ftok ( archivo,letra );
	if (clave == -1) throw Common::ErrnoWrap();

	this->shmId = shmget ( clave, tam, 0666 | IPC_CREAT );
	if (this->shmId == -1) throw Common::ErrnoWrap();

	this->ptrDatos = shmat ( this->shmId,NULL,0 );
	if (this->ptrDatos == (void*) -1) throw Common::ErrnoWrap();

}

MemCmpRaw::MemCmpRaw ( const MemCmpRaw& origen ) : shmId(origen.shmId) {
	this->ptrDatos = shmat ( origen.shmId,NULL,0 );
	if ( this->ptrDatos == (void*) -1 ) throw Common::ErrnoWrap();
}

MemCmpRaw::~MemCmpRaw ()
{
	int retorno = shmdt ( (void *) this->ptrDatos );
	if (retorno == -1) throw Common::ErrnoWrap();
	int procAdosados = this->cantidadProcesosAdosados ();
	if ( procAdosados == 0 ) {
		retorno = shmctl ( this->shmId,IPC_RMID,NULL );
		if (retorno == -1) throw Common::ErrnoWrap();
	}
}

MemCmpRaw& MemCmpRaw::operator= ( const MemCmpRaw& origen ) {
	this->shmId = origen.shmId;
	this->ptrDatos  = shmat ( this->shmId,NULL,0 );
	if ( this->ptrDatos == (void*) -1 ) throw Common::ErrnoWrap();
	return *this;
}

void MemCmpRaw::escribir (const int offset, void * data, size_t tam)
{
	memcpy(this->ptrDatos+offset, data, tam);
}

void MemCmpRaw::leer (const int offset, void * dest, size_t tam) const
{
	memcpy(dest,this->ptrDatos+offset,tam);
}

void MemCmpRaw::reset ()
{
	memset(this->ptrDatos,0,tam);
}

int MemCmpRaw::cantidadProcesosAdosados () const {
	shmid_ds estado;
	int retorno = shmctl ( this->shmId,IPC_STAT,&estado );
	if (retorno == -1) throw Common::ErrnoWrap();
	return estado.shm_nattch;
}
