#include "pu_barball.h"

BarbBall::BarbBall() {
  name = "Adrienne Barbeauball";
}

void BarbBall::drawPickup(SDL_Renderer * renderer){
  SDL_RenderCopy(renderer,putexture,NULL,&pos);
}

void BarbBall::puEffector(IPBall * ball, IPPaddle * lpaddle, IPPaddle * rpaddle){
  bool addpos = true;
  Uint32 ctick = SDL_GetTicks();
  if(ctick - pickupstamp < pickup_dur){
    if(ball->balltex != putexture2) {
      ball->balltex = putexture2;
      SDL_QueryTexture(putexture2,NULL,NULL,&ball->pos.w,&ball->pos.h);
    }
    ball->rotation = 0;
  }
  else {
    deactivate(ball,lpaddle,rpaddle);
  }
}

void BarbBall::deactivate(IPBall * ball, IPPaddle * lpaddle, IPPaddle * rpaddle){
  ball->balltex = ball->defaultballtex;
  SDL_QueryTexture(ball->defaultballtex,NULL,NULL,&ball->pos.w,&ball->pos.h);
  active = false;
}

BarbBall::~BarbBall(){

}
