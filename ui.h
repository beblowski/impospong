#ifndef _IPUI
#define _IPUI
#include "respak.h"
#include "textblock.h"
#include "pickup.h"

class IPUi{

  IPTextBlock uitext;
  SDL_Renderer * rend_copy;

public:
  IPUi();
  ~IPUi();
  void getTex(Respak *,SDL_Renderer *);
  void centerText(std::string, TTF_Font *, SDL_Color, SDL_Renderer *);
  void setHUD(int,int,std::string hudmsg = "");
  void drawHUD(SDL_Renderer *,IPPaddle *, IPPaddle *, IPPickup *);

  SDL_Rect hud_pos;
  SDL_Texture * hudback;
  SDL_Texture * lightglow;
  TTF_Font * scorefont;
  TTF_Font * hudfont;

  int screen_h, screen_w;
  int ui_h;
};

#endif
