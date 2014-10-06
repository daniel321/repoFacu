#include "Logger.h"

namespace Common
{

Logger::Logger(const char path[]) : std::ostream(&buffer),buffer(path) {}

Logger::~Logger() {}

} /* namespace Common */

