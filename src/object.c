#include "includes/object.h"
#include "includes/error.h"
#include "includes/objects/cube.h"
#include "includes/raylib.h"
#include <stdlib.h>

//----------------------------------------------------------------------------------
// Internal function declaration.
//----------------------------------------------------------------------------------

#if defined(__cplusplus)
extern "C" {
#endif

__AC__ static struct Object *_createObjectByType(struct Object *obj,
                                                 enum ObjectType type);
__AC__ static void _destroyObject(struct Object *const obj);

#if defined(__cplusplus)
}
#endif

//----------------------------------------------------------------------------------
// Public function definition.
//----------------------------------------------------------------------------------
__AC__ struct Object *createObject(enum ObjectType type) {
  struct Object *obj = (struct Object *)malloc(sizeof(struct Object));

  if (!obj) {
    printError(TextFormat("struct Object * failed - %d", type));
    return NULL;
  }

  _createObjectByType(obj, type);
  if (!obj->node) {
    free(obj);
    obj = NULL;
    return NULL;
  }

  return obj;
}

__AC__ void destroyObject(struct Object **const ptr) {
  if (ptr && *ptr) {
    _destroyObject(*ptr);
    free(*ptr);
    *ptr = NULL;
  }
}

//----------------------------------------------------------------------------------
// Internal function definition.
//----------------------------------------------------------------------------------
__AC__ static struct Object *_createObjectByType(struct Object *obj,
                                                 enum ObjectType type) {
  switch (type) {
  case AC_PLANE_OBJECT:
    break;
  case AC_CUBE_OBJECT:
    obj->node = createCube((Vector3){0}, (Vector3){1.0f, 1.0f, 1.0f}, RED);
    obj->type = type;
    break;
  default:
    break;
  }

  return obj;
}
__AC__ void updateObject(struct Object *const obj) {
  switch (obj->type) {
  case AC_PLANE_OBJECT:
    break;
  case AC_CUBE_OBJECT:
    updateCube(obj->node, NULL);
    break;
  default:
    break;
  }
}
__AC__ void drawObject(const struct Object *const obj) {
  switch (obj->type) {
  case AC_PLANE_OBJECT:
    break;
  case AC_CUBE_OBJECT:
    drawCube(obj->node);
    break;
  default:
    break;
  }
}
__AC__ static void _destroyObject(struct Object *const obj) {
  switch (obj->type) {
  case AC_PLANE_OBJECT:
    break;
  case AC_CUBE_OBJECT:
    destroyCube((struct Cube **)&obj->node);
    break;
  default:
    break;
  }
}
