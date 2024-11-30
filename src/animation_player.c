#include "includes/animation_player.h"
#include "includes/error.h"
#include "includes/raylib.h"
#include <stdlib.h>

//----------------------------------------------------------------------------------
// Internal function declaration.
//----------------------------------------------------------------------------------
__AC__ struct AnimationPlayer *createAnimationPlayer(const char *filename)
{
  struct AnimationPlayer *ap = NULL;
  
  if (FileExists(filename)){
    ap = (struct AnimationPlayer *)malloc(sizeof(struct AnimationPlayer));
    if (!ap)
    {
      printError("struct AnimationPlayer * failed.");
      return NULL;
    }
    
    ap->animations = LoadModelAnimations(filename, &ap->length);
    if (!ap->animations)
    {
      printError("LoadModelAnimations failed.");
      free(ap);
      ap = NULL;
      return NULL;
    }

    ap->index = PLAYER_IDLE;
    ap->frame = 0;
  }

  return ap;
}
__AC__ void updateAnimationPlayer(struct AnimationPlayer *ap, Model *const model)
{
  ModelAnimation animation = ap->animations[ap->index];
  ap->frame = (ap->frame + 1) % animation.frameCount;
  UpdateModelAnimation(*model, animation, ap->frame);
}
__AC__ void setIndexAnimationPlayer(struct AnimationPlayer *const ap, enum AnimationPlayerIndex index)
{
  if (index >= 0 && index < ap->length) {
    ap->index = index;
  }
}
__AC__ enum AnimationPlayerIndex getCurrentIndexAnimationPlayer(const struct AnimationPlayer *const ap)
{
  return ap->index; 
}
__AC__ void destroyAnimationPlayer(struct AnimationPlayer **const ptr)
{
  if (ptr && *ptr)
  {
    UnloadModelAnimations((*ptr)->animations, (*ptr)->length);
    free((*ptr));
    (*ptr) = NULL;
  }
}
//----------------------------------------------------------------------------------
// Public function definition.
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
// Internal function definition.
//----------------------------------------------------------------------------------
