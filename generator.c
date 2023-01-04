#include "generator.h"
#include <stdio.h>
#include <stdlib.h>

Instruction* generateRandomInstructions(int ramSize) {
    // 01|22|13|45 => isto é uma instrução
    // 02|33|12|01 => isto é outra instrução
            
    // 0 => salvar na memória
    // 1 => opcode => somar
    // 2 => opcode => subtrair
    //-1 => halt
    
    // 22 => significa um endereço da RAM (10 endereço) 
    // 13 => significa 2o endereço
    // 45 => significa 3o endereco
    //ramSize => ESTA FORA DO INTERVALO DE 0 A ramSize DA MEMÓRIA RAM

    Instruction* instructions = (Instruction*) malloc(10 * sizeof(Instruction));

    for (int i=0; i<9; i++){
        instructions[i].opcode = rand() % 4; //0, 1, 2, 3
        instructions[i].info1 = rand() % ramSize; //0 ... RAM_SIZE
        do {
            instructions[i].info2 = rand() % ramSize; //0 ... RAM_SIZE
        } while (instructions[i].info1 == instructions[i].info2);
        instructions[i].info3 = rand() % ramSize; //0 ... RAM_SIZE
    }
    
    //inserindo a ultima instrucao do programa que nao faz nada que presta
    instructions[9].opcode =-1;
    instructions[9].info1 = -1;
    instructions[9].info2 = -1;
    instructions[9].info3 = -1;
    
    return instructions;
}

Instruction* readInstructions(char* fileName, int* ramSize) {
    printf("FILE -> %s\n", fileName);
    FILE* file = fopen(fileName, "r"); // Abrindo arquivo no modo leitura
    
    if (file == NULL) {
        printf("Arquivo nao pode ser aberto.\n");
        exit(1);
    }

    int n, i = 0;
    fscanf(file, "%d %d", ramSize, &n);
    Instruction* instructions = (Instruction*) malloc(n * sizeof(Instruction));
    while (i < n) {
        fscanf(file, "%d %d %d %d", &instructions[i].opcode, &instructions[i].info1, &instructions[i].info2, &instructions[i].info3);
        i++;
    }
    fclose(file); // Fechando o arquivo

    return instructions;
}

Instruction* generateDivisionInstructions(int dividendo, int divisor)
{
    int qtdInstrucoes = 4;

    Instruction* instrucoes = (Instruction*) malloc(qtdInstrucoes * sizeof(Instruction));
    
    //Pegando o dividendo e colocando na posição 0 da RAM
    instrucoes[0].opcode = 0;
    instrucoes[0].info1 = dividendo;
    instrucoes[0].info2 = 0;

    //Pegando o divisor e colocando na posição 1 da RAM
    instrucoes[1].opcode = 0;
    instrucoes[1].info1 = divisor;
    instrucoes[1].info2 = 1;

    //Colocando 0 no quociente temporariamente na posição 2 da RAM
    instrucoes[2].opcode = 0;
    instrucoes[2].info1 = 0;
    instrucoes[2].info2 = 2;

    //Colocando 1 na posição 3 do vetor da ram, que será somado
    instrucoes[3].opcode = 0;
    instrucoes[3].info1 = 1;
    instrucoes[3].info2 = 3;
    
    //Operação de divisão em si
   // int quociente = divisor;
    for (int i = divisor; i <= dividendo; i+=divisor)
    {
        qtdInstrucoes++;
        instrucoes = realloc(instrucoes, qtdInstrucoes*sizeof(Instruction));

        instrucoes[qtdInstrucoes - 1].opcode = 1; //Soma
        instrucoes[qtdInstrucoes - 1].info1 = 2; //Posição do quociente
        instrucoes[qtdInstrucoes - 1].info2 = 3; //Posição do 1
        instrucoes[qtdInstrucoes - 1].info3 = 2; //Armazena a informação na posição do quociente   
    }

    //Criando a instrução para finalizar a máquina
    instrucoes = realloc(instrucoes, (qtdInstrucoes+1)*sizeof(Instruction));

    instrucoes[qtdInstrucoes].opcode = -1;
    instrucoes[qtdInstrucoes].info1 = -1;
    instrucoes[qtdInstrucoes].info2 = -1;
    instrucoes[qtdInstrucoes].info3 = -1;

    return instrucoes; 
}

Instruction* generateMultiplicationInstructions(int fator1, int fator2)
{
    int qtdInstrucoes = 3;

    Instruction* instrucoes = (Instruction*) malloc(qtdInstrucoes * sizeof(Instruction));

    //Pegando o fator 1 e colocando na posição 0 do vetor da RAM
    instrucoes[0].opcode = 0;
    instrucoes[0].info1 = fator1;
    instrucoes[0].info2 = 0;

    //Pegando o fator 2 e colocando na posição 1 do vetor da RAM
    instrucoes[1].opcode = 0;
    instrucoes[1].info1 = fator2;
    instrucoes[1].info2 = 1;

    //Colocando o fator 2 no lugar do resultado da multiplicação (posição 2 do vetor da RAM)
    instrucoes[2].opcode = 0;
    instrucoes[2].info1 = fator2;
    instrucoes[2].info2 = 2;

    //Operação de multiplicação em si
    for(int i = 1; i < fator1; i++)
    {
        qtdInstrucoes++;
        instrucoes = (Instruction*) realloc(instrucoes, qtdInstrucoes*sizeof(Instruction));
        //Soma
        instrucoes[qtdInstrucoes - 1].opcode = 1; 
        instrucoes[qtdInstrucoes - 1].info1 = 1; //Posição do fator2
        instrucoes[qtdInstrucoes - 1].info2 = 2; //Posição do resultado
        instrucoes[qtdInstrucoes - 1].info3 = 2; //Armazena a informação na posição do resultado   
    }

    //Criando a instrução para finalizar a máquina
    instrucoes = realloc(instrucoes, (qtdInstrucoes+1)*sizeof(Instruction));

    instrucoes[qtdInstrucoes].opcode = -1;
    instrucoes[qtdInstrucoes].info1 = -1;
    instrucoes[qtdInstrucoes].info2 = -1;
    instrucoes[qtdInstrucoes].info3 = -1;

    return instrucoes; 
}
