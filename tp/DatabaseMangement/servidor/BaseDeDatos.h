#ifndef BASEDEDATOS_H_
#define BASEDEDATOS_H_

#include <fstream>
#include <vector>
#include "../common/Registro.h"

class BaseDeDatos
{
private:
	std::fstream arch;
	std::vector<Registro> vectorRegistros;
	void cargarDeArchivo();
public:
	BaseDeDatos(const std::string &rutaArch); // Se carga del archivo al instanciar
	~BaseDeDatos();

	/**
	 * Usa un registro para buscar registros matcheantes
	 * Para campos cuales quiera usar *s
	 * @return Lista de registros matcheantes
	 */
	std::vector<Registro> buscar(const Registro &reg);

	/**
	 * Guarda el registro si no existe en la bd
	 * Tira una excepcion si alguno de los campos del registro es *
	 * Ademas persiste el registro en el archivo
	 */
	void guardar(const Registro &reg);
};

#endif /* BASEDEDATOS_H_ */
