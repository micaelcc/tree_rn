#include "Criar_Vetores.h"
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>

/*
    Busca em Vetor
    Recebe um vetor, um numero e o tamanho do vetor e
    retorna 1 para caso encontre, 0 se não encontrar.
*/
int search_vet(int *vet, int num, int tam_max){
    int i;

    for(i=0;i<tam_max; i++){
        if(vet[i] == num)
            return 1;
    }

    return 0;
}

/*
    Funcao que gera vetor aleatorio.
    Recebe um n (tamanho), valor minimo
    e maximo para range. Retorna ponteiro
    para vetor.
*/
int * vet_random_n(int n, int min, int max){

    srand(time(NULL));
    int *vet = malloc(n*sizeof(int));
    int num;
    int i;

    for(i=0; i<n; i++){

        do{
            num = rand() % max;
        }while(search_vet(vet, num,i));

        vet[i] = num;
    }

    return vet;
}