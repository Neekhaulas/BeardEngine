#ifndef __PLATEFORM_H
#define __PLATEFORM_H

#ifdef _MSC_VER

#include <io.h>

#define open _open
#define write _write
#define read _read
#define close _close

#define vsprintf vsprintf_s
#define sprintf sprintf_s

#endif

#endif