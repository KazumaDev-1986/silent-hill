#ifndef __AC_ANIMATION_PLAYER_H__
#define __AC_ANIMATION_PLAYER_H__

#include "config.h"
#include "raylib.h"
#include <stdint.h>

__AC__ enum AnimationPlayerIndex {
  PLAYER_IDLE = 1,
  PLAYER_WALK = 3,
  PLAYER_BACK = 0,
  PLAYER_RUN  = 2
};

__AC__ struct AnimationPlayer {
  enum AnimationPlayerIndex index;
  ModelAnimation *animations;
  int32_t length;
  int32_t frame;
};

#if defined(__cplusplus)
extern "C" {
#endif

__AC__ struct AnimationPlayer *createAnimationPlayer(const char *filename);
__AC__ void updateAnimationPlayer(struct AnimationPlayer *ap, Model *const model);
__AC__ void setIndexAnimationPlayer(struct AnimationPlayer *const ap, enum AnimationPlayerIndex index);
__AC__ enum AnimationPlayerIndex getCurrentIndexAnimationPlayer(const struct AnimationPlayer *const ap);
__AC__ void destroyAnimationPlayer(struct AnimationPlayer **const ptr);

#if defined(__cplusplus)
}
#endif

#endif // __AC_ANIMATION_PLAYER_H__
