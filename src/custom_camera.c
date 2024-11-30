#include "includes/custom_camera.h"
#include "includes/error.h"
#include "includes/raylib.h"
#include "includes/raymath.h"
#include <stdlib.h>
#include <math.h>

//----------------------------------------------------------------------------------
// Internal varables and function declaration.
//----------------------------------------------------------------------------------
static struct CustomCamera *_customCamera;
static float _currentAngle = 0.0f;

#if defined(__cplusplus)
extern "C" {
#endif

#if defined(__cplusplus)
}
#endif


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

  _customCamera = camera;

  return camera;
}
__AC__ void updateCustomCamera(Vector3 position, Vector3 rotation)
{
  _customCamera->data.target.x = position.x;
  _customCamera->data.target.y = position.y + 0.5f;
  _customCamera->data.target.z = position.z;

  _currentAngle = Lerp(_currentAngle, rotation.y, 0.09f);

  _customCamera->data.position.x = position.x + cosf(DEG2RAD * _currentAngle) * 3.0;
  _customCamera->data.position.y = _customCamera->data.position.y;
  _customCamera->data.position.z = position.z - sinf(DEG2RAD * _currentAngle) * 3.0;
}
__AC__ void destroyCustomCamera(struct CustomCamera **const ptr)
{
  if (ptr && *ptr)
  {
    free(*ptr);
    *ptr = NULL;
    _customCamera = NULL;
  }
}

//----------------------------------------------------------------------------------
// Internal function definition.
//----------------------------------------------------------------------------------

