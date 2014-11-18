#include "Registro.h"
#include <stdexcept>
#include <cstring>

Registro::Registro(struct registro &reg) : reg()
{
	strcpy(this->reg.nombre, reg.nombre);
	strcpy(this->reg.direccion, reg.direccion);
	strcpy(this->reg.telefono, reg.telefono);
}

Registro::Registro(const std::string &nombre, const std::string &direccion, const std::string telefono)
	: reg()
{
	if (nombre.length() > tamNombre+1) throw std::length_error("Nombre de largo demasiado extenso.");
	if (direccion.length() > tamDir+1) throw std::length_error("Direccion de largo demasiado extenso.");
	if (telefono.length() > tamTel+1) throw std::length_error("Telefono de largo demasiado extenso.");
	strcpy(this->reg.nombre, nombre.c_str());
	strcpy(this->reg.direccion, direccion.c_str());
	strcpy(this->reg.telefono, telefono.c_str());
}

Registro::Registro(const char aDeserializar[tamTotal]) : reg()
{
	strncpy(this->reg.nombre, aDeserializar, tamNombre);
	strncpy(this->reg.direccion, aDeserializar+tamNombre, tamDir);
	strncpy(this->reg.telefono, aDeserializar+tamNombre+tamTel, tamTel);
}

struct registro& Registro::getRegistro()
{
	return this->reg;
}

char* Registro::serializar() const
{
	char *result = new char[tamTotal](); // Aparentemente poner () hace que inicialize en 0 la mem
	strncpy(result, this->reg.nombre, strlen(this->reg.nombre));
	strncpy(result+tamNombre, this->reg.direccion, strlen(this->reg.direccion));
	strncpy(result+tamNombre+tamTel, this->reg.telefono, strlen(this->reg.direccion));
	return result;
}

std::string Registro::getNombre() const
{
	return std::string(reg.nombre);
}

std::string Registro::getDireccion() const
{
	return std::string(reg.direccion);
}

std::string Registro::getTelefono() const
{
	return std::string(reg.telefono);
}

std::ostream& operator<<(std::ostream& os, const Registro& reg)
{
    os << reg.reg.nombre <<	" - " << reg.reg.direccion << " - " << reg.reg.telefono;
    return os;
}



