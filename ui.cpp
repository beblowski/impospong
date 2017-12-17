#include "ui.h"

IPUi::IPUi(){
  hud_pos.x = 0;
}

void IPUi::getTex(Respak * respak,SDL_Renderer * renderer){
  rend_copy = renderer;
  hudback = respak->loadTexture("ui_back.png",renderer);
  lightglow = respak->loadTexture("lightglow.png",renderer);
  SDL_QueryTexture(hudback,NULL,NULL,&hud_pos.w,&hud_pos.h);
}

void setHUD(int lscore ,int rscore,std::string hudmsg = ""){

}

void IPUi::drawHUD(SDL_Renderer * renderer,IPPaddle * lpaddle, IPPaddle * rpaddle, IPPickup * active_pu){
  SDL_Rect lightpos;
  SDL_Color c_red = {(rand()%55 + 200), 0 ,0};
  SDL_Color c_grn = {0,(rand()%55 + 200), 0};
  char lscore[3];
  char rscore[3];
  sprintf(lscore,"%i",lpaddle->score);
  sprintf(rscore,"%i",rpaddle->score);
  uitext.writeBlock(renderer,lscore,scorefont,c_red);
  uitext.pos.y = screen_h - (ui_h / 2) - (uitext.pos.h / 2);
  uitext.pos.x = 30;

  lightpos = uitext.pos;
  lightpos.w += 16;
  lightpos.h += 16;
  lightpos.x -= 8;
  lightpos.y -= 8;
  SDL_SetTextureColorMod(lightglow,100,0,0);
  SDL_RenderCopy(renderer,lightglow,NULL,&lightpos);

  uitext.drawBlock(renderer);
  uitext.writeBlock(renderer,rscore,scorefont,c_red);
  uitext.pos.y = screen_h - (ui_h / 2) - (uitext.pos.h / 2);
  uitext.pos.x = screen_w - 30 - uitext.pos.w;

  lightpos = uitext.pos;
  lightpos.w += 16;
  lightpos.h += 16;
  lightpos.x -= 8;
  lightpos.y -= 8;
  SDL_SetTextureColorMod(lightglow,100,0,0);
  SDL_RenderCopy(renderer,lightglow,NULL,&lightpos);

  uitext.drawBlock(renderer);
  if(active_pu){
    uitext.writeBlock(renderer,active_pu->name,hudfont,c_grn);
    uitext.pos.y = screen_h - (ui_h / 2) - (uitext.pos.h / 2);
    uitext.pos.x = (screen_w / 2) - (uitext.pos.w / 2);

    lightpos = uitext.pos;
    lightpos.w += 16;
    lightpos.h += 16;
    lightpos.x -= 8;
    lightpos.y -= 8;
    SDL_SetTextureColorMod(lightglow,0,100,0);
    SDL_RenderCopy(renderer,lightglow,NULL,&lightpos);

    uitext.drawBlock(renderer);
  }
  SDL_RenderCopy(renderer,hudback,NULL,&hud_pos);
  //printf(" %i : %i : %i : %i\n",hud_pos.w,hud_pos.h,hud_pos.x,hud_pos.y);
}

void IPUi::centerText(std::string text, TTF_Font * font, SDL_Color color,SDL_Renderer * renderer){
  SDL_Surface * t_surf = TTF_RenderText_Solid(font,text.c_str(),color);
  SDL_Texture * t_text = SDL_CreateTextureFromSurface(renderer,t_surf);
  SDL_FreeSurface(t_surf);
}

IPUi::~IPUi(){
  printf("UIDestruct\n");
  if(hudback) SDL_DestroyTexture(hudback);
  if(lightglow) SDL_DestroyTexture(lightglow);
}
