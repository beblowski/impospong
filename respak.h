#ifndef RESPAK_H
#define RESPAK_H
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <zzip/lib.h>
#include <stdio.h>
#include <cstring>
#include <iostream>
#include <zzip/lib.h>

class Respak {
    std::string resfilename;
    bool koe = true;
  public:
    ~Respak();
    bool loadResfile(std::string);
    SDL_Texture * loadTexture(std::string, SDL_Renderer*);
    TTF_Font * loadTTF(std::string,int);
    Mix_Music * loadMusic(std::string);
    Mix_Chunk * loadChunk(std::string);
};

#endif
