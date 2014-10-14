#ifndef ASIENTOS_H_
#define ASIENTOS_H_

#include <vector>
#include "../common/memCompartida/MemCompartida.h"
#include "../common/memCompartida/MemCmpRaw.h"
#include "../common/semaforos/Semaforo.h"
#include "../common/logger/Logger.h"

class Asientos
{
private:
	MemoriaCompartida<int> totalAsientos;
	MemCmpRaw asientos;
	std::vector<Semaforo> semaforos;
	void cargarSemaforos();
	void inicializarSemaforos();
public:
	/**
	 * Constructor a ser llamado solo por el proceso inicializador de la clase
	 * @param totalAsientos	Total de asientos
	 */
	Asientos(int totalAsientos);
	/**
	 * Constructor a ser llamado por los clientes que quieran sentarse
	 */
	Asientos();
	/**
	 * Hace que un cliente se sient en un asiento
	 * La politica es intentar un asiento al azar y si esta ocupado iterar hacia la derecha circularmente
	 * @param pid	Pid del cliente
	 * @param log	Puntero a un logger si es que se desea loggear
	 */
	void sentarse(int pid, Common::Logger* log);
	/**
	 * Pone todos los asientos como libres.
	 */
	void reset();
	/**
	 * Elimina todos los recursos asociados al SO
	 */
	void liberar();

};

#endif /* ASIENTOS_H_ */
