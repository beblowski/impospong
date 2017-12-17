#include "ball.h"

IPBall::IPBall(){
  velocX = IP_MAX_X_VELOC;
  velocY = 0;
  r = g = b =255;
}

void IPBall::getTex(SDL_Texture * balltexture){
  defaultballtex = balltexture;
  balltex = defaultballtex;
  SDL_QueryTexture(balltex,NULL,NULL,&pos.w,&pos.h);
  pos.y = (board_y / 2) - (pos.h / 2);
  pos.x = (board_x / 2) - (pos.w / 2);
  //animball.setAnim(balltexture,8,70,-1);
  //pos.w = animball.clip.w;
  //pos.h = animball.clip.h;
}

void IPBall::getAud(){
  //bounce1 = ("bounce1.ogg");
}

void IPBall::draw(SDL_Renderer * renderer){
  SDL_RendererFlip flipballtex;
  Uint32 thisticks = SDL_GetTicks();
  //int dif = (thisticks - lastticks) / 2;


  b = 255 - (velocX * 10);
  g = 255 - (b / 2) - (velocY * 2);
  if(b > 100) g = b = 255;

  SDL_SetTextureColorMod(balltex,r,g,b);
  //animball.setFPS((velocX * 5));
  //animball.stepAnim();
  rotation += (velocX * 4);
  if(rotation > 360) rotation = 0;
  if(direction) flipballtex = SDL_FLIP_HORIZONTAL;
  else flipballtex = SDL_FLIP_VERTICAL;
  SDL_RenderCopyEx(renderer,balltex,NULL,&pos,rotation,NULL,flipballtex);
  //SDL_RenderCopy(renderer,balltex,NULL,&pos);
  lastticks = thisticks;
}

void IPBall::moveBall(IPPaddle * lpaddle, IPPaddle * rpaddle){
  if( (pos.x + (pos.w) ) > rpaddle->pos.x &&
       pos.y > (rpaddle->pos.y - pos.h) &&
       pos.y < (rpaddle->pos.y + rpaddle->pos.h) ){
    direction = 0;
    //velocX++;
    calcVeloc(rpaddle);
  }
  else if( (pos.x) <= (lpaddle->pos.x + lpaddle->pos.w) &&
       pos.y > (lpaddle->pos.y - pos.h) &&
       pos.y < (lpaddle->pos.y + lpaddle->pos.h) ){
    direction = 1;
    //velocX += 1;
    calcVeloc(lpaddle);
  }
  else if ( pos.x > board_x ) {
    lpaddle->score++;
    outofbounds = true;
  }
  else if ( pos.x < 0 ){
    rpaddle->score++;
    outofbounds = true;
  }
  if(direction){
    pos.x += velocX;
  }
  else {
    pos.x -= velocX;
  }
  pos.y -= velocY;
  if(pos.y <= 0){
    pos.y = 0;
    if(velocY < IP_MAX_Y_VELOC) velocY += (velocX / 2);
    if(velocY > 0) velocY -= (velocY * 2);
    if(ballspin > 0) ballspin -= (ballspin * 2);
  }
  if((pos.y+pos.h) > board_y){
    pos.y = board_y - pos.h;
    if(velocY < IP_MAX_Y_VELOC) velocY += (velocX / 2);
    if(ballspin < 0) ballspin -= (ballspin * 2);
    //if(velocY > 0) velocY -= (velocY * 2);
    //if(velocY > -4 ) velocY = -4;
  }
  velocY += ballspin;
  if(ballspin > 0) ballspin += .004;
  if(ballspin < 0) ballspin -= .004;
  if(ballspin > ballspinmax){
    ballspin = ballspinmax;
  }
  else if(ballspin < ballspinmin){
    ballspin = ballspinmin;
  }
}

int IPBall::calcVeloc(IPPaddle * paddle){
  ballspin = 0;
  unsigned short steps = 13;
  double stepset = (paddle->pos.h / 2) / steps;
  int coll = (pos.y + (pos.h / 2)) - paddle->pos.y;
  if(coll < (paddle->pos.h / 2)) {
    for(int i = 0; i < steps; i++){
      if(coll > (stepset * i) - (pos.h) + 1 && coll < stepset * (i + 1)){
        velocY = steps - i;
        velocX = (i + 9);
        ballspin = (steps - i) * .02;
      }
    }
    if(velocX < velocY) velocY = velocX;
  }
  else {
    for(int i = 0; i < steps; i++){
      if(coll > (stepset * i) + (paddle->pos.h / 2) && (stepset * (i+1)) + (paddle->pos.h / 2)){
        velocY = i;
        velocX = i + 10;
        ballspin = i * .02;
        ballspin -= (ballspin * 2);
      }
    }
    if(velocX < velocY) velocY = velocX;
    velocY -= (velocY * 2);
  }
  /*
  else {
    for(int i = 0; i <= steps; i++){
      if(coll > (stepset * i) + (paddle->pos.y / 2) && coll < (stepset * (i + 1)) + (paddle->pos.y / 2) + (pos.h/2) ){
        velocY = i;
        33("%i : %i : %i : %i\n",i,coll,(stepset * i) + (paddle->pos.y / 2),(stepset * (i + 1)) + (paddle->pos.y / 2));
      }
    }
    velocY -= (velocY * 2);
  }
  */

  if(velocY == 0) {
    velocY = .000001;
  }
  //printf("%f : %f : %f\n",velocX,velocY,ballspin);
  Mix_PlayChannel(-1,bounce1,0);
  return 0;
}

IPBall::~IPBall(){
  printf("BallDestruct\n");
  if(balltex) SDL_DestroyTexture(balltex);
  if(defaultballtex) SDL_DestroyTexture(defaultballtex);
  if(bounce1) Mix_FreeChunk(bounce1);
}
