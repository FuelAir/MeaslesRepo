#include <stdio.h>
#include <stdlib.h>
#include <openssl/sha.h>
#include <math.h>

#include "hashUtils.h"

void cpyhash(unsigned char * dst, unsigned char * org){
    for(i