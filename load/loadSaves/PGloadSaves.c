//
//  PGloadSaves.c
//  pixel_game
//
//  Created by gaoyuzhuo on 2022/1/28.
//

#include "PGloadSaves.h"
#include "PGerror.h"
#include <string.h>
#include "PGprogrammerHelper.h"
int PGloadSaves(char* filePath,PGloadSaveFile* var){
    //打开文件
    FILE* fp = NULL;
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
    int typeListOfFileHeader[5] = {32,32,64,32,32};
    PGmemoryAlocateToDifferentSizeOfVariable(fileHeader, sizeof(fileHeader), typeListOfFileHeader, 5,&(var->header.mapHeight),&(var->header.mapWidth),&(var->header.seed),&(var->header.whenCreat),&(var->header.versionWhenCreat));
    //读取文件变量
    uint8_t fileVariable[26];
    fread(fileVariable,sizeof(fileVariable),1,fp);
    int typeListOfFileVariable[6] = {8,64,32,64,8,32};
    PGmemoryAlocateToDifferentSizeOfVariable(fileVariable, sizeof(fileVariable), typeListOfFileVariable, 6,&(var->var.diffculty),&(var->var.gameDuration),&(var->var.newestVersion),&(var->var.storgeBasicID),&(var->var.numberOfWorld),&(var->var.numberOfRegisteredID));
    //读取房主信息
    //读取房主信息.读取房主ID
    char ownerID[21];
    fread(ownerID, sizeof(char), 20, fp);
    ownerID[20] = '\0';
    for(int i = 0;i < 20;i++){
        var->owner.ID[i] = ownerID[i];
    }
    //读取房主上次上次游戏和游戏版本时间信息
    uint32_t fileOwner[2];
    fread(fileOwner,sizeof(fileOwner),1,fp);
    var->owner.lastPlayTime = fileOwner[0];
    var->owner.lastPlayVersion = fileOwner[1];
    return 0;
}
