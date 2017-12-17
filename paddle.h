#ifndef _IPPADDLE
#define _IPPADDLE
#include "respak.h"

class IPPaddle {
  bool flip = false;
  Respak * rpak = NULL;
  int paddle_target;
  int board_w, board_h;
public:
  IPPaddle();
  ~IPPaddle();
  void getTex(SDL_Texture *,bool);
  void draw(SDL_Renderer *);
  void moveKey();
  void moveMouse(int);
  void moveAI(int);
  void setBoardSize(unsigned int, unsigned int);

  SDL_Texture * paddletex = NULL;
  SDL_Rect pos;
  unsigned int score = 0;
  double paddle_vel;

  double accelrate = .45;
  double accelmax = 10;

};

#endif
