#include <stdio.h>
#include <stdlib.h>
#include <openssl/sha.h>
#include <math.h>

#include "hashUtils.h"

void cpyhash(unsigned char * dst, unsigned char * org){
    for(int i = 0; i<SHA256_DIGEST_LENGTH; i++){
        dst[i]=org[i];
    }
}

void printhash(unsigned char * hash){
    for(int i = 0; i<SHA256_DIGEST_LENGTH; i++){
        printf("%02x", hash[i]);
    }
    printf("\n");
}

//Carrega o vetor com os valores de cada carteira da blockchain
void loadWallet(int * wallet