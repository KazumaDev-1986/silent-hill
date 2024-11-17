#include "includes/screen.h"
#include <stdlib.h>

//----------------------------------------------------------------------------------
// Internal function declaration.
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
// Public function definition.
//----------------------------------------------------------------------------------

__AC__ struct Screen *createScreen(enum ScreenType type) {
  struct Screen *screen = NULL;

  switch (type) {
  case AC_MENU_SCREEN:
    screen = createMenuScreen();
    break;
  case AC_LEVEL_0_SCREEN:
    screen = createLevel0Screen();
    break;
  default:
    break;
  }

  return screen;
}
__AC__ void destroyScreen(struct Screen **const ptr) {
  switch ((*ptr)->getScreenType()) {
  case AC_MENU_SCREEN:
    destroyMenuScreen(ptr);
    break;
  case AC_LEVEL_0_SCREEN:
    destroyLevel0Screen(ptr);
    break;
  default:
    break;
  }
}
//----------------------------------------------------------------------------------
// Internal function definition.
//----------------------------------------------------------------------------------
