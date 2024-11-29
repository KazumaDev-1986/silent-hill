#include "../includes/objects/player.h"
#include "../includes/error.h"
#include "../includes/rlgl.h"
#include <math.h>
#include <stdlib.h>

//----------------------------------------------------------------------------------
// Internal function declaration.
//----------------------------------------------------------------------------------
// static const char *MODEL_PATH = "data/models/lorena.m3d";
static const float _VELOCITY = 0.05;
static const float _ROTATION_VELOCITY = 2.0f;

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
    player->position.x += cosf(DEG2RAD * player->rotation.y) * _VELOCITY;
    player->position.z -= sinf(DEG2RAD * player->rotation.y) * _VELOCITY;

  } else if (IsKeyDown(KEY_S)) {
    player->position.x -= cosf(DEG2RAD * player->rotation.y) * _VELOCITY;
    player->position.z += sinf(DEG2RAD * player->rotation.y) * _VELOCITY;
  }
  if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
    player->rotation.y += _ROTATION_VELOCITY;
  } else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
    player->rotation.y -= _ROTATION_VELOCITY;
  }

  // player->rotation.y = Clamp(player->rotation.y, 0.0f, 360.0f);

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

  DrawCube((Vector3){0.5f, 0.75f, 0.0f}, 1.0f, 0.5f, 0.5f, RED);
  DrawCubeWires((Vector3){0.5f, 0.75f, 0.0f}, 1.0f, 0.5f, 0.5f, DARKGRAY);

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
