#include "includes/config.h"
#include "includes/error.h"
#include "includes/object.h"
#include "includes/raylib.h"
#include "includes/rlgl.h"
#include "includes/screen.h"
#include "includes/utils.h"
#include <stdlib.h>

//------NULL--------------------------------------------------------------
// Internal function declaration.
//----------------------------------------------------------------------------------
static enum ScreenType _currentScreenType = AC_LEVEL_0_SCREEN;
static enum ScreenType _nextScreenType = AC_VOID_SCREEN;
static Camera *_camera;

#if defined(__cplusplus)
extern "C" {
#endif
__AC__ static void _updateLevel0Screen(struct Screen *const screen);
__AC__ static void _drawLevel0Screen(const struct Screen *const screen);
__AC__ static enum ScreenType _getScreenType(void);
__AC__ static enum ScreenType _getNextScreenType(void);
__AC__ static Camera *_createCamera(void);
__AC__ static void _destroyCamera(Camera **const ptr);
__AC__ static void _destroyAllObjects(struct List **const ptr);
__AC__ static void _resetIntervalVariables(void);

__AC__ static void _drawCube(const struct Cube *const cube);
__AC__ static void _rotationCube(const struct Cube *const cube);

#if defined(__cplusplus)
}
#endif

//----------------------------------------------------------------------------------
// Public function definition.
//----------------------------------------------------------------------------------
__AC__ struct Screen *createLevel0Screen(void) {
  _resetIntervalVariables();
  struct Screen *screen = (struct Screen *)malloc(sizeof(struct Screen));
  if (!screen) {
    printError("createLevel0Screen failed");
    return NULL;
  }

  _camera = _createCamera();
  if (!_camera) {
    free(screen);
    screen = NULL;
    return NULL;
  }

  screen->updateScreen = &_updateLevel0Screen;
  screen->drawScreen = &_drawLevel0Screen;
  screen->getScreenType = &_getScreenType;
  screen->getNextScreenType = &_getNextScreenType;

  screen->objects = NULL;

  addElementList(&screen->objects,
                 createCubeObject((Vector3){0}, (Vector3){1.0f, 1.0f, 1.0f},
                                  RED, NULL, &_rotationCube));
  addElementList(&screen->objects, createCubeObject((Vector3){2.0f, 0.0f, 0.0f},
                                                    (Vector3){1.0f, 1.0f, 1.0f},
                                                    BLUE, NULL, &_drawCube));
  addElementList(&screen->objects,
                 createCubeObject((Vector3){-2.0f, 0.0f, 0.0f},
                                  (Vector3){1.0f, 1.0f, 1.0f}, GREEN, NULL,
                                  &_drawCube));

  return screen;
}
__AC__ void destroyLevel0Screen(struct Screen **const ptr) {
  _destroyCamera(&_camera);
  if (ptr && *ptr) {
    _destroyAllObjects(&(*ptr)->objects);
    free(*ptr);
    *ptr = NULL;
  }
}

//----------------------------------------------------------------------------------
// Internal function definition.
//----------------------------------------------------------------------------------
__AC__ static void _updateLevel0Screen(struct Screen *const screen) {

  if (_camera) {
    UpdateCamera(_camera, CAMERA_FIRST_PERSON);
  }

  if (screen && screen->objects) {
    struct List *tmp = screen->objects;
    while (tmp) {
      if (tmp->value) {
        updateObject((struct Object *)tmp->value);
      }

      tmp = tmp->next;
    }
  }
}
__AC__ static void _drawLevel0Screen(const struct Screen *const screen) {
  ClearBackground(BLACK);
  if (_camera) {
    BeginMode3D(*_camera);
    DrawGrid(10, 1.0f);
    if (screen && screen->objects) {
      struct List *tmp = screen->objects;
      while (tmp) {
        if (tmp->value) {
          drawObject((struct Object *)tmp->value);
        }
        tmp = tmp->next;
      }
    }

    EndMode3D();
  }
}
__AC__ static enum ScreenType _getScreenType(void) {
  return _currentScreenType;
}
__AC__ static enum ScreenType _getNextScreenType(void) {
  return _nextScreenType;
}
__AC__ static Camera *_createCamera(void) {
  Camera *camera = (Camera *)malloc(sizeof(Camera));
  if (!camera) {
    printError("Camera * failer");
    return NULL;
  }

  camera->fovy = 45.0f;
  camera->position = (Vector3){10.0f, 10.0f, 0.0f};
  camera->target = (Vector3){0};
  camera->up = (Vector3){0.0f, 1.0f, 0.0f};
  camera->projection = CAMERA_PERSPECTIVE;

  return camera;
}
__AC__ static void _destroyCamera(Camera **const ptr) {
  if (ptr && *ptr) {
    free(*ptr);
    (*ptr) = NULL;
  }
}
__AC__ static void _destroyAllObjects(struct List **const ptr) {
  if (ptr && *ptr) {
    struct List *tmp = (*ptr);
    while (tmp) {
      destroyObject((struct Object **)&tmp->value);
      tmp = tmp->next;
    }
  }
}
__AC__ static void _resetIntervalVariables(void) {
  _destroyCamera(&_camera);
  _nextScreenType = AC_VOID_SCREEN;
}
__AC__ static void _drawCube(const struct Cube *const cube) {
  DrawCubeV(cube->position, cube->size, cube->color);
  DrawCubeWiresV(cube->position, cube->size, DARKGRAY);
}
__AC__ static void _rotationCube(const struct Cube *const cube) {
  static float angle = 0.0f;
  if (angle > 360) {
    angle = 0.0f;
  } else {
    angle += 1.0f;
  }
  rlPushMatrix();
  rlRotatef(angle, 0.0f, 1.0f, 0.0f);

  DrawCubeV(cube->position, cube->size, cube->color);
  DrawCubeWiresV(cube->position, cube->size, DARKGRAY);

  rlPopMatrix();
}
