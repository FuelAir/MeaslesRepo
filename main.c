
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

        data[i-3] = endOrigem;
        data[i-2] = endDst;
        data[i-1] = qtdBitcoin;

        if((unsigned long) qtdBitcoin >= wallet[(unsigned long)endOrigem]){
            wallet[(unsigned long)endOrigem] = 0;
        }else{
            wallet[(unsigned long)endOrigem] -= (unsigned long)qtdBitcoin; 
        }
        wallet[(unsigned long)endDst] += (unsigned long)qtdBitcoin;
        
    }
    for (int i = qtdTransacoes; i<184; i++){
        data[i] = 0;
    }
}

//Calcula o nonce correto para o hash
void mineBlock(BlocoNaoMinerado * blocoAMinerar, unsigned char * h){
    unsigned char hash[SHA256_DIGEST_LENGTH];
    do{
        blocoAMinerar->nonce += 1;

        //Gera o hash do bloco.
        SHA256((unsigned char *)blocoAMinerar, sizeof(BlocoNaoMinerado),hash);

    //Verifica se os 3 primeiras posições do vetor são 0.
    }while(((unsigned long)hash[0] + (unsigned long)hash[1] + (unsigned long)hash[2] != 0));
    cpyhash(h,hash);
}

//Carrega todos os dados no bloco
void createBlock(BlocoNaoMinerado * blocoAMinerar, int i, unsigned char * hash){
    blocoAMinerar->numero = i;
    blocoAMinerar->nonce = -1;
    cpyhash(blocoAMinerar->hashAnterior,hash);
    generateBlockData(blocoAMinerar->data);
    mineBlock(blocoAMinerar,hash);
}

void generateBlocks(int num_blocks){