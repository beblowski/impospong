#ifndef _IPBARBBALL
#define _IPBARBBALL
#include "pickup.h"

class BarbBall : public IPPickup {

public:
  BarbBall();
  ~BarbBall();

  void drawPickup(SDL_Renderer *);
  void puEffector(IPBall *, IPPaddle *, IPPaddle *);
  void deactivate(IPBall *, IPPaddle *, IPPaddle *);

  const int indent = IP_PU_BARBBALL;
};

#endif
