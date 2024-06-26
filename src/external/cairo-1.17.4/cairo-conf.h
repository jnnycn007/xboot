#ifndef __CAIRO_CONF_H__
#define __CAIRO_CONF_H__

#include <xboot.h>

#undef likely
#undef unlikely

#if defined(__BIG_ENDIAN)
# define WORDS_BIGENDIAN		(1)
#endif

#define CAIRO_NO_MUTEX			(1)
#define HAVE_UINT64_T			(1)
#define HAVE_STDINT_H			(1)
#define HAVE_LOCALTIME_R		(1)
#define HAVE_GMTIME_R			(1)
#define HAVE_CTIME_R			(1)

#endif /* __CAIRO_CONF_H__ */


