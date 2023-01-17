
#include <stdio.h>
#include <openssl/crypto.h>
#include <openssl/sha.h>

#include "mtwister.h"
#include "hashUtils.h"

//Macro
#define BUFFER_SIZE 16

//Variaveis Globais
MTRand randNumber;
int wallet[256] = {0};

//Gera Dados do Bloco - Recebe o vetor de char do bloco
void generateBlockData(unsigned char * data){
    unsigned long qtdTransacoes = (1 + (genRandLong(&randNumber) % 61)) * 3;
    for (int i = 3; i<=qtdTransacoes; i+=3){
        unsigned char endOrigem = (unsigned char) genRandLong(&randNumber) % 256;
        unsigned char endDst = (unsigned char) genRandLong(&randNumber) % 256;
        unsigned char qtdBitcoin = (unsigned char) (1 + (genRandLong(&randNumber) % 50));