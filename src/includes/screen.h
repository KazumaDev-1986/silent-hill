#ifndef __AC_SCREEN_H__
#define __AC_SCREEN_H__

#include "config.h"

enum ScreenType { AC_VOID_SCREEN = 0, AC_MENU_SCREEN, AC_LEVEL_0_SCREEN };

struct Screen {
  struct List *objects;

  void (*updateScreen)(struct Screen *const);
  void (*drawScreen)(const struct Screen *const);

  enum ScreenType (*getScreenType)(void);
  enum ScreenType (*getNextScreenType)(void);
};

#if defined(__cplusplus)
extern "C" {
#endif

__AC__ struct Screen *createScreen(enum ScreenType type);
__AC__ void destroyScreen(struct Screen **const ptr);

// Menu Screen.
__AC__ struct Screen *createMenuScreen(void);
__AC__ void destroyMenuScreen(struct Screen **const ptr);

#if defined(__cplusplus)
}
#endif

#endif //__AC_SCREEN_H__
