#include "textblock.h"

IPTextBlock::IPTextBlock(){
  pos.w = 0;
  pos.h = 0;
  pos.x = 0;
  pos.y = 0;
}

SDL_Texture * IPTextBlock::getText(SDL_Renderer * renderer, std::string msg, TTF_Font * font, SDL_Color color){
  newpos.w = 0;
  newpos.h = 0;
  newpos.x = 0;
  newpos.y = 0;
  SDL_Surface * tSurf = TTF_RenderText_Solid(font, msg.c_str(), color);
  SDL_Texture * newText = SDL_CreateTextureFromSurface(renderer,tSurf);
  SDL_QueryTexture(textblock,NULL,NULL,&newpos.w,&newpos.h);
  SDL_FreeSurface(tSurf);
  if(!newText) return NULL;
  printf("pushback\n");
  createdText.push_back(newText);
  return newText;
}

void IPTextBlock::resetBlock(){
  if(textblock) SDL_DestroyTexture(textblock);
  pos.w = 0;
  pos.h = 0;
  pos.x = 0;
  pos.y = 0;
}

void IPTextBlock::writeBlock(SDL_Renderer * renderer, std::string msg, TTF_Font * font, SDL_Color color){
  resetBlock();
  SDL_Surface * tSurf = TTF_RenderText_Solid(font,msg.c_str(),color);
  if(tSurf){
    textblock = SDL_CreateTextureFromSurface(renderer,tSurf);
    SDL_FreeSurface(tSurf);
    if(textblock){
      SDL_QueryTexture(textblock,NULL,NULL,&pos.w,&pos.h);
    }
  }
}

void IPTextBlock::drawBlock(SDL_Renderer * renderer){
  if(textblock){
    SDL_RenderCopy(renderer,textblock,NULL,&pos);
    lastpos = pos;
  }
}

IPTextBlock::~IPTextBlock(){
  if(textblock) SDL_DestroyTexture(textblock);
  printf("Destroy textblock");
  for(int i = 0; i < createdText.size(); i++){
    if(createdText[i]) SDL_DestroyTexture(createdText[i]);
    printf("Destroy Texture\n");
  }
}
