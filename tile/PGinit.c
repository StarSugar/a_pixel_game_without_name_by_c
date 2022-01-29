//
//  PGinit.c
//  pixel_game
//
//  Created by gaoyuzhuo on 2022/1/27.
//

#include "PGinit.h"
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "PGerror.h"
PGSystem PGinit(char* title,int x,int y,int w,int h,uint32_t flags){
    
    //初始化SDL
    if(SDL_Init(SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER) < 0){
        PGsetError((char*)SDL_GetError());
        PGsystem.win = NULL;
        PGsystem.ren = NULL;
        return PGsystem;
    }
    
    //初始化SDL_image
    int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP;
    if( !( IMG_Init( imgFlags ) & imgFlags ) ){
        PGsetError(strcat("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError()));
        PGsystem.win = NULL;
        PGsystem.ren = NULL;
        return PGsystem;
    }
    
    //定义全局变量win
    SDL_Window* win;
    win = SDL_CreateWindow(title, x, y, w, h, flags);
    if(win == NULL){
        PGsetError((char*)SDL_GetError());
        PGsystem.win = NULL;
        PGsystem.ren = NULL;
        return PGsystem;
    }
    
    //定义全局变量ren
    SDL_Renderer* ren = NULL;
    SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(ren == NULL){
        PGsetError((char*)SDL_GetError());
        PGsystem.win = NULL;
        PGsystem.ren = NULL;
        return PGsystem;
    }
    
    //存入全局变量win和ren
    PGsystem.win = win;
    PGsystem.ren = ren;
    return PGsystem;
}
