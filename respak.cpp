#include "respak.h"

bool Respak::loadResfile(std::string filename){
  ZZIP_DIR * rfile = zzip_dir_open(filename.c_str(),0);
  if(!rfile){
    printf("Resource file [%s] not found\n",filename.c_str());
    if(koe) exit(-1);
    return false;
  }
  zzip_dir_close(rfile);
  resfilename = filename;
  return true;
}

SDL_Texture * Respak::loadTexture(std::string resname, SDL_Renderer * render){
  ZZIP_DIR * resfile = zzip_dir_open(resfilename.c_str(),0);
  ZZIP_FILE * resource = NULL;
  char * buf = NULL;

  SDL_RWops * rw;
  if(!resfile){
    fprintf(stderr,"Cannot open resource file.\n");
    if(koe) exit(-1);
    return NULL;
  }
  ZZIP_DIRENT dirent;
  while(zzip_dir_read(resfile,&dirent)){
    if(dirent.d_name == resname){
      resource = zzip_file_open(resfile,dirent.d_name,0);
      if(!resource){
        fprintf(stderr,"Unable to read from resource file.\n");
        zzip_dir_close(resfile);
        if(koe) exit(-1);
        return NULL;
      }
      buf = new char[dirent.st_size];
      zzip_ssize_t len = zzip_file_read(resource,buf,dirent.st_size);
      rw = SDL_RWFromMem(buf,len);
      SDL_Surface * surf = IMG_Load_RW(rw,0);

      SDL_Texture * tex = SDL_CreateTextureFromSurface(render,surf);
      SDL_FreeSurface(surf);
      SDL_FreeRW(rw);
      delete[] buf;
      zzip_dir_close(resfile);
      if(!tex){
        printf("Unable to load resource: %s\n",resname.c_str());
        printf("Error: %s\n",SDL_GetError());
        if(koe) exit(-1);
      }
      printf("Resource Found\n");
      return tex;
    }
  }
  fprintf(stderr,"Resource not found.\n");
  zzip_dir_close(resfile);
  if(koe) exit(-1);
  return NULL;
}

TTF_Font * Respak::loadTTF(std::string resname, int fontsize){
  ZZIP_DIR * resfile = zzip_dir_open(resfilename.c_str(),0);
  ZZIP_FILE * resource = NULL;
  char * buf = NULL;

  SDL_RWops * rw;
  if(!resfile){
    fprintf(stderr,"Cannot open resource file.\n");
    if(koe) exit(-1);
    return NULL;
  }
  ZZIP_DIRENT dirent;
  while(zzip_dir_read(resfile,&dirent)){
    if(dirent.d_name == resname){
      resource = zzip_file_open(resfile,dirent.d_name,0);
      if(!resource){
        fprintf(stderr,"Unable to read from resource file.\n");
        zzip_dir_close(resfile);
        if(koe) exit(-1);
        return NULL;
      }
      buf = new char[dirent.st_size];
      zzip_ssize_t len = zzip_file_read(resource,buf,dirent.st_size);
      rw = SDL_RWFromMem(buf,len);
      if(rw == NULL){
        fprintf(stderr,"SDLRW error: %s\n",SDL_GetError());
        delete[] buf;
        zzip_dir_close(resfile);
        if(koe) exit(-1);
        return NULL;
      }
      TTF_Font * tex = TTF_OpenFontRW(rw,1,fontsize);
      if(tex == NULL){
        fprintf(stderr,"Error opening font: %s\n",TTF_GetError());
        delete[] buf;
        zzip_dir_close(resfile);
        if(koe) exit(-1);
        return NULL;
      }
      //SDL_FreeRW(rw);
      //delete[] buf;   //freeing these seems to make it all crash
      if(!tex){
        printf("Unable to load resource: %s\n",resname.c_str());
        printf("Error: %s\n",SDL_GetError());
        if(koe) exit(-1);
        return NULL;
      }
      zzip_dir_close(resfile);
      return tex;
    }
  }
  fprintf(stderr,"Resource not found.\n");
  zzip_dir_close(resfile);
  if(koe) exit(-1);
  return NULL;
}

Mix_Music * Respak::loadMusic(std::string resname){
  ZZIP_DIR * resfile = zzip_dir_open(resfilename.c_str(),0);
  ZZIP_FILE * resource = NULL;
  char * buf = NULL;

  SDL_RWops * rw;
  Mix_Music * mus;
  if(!resfile){
    fprintf(stderr,"Cannot open resource file.\n");
    if(koe) exit(-1);
    return NULL;
  }
  ZZIP_DIRENT dirent;
  while(zzip_dir_read(resfile,&dirent)){
    if(dirent.d_name == resname){
      resource = zzip_file_open(resfile,dirent.d_name,0);
      if(!resource){
        fprintf(stderr,"Unable to read from resource file.\n");
        zzip_dir_close(resfile);
        if(koe) exit(-1);
        return NULL;
      }
      buf = new char[dirent.st_size];
      zzip_ssize_t len = zzip_file_read(resource,buf,dirent.st_size);
      rw = SDL_RWFromMem(buf,len);
      if(rw == NULL){
        fprintf(stderr,"SDLRW error: %s\n",SDL_GetError());
        delete[] buf;
        zzip_dir_close(resfile);
        if(koe) exit(-1);
        return NULL;
      }
      mus = Mix_LoadMUS_RW(rw,1);
      //SDL_FreeRW(rw);
      //delete[] buf;   //freeing these seems to make it all crash
      if(!mus){
        printf("Unable to load resource: %s\n",resname.c_str());
        printf("Error: %s\n",SDL_GetError());
        if(koe) exit(-1);
        return NULL;
      }
      zzip_dir_close(resfile);
      return mus;
    }
  }
  fprintf(stderr,"Resource not found.\n");
  zzip_dir_close(resfile);
  if(koe) exit(-1);
  return NULL;
}

Mix_Chunk * Respak::loadChunk(std::string resname){
  ZZIP_DIR * resfile = zzip_dir_open(resfilename.c_str(),0);
  ZZIP_FILE * resource = NULL;
  char * buf = NULL;

  SDL_RWops * rw;
  Mix_Chunk * chunk;
  if(!resfile){
    fprintf(stderr,"Cannot open resource file.\n");
    if(koe) exit(-1);
    return NULL;
  }
  ZZIP_DIRENT dirent;
  while(zzip_dir_read(resfile,&dirent)){
    if(dirent.d_name == resname){
      resource = zzip_file_open(resfile,dirent.d_name,0);
      if(!resource){
        fprintf(stderr,"Unable to load resource.\n");
        zzip_dir_close(resfile);
        if(koe) exit(-1);
        return NULL;
      }
      buf = new char[dirent.st_size];
      zzip_ssize_t len = zzip_file_read(resource,buf,dirent.st_size);
      rw = SDL_RWFromMem(buf,len);
      if(rw == NULL){
        fprintf(stderr,"SDLRW error: %s\n",SDL_GetError());
        delete[] buf;
        zzip_dir_close(resfile);
        if(koe) exit(-1);
        return NULL;
      }
      chunk = Mix_LoadWAV_RW(rw,1);
      //SDL_FreeRW(rw);
      //delete[] buf;   //freeing these seems to make it all crash
      if(!chunk){
        printf("Unable to load resource.\n");
        if(koe) exit(-1);
        return NULL;
      }
      zzip_dir_close(resfile);
      return chunk;
    }
  }
  fprintf(stderr,"Resource not found.\n");
  zzip_dir_close(resfile);
  if(koe) exit(-1);
  return NULL;
}

Respak::~Respak(){

}



