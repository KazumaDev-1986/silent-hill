#ifndef __AC_CUBE_H__
#define __AC_CUBE_H__

#include "../config.h"
#include "../raylib.h"

__AC__ struct Cube {
  Vector3 position;
  Vector3 size;
  Color color;

  void (*_update)(struct Cube *const);
  void (*_draw)(const struct Cube *const);
};

#if defined(__cplusplus)
extern "C" {
#endif

__AC__ struct Cube *createCube(Vector3 position, Vector3 size, Color color,
                               void (*update)(struct Cube *const),
                               void (*draw)(const struct Cube *const));
__AC__ void updateCube(struct Cube *const cube);
__AC__ void drawCube(const struct Cube *const cube);
__AC__ void destroyCube(struct Cube **ptr);

#if defined(__cplusplus)
}
#endif

#endif //__AC_CUBE_H__
