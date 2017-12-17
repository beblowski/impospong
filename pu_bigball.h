#ifndef _IPBIGBALL
#define _IPBIGBALL
#include "pickup.h"

class BigBall : public IPPickup {
  int orig_w=0, orig_h=0;
public:
  BigBall();
  ~BigBall();

  void drawPickup(SDL_Renderer *);
  void puEffector(IPBall *, IPPaddle *, IPPaddle *);
  void deactivate(IPBall * ball, IPPaddle * lpaddle = NULL, IPPaddle * rpaddle = NULL);

  const int indent = IP_PU_BIGBALL;
};

#endif
