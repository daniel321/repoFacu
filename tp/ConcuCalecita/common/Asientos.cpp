#include "Asientos.h"
#include <cstdlib>

static const char* pathFtokContadorLugares = "client.exe";
static const char* pathFtokAsientos = "calesita.exe";
static const int semaforosPorBache = 24;
static const int tamBytesAsiento = sizeof(bool);

Asientos::Asientos(int totalAsientos) : totalAsientos(pathFtokContadorLugares, 'a'),
		asientos(pathFtokAsientos, 'a', totalAsientos*tamBytesAsiento), semaforos()
{
	this->totalAsientos.escribir(totalAsientos);
	cargarSemaforos();
	inicializarSemaforos();
}

Asientos::Asientos() : totalAsientos(pathFtokContadorLugares, 'a'),
		asientos(pathFtokAsientos, 'a', totalAsientos.leer()*tamBytesAsiento), semaforos()
{
	cargarSemaforos();
}

void Asientos::cargarSemaforos()
{
	int baches = totalAsientos.leer() / semaforosPorBache;
	for (int i = 0; i <= baches; ++i)
	{
		semaforos.push_back(Semaforo(pathFtokAsientos, 'a'+i, semaforosPorBache));
	}
}

void Asientos::inicializarSemaforos()
{
	for (int i = 0; i < semaforos.size(); ++i)
	{
		semaforos[i].inicializar(1);
	}
}

void Asientos::liberar()
{
	for (int i = 0; i < semaforos.size(); ++i)
	{
		semaforos[i].eliminar();
	} // La memoria compartida se libera sola
}

void Asientos::reset()
{
	asientos.reset();
}

int Asientos::getOcupados()
{
	int contador = 0;
	for (int i = 0; i < totalAsientos.leer(); ++i)
	{
		bool estaOcupado = false;
		asientos.leer(i*sizeof(bool), &estaOcupado, sizeof(bool));
		if (estaOcupado) ++contador;
	}
	return contador;
}

void Asientos::sentarse(int pid, std::ostream *log)
{
	srand(pid);
	int t = totalAsientos.leer();
	int posibleAsiento = rand() % totalAsientos.leer();
	bool sePudoSentar = false;
	while (!sePudoSentar)
	{
		if (log != 0) *log << "Cliente " << pid << " intentando sentarse en el asiento " << posibleAsiento << std::endl;
		int bache = posibleAsiento / semaforosPorBache;
		semaforos[bache].wait(posibleAsiento % semaforosPorBache);
		bool estaOcupado;
		asientos.leer(posibleAsiento*sizeof(bool), &estaOcupado, sizeof(bool));
		if (!estaOcupado)
		{
			estaOcupado = true;
			asientos.escribir(posibleAsiento*sizeof(bool), &estaOcupado, sizeof(bool));
			sePudoSentar = true;
		}
		semaforos[bache].signal(posibleAsiento % semaforosPorBache);
		if (log != 0 && sePudoSentar) *log << "Cliente " << pid << " se sento en el asiento " << posibleAsiento << std::endl;
		posibleAsiento = (posibleAsiento+1) % totalAsientos.leer();
	}
}
