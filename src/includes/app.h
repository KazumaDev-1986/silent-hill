#ifndef __AC_APP_H__
#define __AC_APP_H__

#include "config.h"
#include "screen.h"

struct App {
  bool live;
  struct Screen *currentScreen;
};

#if defined(__cplusplus)
extern "C" {
#endif

__AC__ struct App *createApp(void);

__AC__ void runApp(struct App *const app);

__AC__ void destroyApp(struct App **const ptr);

#if defined(__cplusplus)
}
#endif

#endif // __AC_APP_H__
