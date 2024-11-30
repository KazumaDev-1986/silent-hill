#include "../includes/objects/player.h"
#include "../includes/error.h"
#include "../includes/raymath.h"
#include "../includes/rlgl.h"
#include <math.h>
#include <stdint.h>
#include <stdlib.h>

//----------------------------------------------------------------------------------
// Internal function declaration.
//----------------------------------------------------------------------------------
// static const char *MODEL_PATH = "data/models/lorena.m3d";
static const float _VELOCITY = 0.05f;
static const float _ROTATION_VELOCITY = 3.0f;

static int32_t _animationCount = 0.0f;
static int32_t _animationFrame = 0.0f;
static int32_t _animationIndex = 0.0f;

static float _rotationAngle = 0.0f;

#if defined(__cplusplus)
extern "C" {
#endif

__AC__ static void _updateAnimation(struct Player *const player);

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

  player->model = LoadModel("./data/models/lorena.m3d");
  player->texture = LoadTexture("./data/models/lorena_color.png");
  player->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture =
      player->texture;

  player->animations =
      LoadModelAnimations("./data/models/lorena.m3d", &_animationCount);

  return player;
}
__AC__ void updatePlayer(struct Player *const player) {
  _animationIndex = 1;

  if (IsKeyDown(KEY_W)) {
    player->position.x -= cosf(DEG2RAD * player->rotation.y) * _VELOCITY;
    player->position.z += sinf(DEG2RAD * player->rotation.y) * _VELOCITY;
    _animationIndex = 3;
  } else if (IsKeyDown(KEY_S)) {
    player->position.x += cosf(DEG2RAD * player->rotation.y) * _VELOCITY;
    player->position.z -= sinf(DEG2RAD * player->rotation.y) * _VELOCITY;
    _animationIndex = 0;
  }
  if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
    player->rotation.y += _ROTATION_VELOCITY;
  } else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
    player->rotation.y -= _ROTATION_VELOCITY;
  }

  if (player->updateCamera) {
    player->updateCamera(player->position, player->rotation);
  }
  _updateAnimation(player);
}
__AC__ void drawPlayer(const struct Player *const player) {

  // rlPushMatrix();
  // rlLoadIdentity();
  // rlTranslatef(player->position.x, player->position.y, player->position.z);
  // rlRotatef(player->rotation.y, 0.0f, 1.0f, 0.0f);
  // DrawCube((Vector3){0}, 1.0f, 1.5f, 1.0f, RAYWHITE);
  // DrawCubeWires((Vector3){0}, 1.0f, 1.5f, 1.0f, DARKGRAY);

  // DrawCube((Vector3){0.0f, 0.75f, 0.5f}, 0.5f, 0.5f, 0.5f, RED);
  // DrawCubeWires((Vector3){0.0f, 0.75f, 0.5f}, 0.5f, 0.5f, 0.5f, DARKGRAY);

  // rlPopMatrix();
  // DrawModel(player->model, (Vector3){0}, 1.0f, RAYWHITE);

  if (_animationIndex != 1) {
    _rotationAngle = Lerp(_rotationAngle, player->rotation.y, 0.3f);
  }

  DrawModelEx(player->model, player->position, (Vector3){0.0f, 1.0f, 0},
              _rotationAngle - 90.0f, (Vector3){1.0f, 1.0f, 1.0f}, RAYWHITE);
}
__AC__ void destroyPlayer(struct Player **const ptr) {
  if (ptr && *ptr) {
    UnloadTexture((*ptr)->texture);
    UnloadModelAnimations((*ptr)->animations, _animationCount);
    UnloadModel((*ptr)->model);

    free(*ptr);
    (*ptr) = NULL;
  }
}

//----------------------------------------------------------------------------------
// Internal function definition.
//----------------------------------------------------------------------------------
__AC__ static void _updateAnimation(struct Player *const player) {
  ModelAnimation animation = player->animations[_animationIndex];
  _animationFrame = (_animationFrame + 1) % animation.frameCount;
  UpdateModelAnimation(player->model, animation, _animationFrame);
}
