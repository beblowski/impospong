#include "animate.h"

Animation::Animation(){

}

void Animation::setAnim(SDL_Texture * tex,unsigned short nf,unsigned short fr,short lp){
  numframes = nf;
  framesps = fr;
  loop = lp;
  framechunk = (1000/framesps);
  lastframechange = SDL_GetTicks();
  SDL_QueryTexture(tex,NULL,NULL,&img_w,&img_h);
  clip_chunk = img_w / numframes;
  clip.x = clip.y = 0;
  clip.h = img_h;
  clip.w = clip_chunk;
}

void Animation::stepAnim(){
  Uint32 ctick = SDL_GetTicks();
  if((ctick - lastframechange) > framechunk){
    loop++;
    if(loop > (numframes - 1)){
      loop = 0;
    }
    setClip();
    lastframechange = SDL_GetTicks();
  }
}

void Animation::setClip(){
  clip.x = (loop * clip_chunk);
}

Animation::~Animation(){

}
