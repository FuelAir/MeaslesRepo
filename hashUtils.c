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
void loadWallet(int * wallet){
    FILE * pFile = fopen("data/blockchain.dat","rb");
    fseek(pFile, -1024L, SEEK_END);
    fread(wallet, sizeof(int), 256, pFile);
    fclose(pFile);
}

//Carrega o bloco com o indice informado
BlocoMinerado searchBlock(int index){
    //Retorna o bloco com os dados da caretira.
    //Se a busca não encontrar nenhum valor, retorna um bloco com valor -1 armazenado.

    BlocoMi