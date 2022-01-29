//
//  PGprogrammerHelper.c
//  pixel_game
//
//  Created by gaoyuzhuo on 2022/1/29.
//

#include "PGprogrammerHelper.h"
#include <stdarg.h>
int PGmemoryAlocateToDifferentSizeOfVariable(void* memory,uint32_t memoryLength,int* typeList,uint32_t typeListLength,...){
    //这个变量用来记录使用过的memory用了多少byte
    int byteMemoryLengthAtNow = 0;
    //这三个变量用来转化memory的类型
    uint8_t* u8pointer = memory;
    //可选参数变量的定义
    va_list argptr;
    va_start(argptr, typeListLength);
    for(int i = 0;i < typeListLength;i++){
        if(memoryLength > byteMemoryLengthAtNow){
            if(typeList[i] == 8){
                *(va_arg(argptr, int8_t*)) = u8pointer[byteMemoryLengthAtNow];
                byteMemoryLengthAtNow++;
            }
            if(typeList[i] == 32){
                *(va_arg(argptr, int32_t*)) = ((uint32_t)u8pointer[byteMemoryLengthAtNow] << 24) + ((uint32_t)u8pointer[byteMemoryLengthAtNow + 1] << 16) + ((uint32_t)u8pointer[byteMemoryLengthAtNow + 2] << 8) + (uint32_t)u8pointer[byteMemoryLengthAtNow + 3];
                byteMemoryLengthAtNow += 4;
            }
            if(typeList[i] == 64){
                *(va_arg(argptr, int64_t*)) = ((uint64_t)u8pointer[byteMemoryLengthAtNow] << 56) + ((uint64_t)u8pointer[byteMemoryLengthAtNow + 1] << 48) + ((uint64_t)u8pointer[byteMemoryLengthAtNow + 2] << 40) + ((uint64_t)u8pointer[byteMemoryLengthAtNow + 3] << 32) + ((uint64_t)u8pointer[byteMemoryLengthAtNow + 4] << 24) + ((uint64_t)u8pointer[byteMemoryLengthAtNow + 5] << 16) + ((uint64_t)u8pointer[byteMemoryLengthAtNow + 6] << 8) + ((uint64_t)u8pointer[byteMemoryLengthAtNow + 7]);
                byteMemoryLengthAtNow += 8;
            }
        }
        else{
            PGsetError("PGmemoryAlocateToDifferentSizeOfVariable:No enough space for the variables.\0");
            return -1;
        }
    }
    return 0;
}
