#ifndef _IPPICKUP
#define _IPPICKUP
#include "respak.h"
#include "ball.h"
#include "paddle.h"

#define IP_MIN_SPAWNTIME 4000
#define IP_MAX_SPAWNTIME 10000

#define IP_PU_BIGBALL 0
#define IP_PU_SMALLBALL 1
#define IP_PU_DRUNKBALL 2
#define IP_PU_BARBBALL 3

#define NUM_PICKUPS 4

class IPPickup {

  short alphamod;
  Uint8 r, g, b;

public:
  IPPickup();
  ~IPPickup();

  void place(unsigned int x, unsigned int y);
  void checkColl(IPBall*,IPPaddle*,IPPaddle*);
  virtual void drawPickup(SDL_Renderer *){}
  virtual void puEffector(IPBall *, IPPaddle *, IPPaddle *){}
  virtual void deactivate(IPBall *, IPPaddle *, IPPaddle *){}

  bool onboard = false;
  bool active = false;

  Uint8 texturealpha;
  SDL_Rect pos;
  Uint32 spawnstamp,
         pickupstamp;
  unsigned int spawn_dur,
               pickup_dur;
  SDL_Texture * putexture = NULL;
  SDL_Texture * putexture2 = NULL;
  SDL_Texture * putexture3 = NULL;

  std::string name;

};

#endif
