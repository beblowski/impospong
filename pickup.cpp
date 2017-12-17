#include "pickup.h"

IPPickup::IPPickup(){

}

void IPPickup::place(unsigned int tar_x, unsigned int tar_y){
  texturealpha = 255;
  SDL_QueryTexture(putexture,NULL,NULL,&pos.w,&pos.h);
  pos.x = tar_x;
  pos.y = tar_y;
  spawn_dur = (rand() % 10000) + 5000;
  spawnstamp = SDL_GetTicks();
  onboard = true;
}

void IPPickup::checkColl(IPBall * ball, IPPaddle * lpaddle, IPPaddle * rpaddle){
  Uint32 ctick = SDL_GetTicks();
  if(
  ( ball->pos.x + ball->pos.w > pos.x && ball->pos.x < pos.x + pos.w ) &&
  ( ball->pos.y + ball->pos.h > pos.y && ball->pos.y < pos.y + pos.h ) ){
    onboard = false;
    active = true;
    pickupstamp = SDL_GetTicks();
    pickup_dur = rand()%10000 + 6000;
  }
  if(ctick - spawnstamp > spawn_dur) onboard = false;
  if(ctick - spawnstamp > spawn_dur - 2000 ){
    texturealpha += alphamod;
    if(texturealpha > 255) texturealpha = 255;
    if(texturealpha < 0) texturealpha = 0;
    if(texturealpha == 0) alphamod = 7;
    if(texturealpha == 255) alphamod = -7;
    SDL_SetTextureAlphaMod(putexture,texturealpha);
  }
  else SDL_SetTextureAlphaMod(putexture,255);
  r = rand()%50 + 205;
  g = rand()%50 + 205;
  b=255;
  SDL_SetTextureColorMod(putexture,r,g,b);
}

IPPickup::~IPPickup(){
  if(putexture) SDL_DestroyTexture(putexture);
  if(putexture2) SDL_DestroyTexture(putexture2);
  if(putexture3) SDL_DestroyTexture(putexture3);
}
