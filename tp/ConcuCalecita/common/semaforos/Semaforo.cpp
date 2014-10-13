#include "Semaforo.h"

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "../exception/ErrnoWrap.h"

union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO (Linux-specific) */
};

Semaforo :: Semaforo (const std::string& nombre, const char projId, const int cantidad, const int valorInicial)
	: cantidad(cantidad)
{
	key_t clave = ftok ( nombre.c_str(), projId);
	if (clave == -1) throw Common::ErrnoWrap();
	this->id = semget ( clave, cantidad, 0666 | IPC_CREAT );
}

void Semaforo :: inicializar (const int val) const
{
	semun init;
	init.val = val;
	for (int i = 0; i < cantidad; ++i)
	{
		int resultado = semctl ( this->id, i,SETVAL,init );
		if (resultado == -1) throw Common::ErrnoWrap();
	}
}

void Semaforo :: wait (const int num) const {

	struct sembuf operacion;

	operacion.sem_num = num;	// numero de semaforo
	operacion.sem_op  = -1;	// restar 1 al semaforo
	//operacion.sem_flg = SEM_UNDO;

	int resultado = semop ( this->id,&operacion, 1 );
	if (resultado == -1) throw Common::ErrnoWrap();
}

void Semaforo :: signal (const int num) const {

	struct sembuf operacion;

	operacion.sem_num = num;	// numero de semaforo
	operacion.sem_op  = 1;	// sumar 1 al semaforo
	//operacion.sem_flg = SEM_UNDO;

	int resultado = semop ( this->id,&operacion, 1 );
	if (resultado == -1) throw Common::ErrnoWrap();
}

void Semaforo :: eliminar () const {
	semctl ( this->id,0,IPC_RMID );
}
