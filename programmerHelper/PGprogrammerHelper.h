//
//  PGprogrammerHelper.h
//  pixel_game
//
//  Created by gaoyuzhuo on 2022/1/29.
//

#ifndef PGprogrammerHelper_h
#define PGprogrammerHelper_h

#include <stdio.h>
#include "PGerror.h"
//pointer and NULL full into a forever love
#define PAN(X) if(X == NULL){PGsetError("pointer X doesn't point to anything");return -1;}
int PGmemoryAlocateToDifferentSizeOfVariable(void* memory,uint32_t memoryLength,int* typeList,uint32_t typeListLength,...);
#endif /* PGprogrammerHelper_h */
