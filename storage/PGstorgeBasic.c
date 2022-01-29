//
//  PGstorgeBasic.c
//  pixel_game
//
//  Created by gaoyuzhuo on 2022/1/29.
//

#include "PGstorgeBasic.h"
#include <stdlib.h>
#include "PGprogrammerHelper.h"
#include "PGerror.h"
static uint64_t BasicID = 0;
PGstorgeBag PGcreatStorgeBag(unsigned int height,unsigned int width,uint32_t type){
    PGstorgeItem* mem = (PGstorgeItem*)malloc(sizeof(PGstorgeItem) * height * width);
    memset(mem, 0, width * height);
    PGstorgeBag res = {
        type,
        BasicID,
        height,
        width,
        mem,
    };
    BasicID += 1;
    return res;
}
int PGputItemToStorge(PGstorgeBag* aBag,unsigned int x,unsigned int y,unsigned int item){
    PAN(aBag);
    //还没有写item，所以空着
    return 0;
}
unsigned int PGgetItemFromStorge(PGstorgeBag* aBag,unsigned int x,unsigned int y){
    PAN(aBag);
    if(y < aBag->height && x < aBag->width){
        if(aBag->storgeBag[aBag->width * y + x].valueType == 0)
            return (aBag->storgeBag[aBag->width * y + x].val.number);
        else if(aBag->storgeBag[aBag->width * y + x].valueType == 1)
            return aBag->storgeBag[aBag->storgeBag[aBag->width * y + x].val.mainPosition].val.number;
        else PGsetError("PGgetItemFromStorge:There is nothing");
        return -1;
    }
    else{
        PGsetError("PGgetItemFromStorge:Asked beyond the scope.\0");
        return -1;
    }
}
int PGstorgeBasicUpdateBasicID(PGloadSaveFile* file){
    BasicID = file->var.storgeBasicID;
    return 0;
}
