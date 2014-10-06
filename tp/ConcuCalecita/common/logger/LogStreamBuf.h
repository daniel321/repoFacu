#ifndef LOGSTREAMBUF_H_
#define LOGSTREAMBUF_H_

#include <sstream>

namespace Common
{

/**
 * Buffer utilizado por el logger
 */
class LogStreamBuf : public std::stringbuf
{
	public:
		LogStreamBuf(const char* path);
		virtual ~LogStreamBuf();
		/**
		 * Función que efectivamente realiza el flusheo de datos, es llamada por el ostream
		 */
		virtual int sync ();
	protected:
		int fileDescriptor;
	private:
		/**
		 * Devuelve un string con el timestamp actual en formato humanamente legible
		 */
		std::string timestamp();
};

} /* namespace Common */
#endif /* LOGSTREAMBUF_H_ */
