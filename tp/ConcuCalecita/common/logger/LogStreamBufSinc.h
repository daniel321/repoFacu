#ifndef LOGSTREAMBUFSINC_H_
#define LOGSTREAMBUFSINC_H_

#include "LogStreamBuf.h"

namespace Common
{

class LogStreamBufSinc: public Common::LogStreamBuf
{
	public:
		LogStreamBufSinc(const char path[]);
		virtual int sync ();
};

} /* namespace common */
#endif /* LOGSTREAMBUFSINC_H_ */
