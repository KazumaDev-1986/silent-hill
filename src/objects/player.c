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
static const float _RUN_VELOCITY = 0.08f;
static const float _WALK_VELOCITY = 0.06f;
static const float _BACK_VELOCITY = 0.04f;
static const float _ROTATION_VELOCITY = 3.0f;

static float _rotationAngle = 0.0f;
static const char *_modelFilename = "./data/models/lorena.m3d";
static const char *_textureFilename = "./data/models/lorena_color.png";

#if defined(__cplusplus)
extern "C" {
#endif

__AC__ static void _movement(struct Player *const player);

#if defined(__cplusplus)
}
#endif

//----------------------------------------------------------------------------------
// Public function definition.
//----------------------------------------------------------------------------------
__AC__ struct Player *createPlayer(Vector3 position,
                                   void (*updateCamera)(Vector3, Vector3)) {
  struct Player *player  = NULL;
  if (FileExists(_modelFilename) && FileExists(_textureFilename))
  {
    player = (struct Player *)malloc(sizeof(struct Player));
    if (!player) {
      printError("struct Player * failed.");
      return NULL;
    }

    player->position = position;
    player->rotation = (Vector3){0};
    player->updateCamera = updateCamera;

    player->model = LoadModel(_modelFilename);
    player->texture = LoadTexture(_textureFilename);
    player->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture =
        player->texture;

    player->ap = createAnimationPlayer(_modelFilename);
    if (!player->ap)
    {
      UnloadTexture(player->texture);
      UnloadModel(player->model);
      free(player);
      player = NULL;
    }
  }
  return player;
}
__AC__ void updatePlayer(struct Player *const player) {
  _movement(player);
  if (player->updateCamera) {
    player->updateCamera(player->position, player->rotation);
  }
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

  if (getCurrentIndexAnimationPlayer(player->ap) != PLAYER_IDLE) {
    _rotationAngle = Lerp(_rotationAngle, player->rotation.y, 0.3f);
  }

  // DrawModelEx(player->model, player->position, (Vector3){0.0f, 1.0f, 0},
  //             _rotationAngle - 90.0f, (Vector3){1.0f, 1.0f, 1.0f}, RAYWHITE);
  DrawModelWiresEx(player->model, player->position, (Vector3){0.0f, 1.0f, 0},
              _rotationAngle - 90.0f, (Vector3){1.0f, 1.0f, 1.0f}, RAYWHITE);
}
__AC__ void destroyPlayer(struct Player **const ptr) {
  if (ptr && *ptr) {
    UnloadTexture((*ptr)->texture);
    destroyAnimationPlayer(&(*ptr)->ap);
    UnloadModel((*ptr)->model);

    free(*ptr);
    (*ptr) = NULL;
  }
}

//----------------------------------------------------------------------------------
// Internal function definition.
//----------------------------------------------------------------------------------
__AC__ static void _movement(struct Player *const player)
{
  float rotationRad = DEG2RAD * player->rotation.y;
  enum AnimationPlayerIndex index = PLAYER_IDLE;
  
  if (IsKeyDown(KEY_W)) {
    float velocity = (IsKeyDown(KEY_LEFT_SHIFT)) ? _RUN_VELOCITY : _WALK_VELOCITY;
    index = (IsKeyDown(KEY_LEFT_SHIFT)) ? PLAYER_RUN : PLAYER_WALK;
    
    player->position.x -= cosf(rotationRad) * velocity;
    player->position.z += sinf(rotationRad) * velocity;
  } else if (IsKeyDown(KEY_S)) {
    player->position.x += cosf(rotationRad) * _BACK_VELOCITY;
    player->position.z -= sinf(rotationRad) * _BACK_VELOCITY;
    index = PLAYER_BACK;
  }
  if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
    player->rotation.y += _ROTATION_VELOCITY;
  } else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
    player->rotation.y -= _ROTATION_VELOCITY;
  }
  
  setIndexAnimationPlayer(player->ap, index);  
  updateAnimationPlayer(player->ap, &player->model);
}
