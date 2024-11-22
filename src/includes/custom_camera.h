#ifndef __AC_CUSTOM_CAMERA_H__
#define __AC_CUSTOM_CAMERA_H__

#include "config.h"
#include "raylib.h"


__AC__ struct CustomCamera {
  Camera data;
};

#if defined(__cplusplus)
extern "C" {
#endif

__AC__ struct CustomCamera *createCustomCamera(Vector3 position, Vector3 target);
__AC__ void updateCustomCamera(Vector3 position, Vector3 rotation);
__AC__ void destroyCustomCamera(struct CustomCamera **const ptr);

#if defined(__cplusplus)
}
#endif 

#endif // __AC_CUSTOM_CAMERA_H___
