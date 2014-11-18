#ifndef REGISTRO_H_
#define REGISTRO_H_

#include <ostream>

static const int tamNombre = 61;
static const int tamDir = 120;
static const int tamTel = 13;
static const int tamTotal = tamNombre+tamDir+tamTel;

struct registro{
	char nombre[tamNombre];
	char direccion[tamDir];
	char telefono[tamTel];
};

class Registro
{
	private:
		struct registro reg;
	public:
		/**
		 * Constructor por copia de struct
		 */
		Registro(struct registro &reg);
		/**
		 * Constructor explicito
		 */
		Registro(const std::string &nombre, const std::string &direccion, const std::string telefono);
		/**
		 * Constructor por deserialización
		 */
		Registro(const char aDeserializar[tamTotal]);
		/**
		 * Serializa y devuelve el struct registro de forma serializada
		 * Notar que el char* devuelto debe ser eliminado con delete[]
		 */
		char* serializar() const;
		/**
		 * Devuelve el struct registro subyacente
		 */
		struct registro& getRegistro();
		/**
		 * Getters como string
		 */
		std::string getNombre() const;
		std::string getDireccion() const;
		std::string getTelefono() const;
		/**
		 * Para imprimir a ostream
		 */
		friend std::ostream& operator<<(std::ostream& os, const Registro& reg);
};

#endif /* REGISTRO_H_ */
