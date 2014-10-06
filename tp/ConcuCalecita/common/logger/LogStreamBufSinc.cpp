#include "LogStreamBufSinc.h"
#include <sys/file.h>
#include <errno.h>
#include <string.h>
#include <stdexcept>

namespace Common
{

LogStreamBufSinc::LogStreamBufSinc(const char path[]) : LogStreamBuf(path) {}

int LogStreamBufSinc::sync ()
{
	int lockResult = ::flock(this->fileDescriptor, LOCK_EX);
	if (lockResult == -1) throw std::runtime_error(strerror(errno));
	LogStreamBuf::sync();
	lockResult = ::flock(this->fileDescriptor, LOCK_UN);
	if (lockResult == -1) throw std::runtime_error(strerror(errno));
	return 0;
}

} /* namespace Common */
