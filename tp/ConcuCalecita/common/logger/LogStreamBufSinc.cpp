#include "LogStreamBufSinc.h"
#include <sys/file.h>

#include "../exception/ErrnoWrap.h"

namespace Common
{

LogStreamBufSinc::LogStreamBufSinc(const char path[]) : LogStreamBuf(path) {}

int LogStreamBufSinc::sync ()
{
	int lockResult = ::flock(this->fileDescriptor, LOCK_EX);
	if (lockResult == -1) throw ErrnoWrap();
	LogStreamBuf::sync();
	lockResult = ::flock(this->fileDescriptor, LOCK_UN);
	if (lockResult == -1) throw ErrnoWrap();
	return 0;
}

} /* namespace Common */
