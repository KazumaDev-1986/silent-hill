#include "../includes/objects/player.h"
#include "../includes/error.h"
#include "../includes/rlgl.h"
#include <math.h>
#include <stdlib.h>

//----------------------------------------------------------------------------------
// Internal function declaration.
//----------------------------------------------------------------------------------
// static const char *MODEL_PATH = "data/models/lorena.m3d";

#if defined(__cplusplus)
extern "C" {
#endif
#if defined(__cplusplus)
}
#endif

//----------------------------------------------------------------------------------
// Public function definition.
//----------------------------------------------------------------------------------
__AC__ struct Player *createPlayer(Vector3 position,
                                   void (*updateCamera)(Vector3, Vector3)) {
  struct Player *player = (struct Player *)malloc(sizeof(struct Player));
  if (!player) {
    printError("struct Player * failed.");
    return NULL;
  }

  player->position = position;
  player->rotation = (Vector3){0};
  player->updateCamera = updateCamera;

  return player;
}
__AC__ void updatePlayer(struct Player *const player) {
  if (IsKeyDown(KEY_W)) {
    player->position.x += cosf(DEG2RAD * player->rotation.y) * 0.05f;
    player->position.z -= sinf(DEG2RAD * player->rotation.y) * 0.05f;

  } else if (IsKeyDown(KEY_S)) {
    // player->position.x -= cosf(player->rotation.y) * 0.5f;
    // player->position.z -= sinf(player->rotation.y) * 0.5f;
  } else if (IsKeyDown(KEY_LEFT)) {
    player->rotation.y += 1.0f;
    if (player->rotation.y > 360.0f) {
      player->rotation.y = 0;
    }
  } else if (IsKeyDown(KEY_RIGHT)) {
    player->rotation.y -= 1.0f;
    if (player->rotation.y < 0) {
      player->rotation.y = 360;
    }
  }

  if (player->updateCamera) {
    player->updateCamera(player->position, player->rotation);
  }
}
__AC__ void drawPlayer(const struct Player *const player) {

  rlPushMatrix();
  rlLoadIdentity();
  rlTranslatef(player->position.x, player->position.y, player->position.z);
  rlRotatef(player->rotation.y, 0.0f, 1.0f, 0.0f);
  DrawCube((Vector3){0}, 1.0f, 1.5f, 1.0f, RAYWHITE);
  DrawCubeWires((Vector3){0}, 1.0f, 1.5f, 1.0f, DARKGRAY);

  rlPopMatrix();
}
__AC__ void destroyPlayer(struct Player **const ptr) {
  if (ptr && *ptr) {
    free(*ptr);
    (*ptr) = NULL;
  }
}

//----------------------------------------------------------------------------------
// Internal function definition.
//----------------------------------------------------------------------------------
