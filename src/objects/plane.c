#include "../includes/objects/plane.h"
#include "../includes/error.h"
#include "../includes/raylib.h"
#include <stdlib.h>

__AC__ struct Plane *createPlane(Vector3 center, Vector2 size, Color color,
                                 void (*update)(struct Plane *const),
                                 void (*draw)(const struct Plane *const)) {
  struct Plane *plane = (struct Plane *)malloc(sizeof(struct Plane));
  if (!plane) {
    printError("struct Plane * failed");
    return NULL;
  }

  plane->center = center;
  plane->size = size;
  plane->color = color;
  plane->_update = update;
  plane->_draw = draw;

  return plane;
}

__AC__ void updatePlane(struct Plane *const plane) {
  if (plane->_update) {
    plane->_update(plane);
  }
}
__AC__ void drawPlane(const struct Plane *const plane) {
  if (plane->_draw) {
    plane->_draw(plane);
  }
}
__AC__ void destroyPlane(struct Plane **const ptr) {
  if (ptr && *ptr) {
    free(*ptr);
    (*ptr) = NULL;
  }
}
