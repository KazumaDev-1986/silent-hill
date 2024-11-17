#ifndef __AC_CUBE_H__
#define __AC_CUBE_H__

#include "../config.h"
#include "../raylib.h"

__AC__ struct Cube {
  Vector3 position;
  Vector3 size;
  Color color;
};

#if defined(__cplusplus)
extern "C" {
#endif

__AC__ struct Cube *createCube(Vector3 position, Vector3 size, Color color);
__AC__ void updateCube(struct Cube *const cube,
                       void (*callback)(struct Cube *const));
__AC__ void drawCube(const struct Cube *const cube);
__AC__ void destroyCube(struct Cube **ptr);

#if defined(__cplusplus)
}
#endif

#endif //__AC_CUBE_H__
