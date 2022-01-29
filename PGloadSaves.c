//
//  PGloadSaves.c
//  pixel_game
//
//  Created by gaoyuzhuo on 2022/1/28.
//

#include "PGloadSaves.h"
#include "PGerror.h"
#include <string.h>
int PGloadSaves(char* filePath,PGloadSaveFile* var){
    //打开文件
    FILE fp = NULL;
    fp = fopen(filePath, "rb");
    if(fp == NULL){
        PGsetError(strcat("Can not open the file.", strcat(filePath, ".\0")));
        return -1;
    }
    //识别文件
    char sign[7] = "";
    fread(sign, sizeof(sign), 1, fp);
    sign[6] = '\0';
    if(strcmp(sign, "PGsave\0") != 0){
        PGsetError(strcat("Expected PGsave file, but not", strcat(filePath, ".\0")));
        return -1;
    }
    //读取文件
    //读取文件头
    uint32_t fileHeader[6];
    fread(fileHeader, sizeof(uint32_t), 1, fp);
    var->header.mapHeight = fileHeader[0];
    var->header.mapWidth = fileHeader[1];
    var->header.seed = ((uint64_t)fileHeader[2] << 32) + fileHeader[3];
    var->header.whenCreat = fileHeader[4];
    var->header.versionWhenCreat = fileHeader[5];
    //读取文件变量
    uint8_t fileVariable[18];
    fread(fileVariable,sizeof(fileVariable),1,fp);
    var->var.diffculty = fileVariable[0];
    var->var.gameDuration = ((uint64_t)fileVariable[1] << 56) + ((uint64_t)fileVariable[2] << 48) + ((uint64_t)fileVariable[3] << 40) + ((uint64_t)fileVariable[4] << 32) + ((uint64_t)fileVariable[5] << 24) + ((uint64_t)fileVariable[6] << 16) + ((uint64_t)fileVariable[7] << 8) + fileVariable[8];
    var->var.newestVersion = ((uint32_t)fileVariable[9] << 24) + ((uint32_t)fileVariable[10] << 16) + ((uint32_t)fileVariable[11] << 8) + fileVariable[12];
    var->var.numberOfWorld = fileVariable[13];
    var->var.numberOfRegisteredID = ((uint32_t)fileVariable[14] << 24) + ((uint32_t)fileVariable[15] << 16) + ((uint32_t)fileVariable[16] << 8) + fileVariable[17];
    //读取房主信息
    return 0;
}
