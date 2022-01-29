//
//  error.c
//  pixel_game
//
//  Created by gaoyuzhuo on 2022/1/27.
//

#include "PGerror.h"
#include <string.h>
static char PGerror[300];
int PGsetError(char* error){
    unsigned long length = strlen(error);
    if(length > 100){
        PGsetError("The setted error is too long.\0");
        return -1;
    }
    int i = 0;
    while(error[i] != '\0'){
        PGerror[i] = error[i];
        i += 1;
    }
    return 0;
}

char* PGgetError(void){
    return PGerror;
}
