//
//  tile.c
//  pixel_game
//
//  Created by gaoyuzhuo on 2022/1/27.
//

#include "PGtile.h"
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "PGerror.h"
#include "PGinit.h"
#include "PGinit.h"


PGSystem PGsystem; //extern value

static uint32_t tileSign = 0;

SDL_Surface* initTileWithBMP(PGtile* aTile);
SDL_Surface* initTileWithSDL_image(PGtile* aTile);

PGtile PGcreatTile(char* path,int x,int y,int w,int h,bool collision,int collideW,int collideH,bool interactive,int interactiveType){
    PGtile result;
    result.uninitTile.path = path;
    result.uninitTile.w = w;
    result.uninitTile.h = h;
    result.uninitTile.x = x;
    result.uninitTile.y = y;
    result.uninitTile.collision = collision;
    result.uninitTile.collideH = collideH;
    result.uninitTile.collideW = collideW;
    result.uninitTile.interactive = interactive;
    result.uninitTile.interactiveType = interactiveType;
    result.uninitTile.sign = tileSign;
    tileSign += 1;
    return result;
}

PGtile PGinitTile(PGtile* aTile){
    SDL_Surface* sur = NULL;
    FILE* fp = NULL;
    fp = fopen(aTile->uninitTile.path,"rb");
    if(fp == NULL){
        char e[26] = "Unable to open the file.\0";
        PGsetError(e);
        return (PGtile)-1;
    }
    //通过文件头来判断文件类型
    char fileType[13] = "";
    fread(fileType, sizeof(fileType), 1, fp);
    //BMP如果是BMP类型的图片
    if(strncmp(fileType, "BM", strlen("BM")) == 0){
        sur = initTileWithBMP(aTile);
        if(sur == NULL){
            char* e;
            e = strcat("Image ", strcat(aTile->uninitTile.path, " was destroyed.\0"));
            PGsetError(e);
            return (PGtile)-1;
        }
    }
    //如果是JPEG、PNG或者TIFF类型的图片
    if(strncmp(fileType + 6, "JFIF", strlen("JFIF")) == 0 ||
       strncmp(fileType + 1, "PNG", strlen("PNG")) == 0 ||
       strncmp(fileType + 2, "*\0", strlen("*\0")) == 0) //这个是TIFF类型的判定
    {
        sur = initTileWithSDL_image(aTile);
        if(sur == NULL){
            char* e;
            e = strcat("Image ", strcat(aTile->uninitTile.path, " was destroyed.\0"));
            PGsetError(e);
            return (PGtile)-1;
        }
    }
    //webp的文件头比较特殊，是基于RIFF的
    if(strncmp(fileType, "RIFF", strlen("RIFF")) == 0){
        if(strncmp(fileType + 8, "WEBP", strlen("WEBP")) == 0){
            sur = initTileWithSDL_image(aTile);
            if(sur == NULL){
                char* e;
                e = strcat("Image ", strcat(aTile->uninitTile.path, " was destroyed.\0"));
                PGsetError(e);
                return (PGtile)-1;
            }
        }
    }
    //如果图片不是所需类型
    else{
        PGsetError("Expected BMP, PNG, JPEG, TIFF, WEBP.");
        return (PGtile)-1;
    }
    //裁剪得到的Surface
    SDL_Rect rect = {aTile->uninitTile.x,aTile->uninitTile.y,aTile->uninitTile.w,aTile->uninitTile.h};
    SDL_Surface* result = NULL;
    if(SDL_BlitScaled(sur,&rect,result,NULL) != 0){
        PGsetError((char*)SDL_GetError());
        return (PGtile)-1;
    }
    //得到texture
    SDL_Texture* tex = SDL_CreateTextureFromSurface(PGsystem.ren, result);
    aTile->initTile.tex = tex;
    return *aTile;
}

SDL_Surface* initTileWithBMP(PGtile* aTile){
    SDL_Surface* sur = NULL;
    sur = SDL_LoadBMP(aTile->uninitTile.path);
    if(sur == NULL){
        PGsetError((char*)SDL_GetError());
        return NULL;
    }
    return sur;
}

SDL_Surface* initTileWithSDL_image(PGtile* aTile){
    SDL_Surface* sur = NULL;
    sur = IMG_Load(aTile->uninitTile.path);
    if(sur == NULL){
        PGsetError((char*)SDL_GetError());
        return NULL;
    }
    return sur;
}
