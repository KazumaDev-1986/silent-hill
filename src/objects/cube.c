#include "../includes/objects/cube.h"
#include "../includes/error.h"
#include <stdlib.h>

//----------------------------------------------------------------------------------
// Internal function declaration.
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
// Public function definition.
//----------------------------------------------------------------------------------

__AC__ struct Cube *createCube(Vector3 position, Vector3 size, Color color,
                               void (*callback)(struct Cube *const)) {
  struct Cube *cube = (struct Cube *)malloc(sizeof(struct Cube));
  if (!cube) {
    printError("struct Cube * failed.");
    return NULL;
  }

  cube->position = position;
  cube->size = size;
  cube->color = color;
  cube->_callback = callback;

  return cube;
}
__AC__ void updateCube(struct Cube *const cube) {
  if (cube->_callback) {
    cube->_callback(cube);
  }
}
__AC__ void drawCube(const struct Cube *const cube) {
  if (cube) {
    DrawCubeV(cube->position, cube->size, cube->color);
    DrawCubeWiresV(cube->position, cube->size, DARKGRAY);
  }
}

__AC__ void destroyCube(struct Cube **ptr) {
  if (ptr && *ptr) {
    free(*ptr);
    (*ptr) = NULL;
  }
}
//----------------------------------------------------------------------------------
// Internal function definition.
//----------------------------------------------------------------------------------
