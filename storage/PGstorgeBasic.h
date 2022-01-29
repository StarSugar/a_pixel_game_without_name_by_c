//
//  PGstorgeBasic.h
//  pixel_game
//
//  Created by gaoyuzhuo on 2022/1/29.
//

#ifndef PGstorgeBasic_h
#define PGstorgeBasic_h

#include <stdio.h>
#include "PGtype.h"
#include "PGloadSaves.h"
PGstorgeBag PGcreatStorgeBag(unsigned int height,unsigned int width,uint32_t type);
int PGputItemToStorge(PGstorgeBag* aBag,unsigned int x,unsigned int y,unsigned int item);
unsigned int PGgetItemFromStorge(PGstorgeBag* aBag,unsigned int x,unsigned int y);
int PGstorgeBasicUpdateBasicID(PGloadSaveFile* file);
#endif /* PGstorgeBasic_h */
