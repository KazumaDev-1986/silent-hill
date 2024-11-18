#ifndef __AC_PLANE_H__
#define __AC_PLANE_H__

#include "../config.h"
#include "../raylib.h"

__AC__ struct Plane {
  Vector3 center;
  Vector2 size;
  Color color;

  void (*_update)(struct Plane *const);
  void (*_draw)(const struct Plane *const);
};

#if defined(__cplusplus)
extern "C" {
#endif

__AC__ struct Plane *createPlane(Vector3 center, Vector2 size, Color color,
                                 void (*update)(struct Plane *const),
                                 void (*draw)(const struct Plane *const));

__AC__ void updatePlane(struct Plane *const plane);
__AC__ void drawPlane(const struct Plane *const plane);
__AC__ void destroyPlane(struct Plane **const ptr);

#if defined(__cplusplus)
}
#endif

#endif // __AC_PLANE_H__
