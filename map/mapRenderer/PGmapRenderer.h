//
//  PGmap.h
//  pixel_game
//
//  Created by gaoyuzhuo on 2022/1/28.
//

#ifndef PGrenderMap_h
#define PGrenderMap_h

#include <stdio.h>
#include "PGtype.h"
#include "PGtile.h"
#include "PGerror.h"

PGrenderMap PGcreatRenderMap(uint32_t height,uint32_t length);
int PGloadRenderMap(char* filePath,unsigned int starH,unsigned int starL,unsigned int endH,unsigned int endL);
int PGfreeRenderMap(PGrenderMap aMap);

#endif /* PGmap_h */
