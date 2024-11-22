#include "includes/custom_camera.h"
#include "includes/error.h"
#include <stdlib.h>
#include <math.h>

//----------------------------------------------------------------------------------
// Internal varables and function declaration.
//----------------------------------------------------------------------------------
static struct CustomCamera *_internalCustomCamera;

//----------------------------------------------------------------------------------
// Public function definition.
//----------------------------------------------------------------------------------
__AC__ struct CustomCamera *createCustomCamera(Vector3 position, Vector3 target)
{
  struct CustomCamera *camera = (struct CustomCamera*)malloc(sizeof(struct CustomCamera));
  if (!camera)
  {
    printError("struct CustomCamera * failed.");
    return NULL;
  }

  camera->data.fovy = 45.0f;
  camera->data.up = (Vector3){0.0f, 1.0f, 0.0f};
  camera->data.position = position;
  camera->data.target = target;  
  camera->data.projection = CAMERA_PERSPECTIVE;

  _internalCustomCamera = camera;

  return camera;
}
__AC__ void updateCustomCamera(Vector3 position, Vector3 rotation)
{
  if (_internalCustomCamera)
  {
    _internalCustomCamera->data.target = position;
    _internalCustomCamera->data.position.x = position.x - 5 * cosf(DEG2RAD * rotation.y);
    _internalCustomCamera->data.position.z = position.z + 5 * sinf(DEG2RAD * rotation.y);
  }
}
__AC__ void destroyCustomCamera(struct CustomCamera **const ptr)
{
  if (ptr && *ptr)
  {
    free(*ptr);
    *ptr = NULL;
    _internalCustomCamera = NULL;
  }
}

//----------------------------------------------------------------------------------
// Internal function definition.
//----------------------------------------------------------------------------------
