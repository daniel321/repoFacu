#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include "LogStreamBuf.h"

namespace Common
{

/**
 * Logger simple a archivo con interface de ostream
 */
class Logger : public std::ostream
{
	private:
		Common::LogStreamBuf buffer;
	public:
		Logger(const char path[]);
		virtual ~Logger();
};

} /* namespace Common */
#endif /* LOGGER_H_ */
