//
//  PGtype.h
//  pixel_game
//
//  Created by gaoyuzhuo on 2022/1/27.
//

#ifndef PGtype_h
#define PGtype_h

#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL.h"

//logic
#define bool uint8_t
#define true 0xff
#define false 0x00

// uninitTile
typedef struct{
    uint32_t sign; //每种 tile 的标志
    char* path;
    int x;
    int y;
    int w;
    int h;
    bool collision;
    int collideW;
    int collideH;
    bool interactive;
    int interactiveType;
} PGUninitTile;

// initTile
typedef struct{
    int sign;
    SDL_Texture* tex;
    int x;
    int y;
    int w;
    int h;
    bool collision;
    int collideW;
    int collideH;
    bool interactive;
    int interactiveType;
} PGInitTile;

//tile
typedef union{
    PGUninitTile uninitTile;
    PGInitTile initTile;
    int error;
} PGtile;

//map
#define PGrenderMap PGtile*

//system
typedef struct{
    SDL_Window* win;
    SDL_Renderer* ren;
    SDL_Event event;
} PGSystem;

typedef struct{
    uint32_t mapHeight;
    uint32_t mapWidth;
    uint64_t seed;
    uint32_t whenCreat;
    uint32_t versionWhenCreat;
} PGsaveFileheader;

typedef struct{
    uint8_t diffculty;
    uint64_t gameDuration;
    uint32_t newestVersion;
    uint8_t numberOfWorld;
    uint32_t numberOfRegisteredID;
} PGsaveFileVariable;

typedef struct{
    char ID[20];
    uint32_t thirsty;
    /*
    uint32_t strenth;
    uint32_t thirsty;
    ...
     */
    uint32_t lastPlayTime;
    uint32_t lastPlayVersion;
} PGsavesFilePlayerImformation;

typedef struct{
    char ID[20];
    uint32_t thirsty;
    /*
    uint32_t strenth;
    uint32_t thirsty;
    bool BossI;
    bool BossII;
    ...
     */
    uint32_t lastPlayTime;
    uint32_t lastPlayVersion;
} PGsavesFileOwnerImformation;

typedef struct{
    PGsaveFileheader header;
    PGsaveFileVariable var;
    PGsavesFileOwnerImformation owner;
} PGloadSaveFile;

#endif /* PGtype_h */
