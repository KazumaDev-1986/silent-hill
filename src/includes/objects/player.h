#ifndef __AC_PLAYER_H__
#define __AC_PLAYER_H__

#include "../config.h"
#include "../raylib.h"
#include "../animation_player.h"

__AC__ struct Player {
  Vector3 position;
  Vector3 rotation;
  Model model;
  Texture2D texture;
  struct AnimationPlayer *ap;
  void (*updateCamera)(Vector3, Vector3);
};

#if defined(__cplusplus)
extern "C" {
#endif

__AC__ struct Player *createPlayer(Vector3 position,
                                   void (*updateCamera)(Vector3, Vector3));
__AC__ void updatePlayer(struct Player *const player);
__AC__ void drawPlayer(const struct Player *const player);
__AC__ void destroyPlayer(struct Player **const ptr);

#if defined(__cplusplus)
}
#endif

#endif //__AC_PLAYER_H__
