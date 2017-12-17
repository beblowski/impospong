#include "pu_drunkball.h"

DrunkBall::DrunkBall() {
  name = "XxX";
}

void DrunkBall::drawPickup(SDL_Renderer * renderer){
  SDL_RenderCopy(renderer,putexture,NULL,&pos);
}

void DrunkBall::puEffector(IPBall * ball, IPPaddle * lpaddle, IPPaddle * rpaddle){
  bool addpos = true;
  Uint32 ctick = SDL_GetTicks();
  if(ctick - pickupstamp < pickup_dur){
    double drunkness = rand()%23;
    drunkness = drunkness / 10;
    if(ball->pos.y > 400) ball->ballspin += drunkness;
    if(ball->pos.y < 400) ball->ballspin -= drunkness;
  }
  else {
    deactivate();
  }
}

void DrunkBall::deactivate(IPBall * ball, IPPaddle * lpaddle, IPPaddle * rpaddle){
  active = false;
}

DrunkBall::~DrunkBall(){

}
