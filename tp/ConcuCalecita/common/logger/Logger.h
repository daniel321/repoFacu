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
	protected:
		Common::LogStreamBuf* buffer;
		Logger();
	public:
		Logger(Common::LogStreamBuf * buffer);
		virtual ~Logger();
};

} /* namespace Common */
#endif /* LOGGER_H_ */
