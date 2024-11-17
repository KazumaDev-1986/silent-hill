#ifndef __AC_UTIL__
#define __AC_UTIL__

#include "config.h"

__AC__ struct List {
  void *value;
  struct List *next;
};

#if defined(__cplusplus)
extern "C" {
#endif

// List functions.
__AC__ void addElementList(struct List **list, void *value);
__AC__ void clearList(struct List **const ptr);

#if defined(__cplusplus)
}
#endif

#endif //__AC_UTIL__
