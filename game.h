#ifndef _IPONGGAME
#define _IPONGGAME
#include "respak.h"
#include "paddle.h"
#include "ball.h"
#include "animate.h"
#include "textblock.h"
#include "ui.h"

#include "pu_bigball.h"
#include "pu_smallball.h"
#include "pu_drunkball.h"
#include "pu_barball.h"

#define IP_MAX_FRAMERATE 60

class IPGame {
  Respak respak;
  bool stmainloop = 1;
  bool stgameloop = 0;
  bool stsplashloop = 1;
  bool stdemoloop = 0;

  bool showdebug = 1;

  Uint8 ren_r, ren_g, ren_b;
  unsigned short screen_w = 800;
  unsigned short screen_h = 600;
  unsigned short uiheight = (screen_h / 6);
  unsigned short board_w = screen_w;
  unsigned short board_h = screen_h - (screen_h / 6);
  unsigned short framerate = IP_MAX_FRAMERATE;
  Uint32 lastframetick = 0;

  short musicvolume = 100;
  short musicvolmod;

  Uint32 lastpickupdrop = 0;
  unsigned int pickupwait = 0;
public:
  Respak * respntr;
  IPGame();
  ~IPGame();
  void mainLoop();
  void splashLoop();
  void gameLoop();
  void demoLoop();
  void puPlacer(int pu = -1);
  void puCheck();
  void drawFrame();
  void checkQuit();
  void gameEvents();
  void demoEvents();
  void splashEvents();
  void globalEvents();
  void resetBoard();
  void resetGame();
  void frameCap();
  void waitTicks(unsigned int);
  void drawDebug();

  SDL_Renderer * renderer = NULL;
  SDL_Window * mainWindow = NULL;
  SDL_Texture * floor = NULL;
  SDL_Texture * splash = NULL;
  SDL_Event event;

  TTF_Font * defaultfont = NULL;
  IPTextBlock gtext;

  IPPaddle lpaddle;
  IPPaddle rpaddle;
  IPBall ball;
  IPUi interface;

  IPPickup * pu_active = NULL;
  IPPickup * pu_onboard = NULL;
  BigBall pu_bigball;
  SmallBall pu_smallball;
  DrunkBall pu_drunkball;
  BarbBall pu_barbball;

  IPPickup * pickups[4] = {&pu_bigball,
                         &pu_smallball,
                         &pu_drunkball,
                         &pu_barbball};

  unsigned int playerscore = 0;

  Mix_Music * splashmusic;
  Mix_Music * music;

};

#endif
