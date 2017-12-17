#include <iostream>
#include "game.h"

#ifdef WINDOWS
int WinMain(){
#else
int main(int argc,char * argv[]){
#endif // WINDOWS
printf("Init Game\n");

  IPGame game;
  printf("Done");
  //game.gameLoop();
}

