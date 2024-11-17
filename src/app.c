#include "includes/app.h"
#include "includes/config.h"
#include "includes/error.h"
#include "includes/raylib.h"
#include "includes/screen.h"
#include <stdlib.h>

//----------------------------------------------------------------------------------
// Internal function declaration.
//----------------------------------------------------------------------------------
#if defined(__cplusplus)
extern "C" {
#endif

__AC__ static void _initApp(void);
__AC__ static void _destroyApp(struct App *const app);
__AC__ static void _updateApp(struct App *app);
__AC__ static void _drawApp(const struct App *const app);

#if defined(__cplusplus)
}
#endif

//----------------------------------------------------------------------------------
// Public function definition.
//----------------------------------------------------------------------------------
__AC__ struct App *createApp(void) {
  struct App *app = (struct App *)malloc(sizeof(struct App));
  if (!app) {
    printError("createApp failed");
    return NULL;
  }

  app->live = true;
  app->currentScreen = createLevel0Screen();
  if (!app->currentScreen) {
    free(app);
    app = NULL;
    return NULL;
  }

  _initApp();
  return app;
}

__AC__ void runApp(struct App *const app) {
  while (!WindowShouldClose()) {
    _updateApp(app);
    _drawApp(app);
  }
}

__AC__ void destroyApp(struct App **const ptr) {
  if (*ptr) {
    _destroyApp(*ptr);
    free(*ptr);
    (*ptr) = NULL;
  }
}
//----------------------------------------------------------------------------------
// Internal function definition.
//----------------------------------------------------------------------------------
__AC__ static void _initApp(void) {
  InitWindow(AC_WIDTH_SCREEN, AC_HEIGHT_SCREEN, AC_TITLE_SCREEN);
  SetTargetFPS(AC_FPS);
}

__AC__ static void _destroyApp(struct App *const app) {
  destroyScreen(&app->currentScreen);
  CloseWindow();
}

__AC__ static void _updateApp(struct App *app) {
  app->currentScreen->updateScreen(app->currentScreen);
}

__AC__ static void _drawApp(const struct App *const app) {
  BeginDrawing();
  app->currentScreen->drawScreen(app->currentScreen);

  EndDrawing();
}
