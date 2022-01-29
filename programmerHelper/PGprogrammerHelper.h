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
#define PAN(X) if(X == NULL){PGsetError("pointer X doesn't point to anything");return -1;}
#endif /* PGprogrammerHelper_h */
