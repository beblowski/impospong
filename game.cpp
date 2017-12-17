#include "game.h"

IPGame::IPGame(){
  interface.ui_h = uiheight;
  interface.screen_h = screen_h;
  interface.screen_w = screen_w;
  printf("Init SDL\n");
  if(SDL_Init(SDL_INIT_EVERYTHING) == -1 ){
    printf("SDL Init Failed: %s\n",SDL_GetError());
    exit(-1);
  }
  TTF_Init();
  if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048) < 0){
    printf("Audio Init Failed: %s\n",Mix_GetError());
  }

  printf("Load rpk\n");
  if(!respak.loadResfile("res.rpk")){
    printf("Failed to load res.rpk\n");
    exit(-1);
  }

  //splashmusic = Mix_LoadMUS("splashmusic.ogg");
  splashmusic = respak.loadMusic("splashmusic.ogg");
  music = respak.loadMusic("gamemusic.ogg");

  mainWindow = SDL_CreateWindow("ImpossiPong",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,screen_w,screen_h,SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(mainWindow,0,SDL_RENDERER_ACCELERATED|SDL_RENDERER_TARGETTEXTURE);
  floor = respak.loadTexture("floor.png", renderer);
  splash = respak.loadTexture("splash.png", renderer);
  if( !mainWindow ||
      !renderer ||
      !floor ||
      !splash){

        printf("Failed loading resources\n");
        exit(-1);
  }
  SDL_Rect sizer = {sizer.x=0, sizer.y=0, sizer.w=screen_w, sizer.h=screen_h};
  SDL_RenderCopy(renderer,floor,NULL,&sizer);
  SDL_RenderCopy(renderer,splash,NULL,&sizer);
  SDL_RenderPresent(renderer);
  Mix_VolumeMusic(musicvolume);
  Mix_PlayMusic( splashmusic, -1);
  SDL_Texture * paddle = respak.loadTexture("paddle.png", renderer);
  lpaddle.setBoardSize(board_w,board_h);
  lpaddle.getTex(paddle,0);
  rpaddle.setBoardSize(board_w,board_h);
  rpaddle.getTex(paddle,1);
  SDL_Texture * balltex = respak.loadTexture("ball.png", renderer);


  interface.hud_pos.y = screen_h - uiheight;
  interface.getTex(&respak,renderer);

  pu_bigball.putexture = respak.loadTexture("pu_bigball.png", renderer);
  pu_smallball.putexture = respak.loadTexture("pu_smallball.png", renderer);
  pu_drunkball.putexture = respak.loadTexture("pu_drunkball.png", renderer);
  pu_barbball.putexture = respak.loadTexture("pu_barbeau.png", renderer);
  pu_barbball.putexture2 = respak.loadTexture("pu_barbeau_ball.png", renderer);

  defaultfont = respak.loadTTF("default.ttf",18);
  interface.scorefont = respak.loadTTF("led_real.ttf",60);
  interface.hudfont = respak.loadTTF("led_real.ttf",40);

  ball.getTex(balltex);
  ball.bounce1 = respak.loadChunk("bounce1.ogg");
  ball.board_x = board_w;
  ball.board_y = board_h;

  if(Mix_PlayingMusic()) Mix_HaltMusic();
  mainLoop();
}

void IPGame::mainLoop(){
  while(stmainloop){
    if(stsplashloop) splashLoop();
    if(stgameloop) gameLoop();
    if(stdemoloop) demoLoop();
  }
}

void IPGame::splashLoop(){
  SDL_Rect sizer = {sizer.x=0, sizer.y=0, sizer.w=screen_w, sizer.h=screen_h};
  while(stsplashloop){
    splashEvents();
    if(!Mix_PlayingMusic()) Mix_PlayMusic(splashmusic,0);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,floor,NULL,&sizer);
    SDL_RenderCopy(renderer,splash,NULL,&sizer);
    gtext.drawBlock(renderer);
    SDL_RenderPresent(renderer);
    frameCap();
    if(!Mix_PlayingMusic()) {
      stdemoloop = true;
      stsplashloop = false;
    }
  }
  if(Mix_PlayingMusic()) Mix_HaltMusic();
}

void IPGame::gameLoop(){
  SDL_SetRelativeMouseMode(SDL_TRUE);
  if(Mix_PlayingMusic()) Mix_HaltMusic();
  if(!Mix_PlayingMusic()) Mix_PlayMusic(music,-1);
  resetGame();
  while(stgameloop){
    gameEvents();
    if(!ball.direction) lpaddle.moveAI(ball.pos.y);
    else lpaddle.paddle_vel = 0;
    ball.moveBall(&lpaddle, &rpaddle);
    if(ball.outofbounds == true){
      ball.outofbounds = false;
      waitTicks(1000);
      resetBoard();
    }
    if(rpaddle.paddle_vel != 0 ) rpaddle.moveKey();
    drawFrame();
    frameCap();
  }
  if(Mix_PlayingMusic()) Mix_HaltMusic();
  SDL_SetRelativeMouseMode(SDL_FALSE);
}

void IPGame::demoLoop(){
  if(Mix_PlayingMusic()) Mix_HaltMusic();
  if(!Mix_PlayingMusic()) Mix_PlayMusic(music,0);
  resetGame();
  while(stdemoloop){
    demoEvents();
    if(!ball.direction) {
      lpaddle.moveAI(ball.pos.y);
      rpaddle.paddle_vel = 0;
    }
    else {
      rpaddle.moveAI(ball.pos.y);
      lpaddle.paddle_vel = 0;
    }
    ball.moveBall(&lpaddle, &rpaddle);
    if(ball.outofbounds == true){
      ball.outofbounds = false;
      resetBoard();
    }
    drawFrame();
    frameCap();
    if(!Mix_PlayingMusic()) {
      stsplashloop = true;
      stdemoloop = false;
    }
  }
  if(Mix_PlayingMusic()) Mix_HaltMusic();
}

void IPGame::frameCap(){
  unsigned short ticksbetweenframes = (1000/framerate);
  Uint32 currenttick = SDL_GetTicks();
  while(currenttick - lastframetick < ticksbetweenframes){
    SDL_Delay(1);
    currenttick = SDL_GetTicks();
  }
  lastframetick = SDL_GetTicks();
  if(musicvolmod != 0){
    musicvolume += musicvolmod;
    if(musicvolume < 0) musicvolume = 0;
    if(musicvolume > 128) musicvolume = 128;
    Mix_VolumeMusic(musicvolume);
  }
}

void IPGame::waitTicks(unsigned int milli){
  Uint32 ticks = SDL_GetTicks();
  while((stgameloop || stdemoloop) && ticks + milli > lastframetick){
    while(SDL_PollEvent(&event)){
      globalEvents();
    }
    if(stdemoloop) demoEvents();
    drawFrame();
    frameCap();
  }
}

void IPGame::gameEvents(){
  while(SDL_PollEvent(&event)){
    globalEvents();
    switch(event.type){

      case SDL_KEYDOWN:
        switch(event.key.keysym.sym){
          case SDLK_DOWN:
          case SDLK_LEFT:
          case SDLK_a:
          case SDLK_s:
            if(rpaddle.paddle_vel < 30)rpaddle.paddle_vel = 20;
            break;
          case SDLK_UP:
          case SDLK_RIGHT:
          case SDLK_d:
          case SDLK_w:
            if(rpaddle.paddle_vel > -30)rpaddle.paddle_vel = -20;
            break;
          case SDLK_q:
            stsplashloop = true;
            stgameloop = false;
            break;
        }
        break; //SDL_KEYDOWN

      case SDL_KEYUP:
        switch(event.key.keysym.sym){
          case SDLK_UP:
          case SDLK_DOWN:
          case SDLK_RIGHT:
          case SDLK_LEFT:
          case SDLK_a:
          case SDLK_w:
          case SDLK_s:
          case SDLK_d:
            rpaddle.paddle_vel = 0;
            break;
        }
        break; //SDL_KEYUP

      case SDL_MOUSEMOTION:
        int mousecoord[2];
        SDL_GetMouseState(&mousecoord[0],&mousecoord[1]);
        rpaddle.moveMouse(mousecoord[1]);
        break; //SDL_MOUSEMOTION
    }
  }
}

void IPGame::demoEvents(){
  while(SDL_PollEvent(&event)){
    const char * keypressed;
    keypressed = SDL_GetKeyName(event.key.keysym.sym);
    int num = atoi(keypressed);
    globalEvents();
    switch(event.type){

      case SDL_KEYDOWN:
        switch(event.key.keysym.sym){
          case SDLK_PERIOD:
            if(framerate < 5000) framerate++;
            break;
          case SDLK_COMMA:
            if(framerate > 1) framerate--;
            break;
          case SDLK_r:
            framerate = IP_MAX_FRAMERATE;
            break;
          case SDLK_0:
            printf("%i\n",num);
            puPlacer(0);
            break;
          case SDLK_1:
            puPlacer(1);
            break;
          case SDLK_2:
            puPlacer(2);
            break;
          case SDLK_3:
            puPlacer(3);
            break;
          default:
            stsplashloop = true;
            stdemoloop = false;
            break;
        }
        break; //SDL_KEYDOWN
    }
  }
}

void IPGame::splashEvents(){
  while(SDL_PollEvent(&event)){
    globalEvents();
    switch(event.type){
      case SDL_KEYDOWN:
        switch(event.key.keysym.sym){
          case SDLK_RETURN:
          case SDLK_RETURN2:
          case SDLK_KP_ENTER:
            stgameloop = true;
            stsplashloop = false;
            break;
        }
        break; //SDL_KEYDOWN
    }
  }
}

void IPGame::globalEvents(){
  switch(event.type){

    case SDL_QUIT:
    //exit(0);
      stmainloop = false;
      stgameloop = false;
      stsplashloop = false;
      stdemoloop = false;
      break;

    case SDL_KEYDOWN:
      switch(event.key.keysym.sym){
        case SDLK_UNDERSCORE:
        case SDLK_MINUS:
          musicvolmod = -1;
          break;
        case SDLK_PLUS:
        case SDLK_EQUALS:
          musicvolmod = 1;
          break;
        case SDLK_q:
          if(stgameloop){
            stgameloop = false;
            stsplashloop = true;
          }
      }
      break; //SDL_KEYDOWN

    case SDL_KEYUP:
      switch(event.key.keysym.sym){
        case SDLK_UNDERSCORE:
        case SDLK_MINUS:
        case SDLK_PLUS:
        case SDLK_EQUALS:
          musicvolmod = 0;
          break;
      }
      break; //SDL_KEYUP
  }
}

void IPGame::puPlacer(int pu){
  Uint32 ctick = SDL_GetTicks();
  if( (!pu_onboard && pickupwait < ctick - lastpickupdrop) || pu >= 0 && !pu_active){
    int tar_x = rand()%board_w;
    int tar_y = rand()%board_h;
    if(pu < 0) pu = rand()%NUM_PICKUPS;
    if(pickups[pu] != NULL){
      pu_onboard = pickups[pu];
      pu_onboard->place(tar_x,tar_y);
      lastpickupdrop = SDL_GetTicks();
      pickupwait = rand()%60000 + 10000;
    }
  }
}

void IPGame::puCheck(){
  if(!pu_onboard && !pu_active) {
    puPlacer();
  }
  if(pu_onboard) {
    if(pu_onboard->onboard == true){
      pu_onboard->checkColl(&ball,&lpaddle,&rpaddle);
      pu_onboard->drawPickup(renderer);
    }
    else {
      if(pu_onboard->active == true){
        pu_active = pu_onboard;
      }
      pu_onboard = NULL;
    }
  }
  if(pu_active){
    if(pu_active->active == true){
      pu_active->puEffector(&ball,&lpaddle,&rpaddle);
    }
    else {
      pu_active = NULL;
    }
  }
}

void IPGame::drawFrame(){
  ren_r = rand()&200 + 55;
  ren_g = rand()&200 + 55;
  ren_b = rand()&200 + 55;
  SDL_RenderClear(renderer);
  //SDL_SetRenderDrawColor(renderer,ren_r,ren_g,ren_b,255);
  SDL_Rect sizer = {sizer.x=0, sizer.y=0, sizer.w=board_w, sizer.h=board_h};
  SDL_RenderCopy(renderer,floor,NULL,&sizer);
  puCheck();
  lpaddle.draw(renderer);
  rpaddle.draw(renderer);
  ball.draw(renderer);
  if(stgameloop || stdemoloop) {
    interface.drawHUD(renderer,&lpaddle,&rpaddle,pu_active);
  }
  drawDebug();
  SDL_RenderPresent(renderer);
}

void IPGame::resetGame(){
  ball.ballspin = 0;
  lpaddle.score = 0;
  rpaddle.score = 0;
  if(pu_active){
    pu_active->deactivate(&ball,&lpaddle,&rpaddle);
    pu_active = NULL;
  }
  if(pu_onboard){
    pu_onboard->onboard = false;
    pu_onboard = NULL;
  }
  framerate = IP_MAX_FRAMERATE;
  resetBoard();
}

void IPGame::resetBoard(){
  rpaddle.paddle_vel = 0;
  ball.velocX = IP_MIN_X_VELOC;
  ball.velocY = IP_MIN_Y_VELOC;
  lpaddle.moveMouse((board_h / 2));
  rpaddle.moveMouse((board_h / 2));
  ball.direction = (rand() % 2);
  ball.pos.x = ((board_w / 2) - (ball.pos.w / 2));
  ball.pos.y = ((board_h / 2) - (ball.pos.h / 2));
  drawFrame();
  waitTicks(3000);
  if(stgameloop) SDL_WarpMouseInWindow(mainWindow,(board_w / 2),(board_h / 2));
}

void IPGame::drawDebug(){
  if(showdebug){

  }
}

IPGame::~IPGame(){
  printf("GameDestruct\n");
  pu_active = NULL;
  pu_onboard = NULL;
  TTF_CloseFont(defaultfont);
  SDL_DestroyWindow(mainWindow);
  SDL_DestroyTexture(floor);
  SDL_DestroyTexture(splash);
  SDL_DestroyRenderer(renderer);
  Mix_FreeMusic(music);
  Mix_FreeMusic(splashmusic);
  TTF_Quit();
  Mix_Quit();
  SDL_Quit();

}
