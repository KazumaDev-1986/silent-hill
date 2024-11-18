#ifndef __AC_OBJECT_H__
#define __AC_OBJECT_H__

#include "config.h"
#include "objects/cube.h"
#include "objects/plane.h"
#include "raylib.h"
#include <stddef.h>

enum ObjectType {
  AC_PLANE_OBJECT = 0,
  AC_CUBE_OBJECT,
};

struct Object {
  void *node;
  enum ObjectType type;
};

#if defined(__cplusplus)
extern "C" {
#endif

__AC__ struct Object *createCubeObject(Vector3 position, Vector3 size,
                                       Color color,
                                       void (*update)(struct Cube *const),
                                       void (*draw)(const struct Cube *const));

__AC__ struct Object *
createPlaneObject(Vector3 center, Vector2 size, Color color,
                  void (*update)(struct Plane *const),
                  void (*draw)(const struct Plane *const));
__AC__ void updateObject(struct Object *const obj);
__AC__ void drawObject(const struct Object *const obj);
__AC__ void destroyObject(struct Object **const ptr);

#if defined(__cplusplus)
}
#endif

#endif // __AC_OBJECT_H__
