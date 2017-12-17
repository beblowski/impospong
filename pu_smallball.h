#ifndef _IPSMALLBALL
#define _IPSMALLBALL
#include "pickup.h"

class SmallBall : public IPPickup {
  int orig_w=0, orig_h=0;
public:
  SmallBall();
  ~SmallBall();

  void drawPickup(SDL_Renderer *);
  void puEffector(IPBall *, IPPaddle *, IPPaddle *);
  void deactivate(IPBall *, IPPaddle * lpaddle = NULL, IPPaddle * rpaddle = NULL);

  const int indent = IP_PU_SMALLBALL;
};

#endif
