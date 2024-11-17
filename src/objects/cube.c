#include "../includes/objects/cube.h"
#include "../includes/error.h"
#include <stdlib.h>

//----------------------------------------------------------------------------------
// Internal function declaration.
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
// Public function definition.
//----------------------------------------------------------------------------------

__AC__ struct Cube *createCube(Vector3 position, Vector3 size, Color color) {
  struct Cube *cube = (struct Cube *)malloc(sizeof(struct Cube));
  if (!cube) {
    printError("struct Cube * failed.");
    return NULL;
  }

  cube->position = position;
  cube->size = size;
  cube->color = color;

  return cube;
}
__AC__ void updateCube(struct Cube *const cube,
                       void (*callback)(struct Cube *const)) {
  if (callback) {
    callback(cube);
  }
}
__AC__ void drawCube(const struct Cube *const cube) {
  DrawCubeV(cube->position, cube->size, cube->color);
}

__AC__ void destroyCube(struct Cube **ptr) {
  if (ptr && *ptr) {
    free(*ptr);
    (*ptr) = NULL;
    TraceLog(LOG_INFO, ">> Cube deleted");
  }
}
//----------------------------------------------------------------------------------
// Internal function definition.
//----------------------------------------------------------------------------------
