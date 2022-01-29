//
//  PGmap.c
//  pixel_game
//
//  Created by gaoyuzhuo on 2022/1/28.
//

#include "PGrmapRenderer.h"
#include <stdlib.h>
PGrenderMap PGcreatRenderMap(uint32_t height,uint32_t length){
    PGtile* result = (PGtile*)malloc(sizeof(PGtile) * height * length);
    memset(result, 0, sizeof(PGtile) * height * length);
    return result;
}

int PGloadRenderMap(char* filePath,unsigned int starH,unsigned int starL,unsigned int endH,unsigned int endL){
    
    return 0;
}

int PGfreeRenderMap(PGrenderMap aMap){
    if(aMap == NULL){
        PGsetError("There is no memory in the Map.");
        return -1;
    }
    free(aMap);
    return 0;
}
