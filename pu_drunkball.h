#ifndef _IPDRUNKBALL
#define _IPDRUNKBALL
#include "pickup.h"

class DrunkBall : public IPPickup {

public:
  DrunkBall();
  ~DrunkBall();

  void drawPickup(SDL_Renderer *);
  void puEffector(IPBall *, IPPaddle *, IPPaddle *);
  void deactivate(IPBall * ball = NULL, IPPaddle * lpaddle = NULL, IPPaddle * rpaddle = NULL);

  const int indent = IP_PU_DRUNKBALL;
};

#endif
