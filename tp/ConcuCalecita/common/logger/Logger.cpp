#include "Logger.h"

namespace Common
{

Logger::Logger(Common::LogStreamBuf * buffer) : std::ostream(buffer), buffer(buffer) {}

Logger::~Logger()
{
	if (buffer != 0) delete buffer;
}

} /* namespace Common */

