//
//  tile.h
//  pixel_game
//
//  Created by gaoyuzhuo on 2022/1/27.
//

#ifndef PGtile_h
#define PGtile_h
#include <stdlib.h>
#include "SDL2/SDL.h"
#include "PGtype.h"

PGtile PGcreatTile(char* path,int x,int y,int w,int h,bool collision,int collideW,int collideH,bool interactive,int interactiveType);
PGtile PGinitTile(PGtile* aTile);

#endif /* tile_h */
