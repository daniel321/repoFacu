#include "BaseDeDatos.h"
#include "../common/exception/ErrnoWrap.h"

BaseDeDatos::BaseDeDatos(const std::string &rutaArch) : vectorRegistros(), arch()
{
	std::ofstream(rutaArch.c_str(), std::fstream::out | std::fstream::app).close(); // Crear si no existe
	arch.open(rutaArch.c_str(),	std::fstream::out | std::fstream::in | std::fstream::binary | std::fstream::app);
	if (!arch.is_open() || arch.fail() || !arch.good()) throw Common::ErrnoWrap();
	cargarDeArchivo();
}

BaseDeDatos::~BaseDeDatos()
{
	arch.close();
}

void BaseDeDatos::cargarDeArchivo()
{
	arch.seekg(0, std::ios::beg);
	char buffer[tamTotal] = {0};
	arch.read(buffer, tamTotal);
	while (arch.good())
	{
		vectorRegistros.push_back(Registro(buffer));
		arch.read(buffer, tamTotal);
	}
	arch.clear();
	arch.seekg(0, std::ios::end);
}

std::vector<Registro> BaseDeDatos::buscar(const Registro &reg)
{
	std::vector<Registro> result;
	for (int i = 0; i < vectorRegistros.size(); ++i)
	{
		if (reg.getNombre() != "*" && reg.getNombre() != vectorRegistros[i].getNombre()) continue;
		if (reg.getDireccion() != "*" && reg.getDireccion() != vectorRegistros[i].getDireccion()) continue;
		if (reg.getTelefono() != "*" && reg.getTelefono() != vectorRegistros[i].getTelefono()) continue;
		result.push_back(vectorRegistros[i]);
	}
	return result;
}

void BaseDeDatos::guardar(const Registro &reg)
{
	if (buscar(reg).size() != 0) return;
	char* buffer = reg.serializar();
	arch.write(buffer, tamTotal);
	delete[] buffer;
	vectorRegistros.push_back(reg);
}

