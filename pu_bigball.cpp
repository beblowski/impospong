#include "pu_bigball.h"

BigBall::BigBall() {
  name = "Big Ball";
}

void BigBall::drawPickup(SDL_Renderer * renderer){
  SDL_RenderCopy(renderer,putexture,NULL,&pos);
}

void BigBall::puEffector(IPBall * ball, IPPaddle * lpaddle, IPPaddle * rpaddle){
  bool addpos = true;
  Uint32 ctick = SDL_GetTicks();
  if(orig_h == 0) orig_h = ball->pos.h;
  if(orig_w == 0) orig_w = ball->pos.w;
  if(ctick - pickupstamp < pickup_dur){
    if(ball->pos.h < orig_h * 2) ball->pos.h++;
    if(ball->pos.w < orig_w * 2) ball->pos.w++;
  }
  else {
    if(ball->pos.w > orig_w) {
      ball->pos.w--;
      if(addpos) {
        ball->pos.x+= 1;
      }
    }
    if(ball->pos.h > orig_h) {
      ball->pos.h--;
      if(addpos) {
        ball->pos.y+= 1;
        addpos = false;
      }
      else {
        addpos = true;
      }
    }
    if((ball->pos.h == orig_h) && (ball->pos.w == orig_w)){
      deactivate(ball);
    }
  }
}

void BigBall::deactivate(IPBall * ball, IPPaddle * lpaddle, IPPaddle * rpaddle){
  if((ball->pos.h > orig_h) || (ball->pos.w > orig_w)){
    ball->pos.h = orig_h;
    ball->pos.w = orig_w;
  }
  active = false;
  onboard = false;
}

BigBall::~BigBall(){

}
