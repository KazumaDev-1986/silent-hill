#include "includes/object.h"
#include "includes/objects/cube.h"
#include "includes/raylib.h"
#include <stdlib.h>

//----------------------------------------------------------------------------------
// Internal function declaration.
//----------------------------------------------------------------------------------

#if defined(__cplusplus)
extern "C" {
#endif

__AC__ static void _destroyObject(struct Object *const obj);

#if defined(__cplusplus)
}
#endif

//----------------------------------------------------------------------------------
// Public function definition.
//----------------------------------------------------------------------------------
__AC__ struct Object *createCubeObject(Vector3 position, Vector3 size,
                                       Color color,
                                       void (*callback)(struct Cube *const)) {
  struct Object *obj = (struct Object *)malloc(sizeof(struct Object));
  if (!obj) {
    return NULL;
  }

  obj->node = createCube(position, size, color, NULL);
  if (!obj->node) {
    free(obj);
    obj = NULL;
    return NULL;
  }
  obj->type = AC_CUBE_OBJECT;

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
__AC__ void updateObject(struct Object *const obj) {
  switch (obj->type) {
  case AC_PLANE_OBJECT:
    break;
  case AC_CUBE_OBJECT:
    updateCube(obj->node);
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
