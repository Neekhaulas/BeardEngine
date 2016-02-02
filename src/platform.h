#ifndef __PLATEFORM_H
#define __PLATEFORM_H

#ifdef _MSC_VER

#include <io.h>

#define open _open
#define write _write
#define read _read
#define close _close

#define O_BINARY _O_BINARY
#define O_RDONLY _O_RDONLY

#define vsprintf vsprintf_s
#define sprintf sprintf_s

#else
#define O_BINARY 0
#endif

#endif
