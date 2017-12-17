#ifndef _IPANIM
#define _IPANIM
#include "respak.h"

class Animation {

  void setClip();

  SDL_Rect frameclip;
  unsigned short numframes,
                 framesps;
  int            img_w,
                 img_h,
                 clip_chunk;
  short loop,
        loop_step = 0;
  Uint32 lastframechange;
  Uint32 framechunk;

public:
  Animation();
  ~Animation();

  void setAnim(SDL_Texture *,unsigned short,unsigned short,short);
  void stepAnim();
  void setFPS(unsigned short fps) { framesps = fps; framechunk = (1000/framesps); }

  SDL_Rect clip;
};

#endif
