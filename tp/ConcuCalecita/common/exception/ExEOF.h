#ifndef EXEOF_H_
#define EXEOF_H_

#include <exception>

namespace Common
{

/**
 * Clase para una excepcion que simboliza un fin de archivo (generalmente por cerrar un lado de un fifo)
 */
class ExEOF : public std::exception
{

};

} /* namespace Common */

#endif /* EXEOF_H_ */
