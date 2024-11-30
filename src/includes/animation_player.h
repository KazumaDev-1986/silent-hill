#ifndef __AC_ANIMATION_PLAYER_H__
#define __AC_ANIMATION_PLAYER_H__

#include "config.h"
#include "raylib.h"
#include <stdint.h>

__AC__ struct AnimationPlayer {
  Model model;

  int32_t length;
  int32_t index;
  int32_t frame;
};

#if defined(__cplusplus)
extern "C" {
#endif

__AC__ struct AnimationPlayer *createAnimationPlayer(const char *filename);
__AC__ void updateAnimationPlayer(struct AnimationPlayer *ap);
__AC__ void destroyAnimationPlayer(const struct AnimationPlayer *const ptr);

#if defined(__cplusplus)
}
#endif

#endif // __AC_ANIMATION_PLAYER_H__
