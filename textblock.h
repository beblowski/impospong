#ifndef _IPTEXTBLOCK
#define _IPTEXTBLOCK
#include "respak.h"
#include <vector>

class IPTextBlock {
  std::vector<SDL_Texture *> createdText;
public:
  IPTextBlock();
  ~IPTextBlock();
  SDL_Texture * getText(SDL_Renderer *,std::string,TTF_Font *, SDL_Color color = {255,255,255});
  void resetBlock();
  void writeBlock(SDL_Renderer *,std::string,TTF_Font *, SDL_Color color = {255,255,255});
  void drawBlock(SDL_Renderer *);

  SDL_Texture * textblock = NULL;
  SDL_Rect pos;
  SDL_Rect lastpos;
  SDL_Rect newpos;

};

#endif
