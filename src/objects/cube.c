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
                               void (*update)(struct Cube *const),
                               void (*draw)(const struct Cube *const)) {
  struct Cube *cube = (struct Cube *)malloc(sizeof(struct Cube));
  if (!cube) {
    printError("struct Cube * failed.");
    return NULL;
  }

  cube->position = position;
  cube->size = size;
  cube->color = color;
  cube->_update = update;
  cube->_draw = draw;

  return cube;
}
__AC__ void updateCube(struct Cube *const cube) {
  if (cube->_update) {
    cube->_update(cube);
  }
}
__AC__ void drawCube(const struct Cube *const cube) {
  if (cube && cube->_draw) {
    cube->_draw(cube);
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
