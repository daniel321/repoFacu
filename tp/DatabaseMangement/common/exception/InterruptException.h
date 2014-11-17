#ifndef INTERRUPTEXCEPTION_H_
#define INTERRUPTEXCEPTION_H_

#include <exception>

namespace Common
{

/**
 * Clase para una excepcion que simboliza una interrupción
 */
class InterruptException : public std::exception
{

};

} /* namespace Common */
#endif /* INTERRUPTEXCEPTION_H_ */
