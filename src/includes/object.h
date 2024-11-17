#ifndef __AC_OBJECT_H__
#define __AC_OBJECT_H__

#include "config.h"
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

__AC__ struct Object *createObject(enum ObjectType type);

__AC__ void updateObject(struct Object *const obj);

__AC__ void drawObject(const struct Object *const obj);

__AC__ void destroyObject(struct Object **const ptr);

#if defined(__cplusplus)
}
#endif

#endif // __AC_OBJECT_H__
