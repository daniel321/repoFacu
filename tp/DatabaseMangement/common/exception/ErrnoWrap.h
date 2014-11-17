#ifndef ERRNOWRAP_H_
#define ERRNOWRAP_H_

#include <stdexcept>

namespace Common
{

class ErrnoWrap: public std::exception
{
public:
	ErrnoWrap();
	ErrnoWrap(const char* mensaje);
	virtual ~ErrnoWrap() throw();
	virtual const char* what() const throw();
private:
	char* mensaje; // Se usa un c-str por error de "looser throw specifier"
};

} /* namespace Common */
#endif /* ERRNOWRAP_H_ */
