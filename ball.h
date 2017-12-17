#ifndef _IPBALL
#define _IPBALL
#include "respak.h"
#include "paddle.h"
#include "SDL2/SDL_mixer.h"
#include "animate.h"

#define IP_MAX_X_VELOC 30
#define IP_MIN_X_VELOC 6
#define IP_MAX_Y_VELOC 7
#define IP_MIN_Y_VELOC 0
#define IP_MIN_BALLSPIN -0.1
#define IP_MAX_BALLSPIN 0.1

class IPBall {

  int calcVeloc(IPPaddle *);
  double r,g,b;

  Uint32 lastticks = 0;
public:
  IPBall();
  ~IPBall();
  void getTex(SDL_Texture *);
  void getAud();
  void draw(SDL_Renderer *);
  void moveBall(IPPaddle *, IPPaddle *);

  SDL_Texture * balltex;
  SDL_Texture * defaultballtex;

  unsigned short board_x;
  unsigned short board_y;
  SDL_Rect pos;
  double ballspinmax = IP_MAX_BALLSPIN;
  double ballspinmin = IP_MIN_BALLSPIN;
  double ballspin;
  double velocX;
  double velocY;
  double rotation = 0;
  bool direction;
  bool outofbounds = 0;

  Mix_Chunk * bounce1 = NULL;

};

#endif
