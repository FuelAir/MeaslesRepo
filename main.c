
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
    
    //Ultima Hash aceita gerada. No genesis o hash anterior é 0000...
    unsigned char hash [SHA256_DIGEST_LENGTH] = {0};

    //Zerar as carteiras antes de começar um novo blockchain
    for (int i = 0; i<256; i++){
        wallet[i] = 0;
    }

    BlocoMinerado buffer[BUFFER_SIZE];
    int cont = 0;
    
    //Arquivo Binário com os dados da blockchain
    FILE * pFile = fopen("data/blockchain.dat","wb");
    FILE * pFileText = fopen("data/blockchainText.txt","wt");

    for(int i = 1; i<=num_blocks; i++){

        BlocoNaoMinerado blocoAMinerar;
        //Gera os dados e minera o bloco.
        createBlock(&blocoAMinerar,i,hash);
        
        //Carrega o buffer 4096||512 bytes com o bloco.
        buffer[cont].bloco = blocoAMinerar;
        cpyhash(buffer[cont].hash, hash);
        
        //printhash(blocoAMinerar.hashAnterior);
        printhash(hash);

        //Se a quantidade de blocos for 16||2, então grava no arquivo.
        if (BUFFER_SIZE-1 == cont){
            fwrite(buffer,sizeof(BlocoMinerado),BUFFER_SIZE,pFile);
            fwrite(buffer,sizeof(BlocoMinerado),BUFFER_SIZE,pFileText);
            cont = 0;
        }else{
            cont ++;
        }
    }
    //Descarrega o buffer se tiver algo antes de finalizar.
    if(cont){
        fwrite(buffer,sizeof(BlocoMinerado),cont,pFile);
        fwrite(buffer,sizeof(BlocoMinerado),cont,pFileText);
        cont = 0;
    }

    fwrite(wallet,sizeof(int),256,pFile);//Grava as carteiras
    fclose(pFile);
    fclose(pFileText);
    printf("\n");
    printf("BlockChain Gerada com Sucesso!");
    printf("\n");
}

void menu(Wallet * w){
    int aux, z;

    do{
        printf("\n\t\t||Consultas||");
        printf("\n1-Imprimir dados de um bloco.");
        printf("\n2-Mostrar a quantidade de Bitcoins de um endereço.");
        printf("\n3-Mostrar a carteira com mais Bitcoins.");
        printf("\n4-Listar endereços em ordem crescente (Relativa a quantidade de bitcoins).");
        printf("\n5-Sair\n");

        scanf("%d", &z);

        switch(z){
            case 1:;
                BlocoMinerado blocoaux;
                do{
                    printf("\nInsira o bloco desejado:\n");
                    scanf("%d", &aux);