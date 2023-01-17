
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