#include "paddle.h"

IPPaddle::IPPaddle(){

}

void IPPaddle::getTex(SDL_Texture * ptexture,bool side = false){
  paddletex = ptexture;
  SDL_QueryTexture(paddletex,NULL,NULL,&pos.w,&pos.h);
  pos.y = (board_h / 2) - (pos.h / 2);
  paddle_target = pos.y;
  if(side) {
    this->flip = true;
    pos.x = board_w - pos.w;
    //printf("%i\n",pos.x);
  }
  else {
    this->flip = false;
    pos.x = 0;
  }
}

void IPPaddle::draw(SDL_Renderer * renderer){
//pos.x = 0; pos.y = 16; pos.w = 25; pos.h = 100;
 // printf("%i %i %i %i\n",pos.x,pos.y,pos.w,pos.h);
  if(pos.y < 0) pos.y = 0;
  if(pos.y > (board_h - pos.h)) pos.y = (board_h - pos.h);
  if(flip){
    SDL_RenderCopyEx(renderer,paddletex,NULL,&pos,NULL,NULL,SDL_FLIP_HORIZONTAL);
  }
  else {
    SDL_RenderCopy(renderer,paddletex,NULL,&pos);
  }
}

void IPPaddle::moveKey(){
  if(pos.y < 0 - (pos.h / 2)) pos.y = 0 - (pos.h / 2);
  if(pos.y > (board_h - pos.h)) pos.y = (board_h - pos.h);
  pos.y += paddle_vel;
}

void IPPaddle::moveMouse(int coord){
  paddle_target = coord - (pos.h / 2);
  pos.y = paddle_target;
}

void IPPaddle::moveAI(int bally){
  paddle_target = bally;
  if(paddle_vel < accelmax){
    paddle_vel += accelrate;
  }
  if(pos.y + (pos.h / 2) > (paddle_target + (pos.h / 3))){
    pos.y -= paddle_vel;
  }
  else if(pos.y + (pos.h / 2) < paddle_target - (pos.h/3)){
    pos.y += paddle_vel;
  }

}

void IPPaddle::setBoardSize(unsigned int w, unsigned int h){
  board_w = w;
  board_h = h;
}

IPPaddle::~IPPaddle(){
  if(paddletex) SDL_DestroyTexture(paddletex);
  if(rpak) rpak = NULL;
}
