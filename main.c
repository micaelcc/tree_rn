//compilando (linux e gcc): gcc -o main *.c
//executando (linux e gcc): ./main

#include <stdio.h>
#include "Tree_RN.h"
#include "Criar_Vetores.h"
#include <stdlib.h>
#include <limits.h>
#define NIL_KEY INT_MIN

extern const int N;
extern const int R;
extern NO * NIL;
extern NO * raiz;

int main(){

    NIL = malloc(sizeof(NO));

    NIL->cor = N;
    NIL->esq = NULL;
    NIL->dir = NULL;
    NIL->pai = NULL;
    NIL->key = NIL_KEY;


    for (int i = 0; i < 1000; i++) {
        int *vet;
        int *vet_2;
        int j;
        int aux = 0;

        raiz = NIL;


        //Vetor de numeros aleatorios, tamanho 10000, range (0/100000)
        vet = vet_random_n(10000, 0, 100000);
        //Inserindo valores aleatorios de "vet" em arv
        for (j = 0; j < 10000; j++){
            NO * z = create_no(vet[j], R);
            insertRN(z);
        }
        
        int tam = 0;
        
        count_no(raiz, &tam);
        
        //Verificando se os nos foram inseridos
        if (tam != 10000) {
            printf("Numero de nos incorreto. %d\n\n", tam);
            raiz = free_tree(raiz);
            return 0;
        }
        
        //Verificando se eh rn
        if(is_rn(raiz) == 0){
            printf("Arvore nao eh RN.\n");
            raiz = free_tree(raiz);
            return 0;
        }
        
        //Criando vetor de indexes
        vet_2 = vet_random_n(1000, 0, 9999);
        
        //Removendo valores, de acordo com o indice
        for (j = 0; j < 1000; j++){
            int ind = vet_2[j];
            NO * z = tree_search(vet[ind], raiz);
            delete_rn(z);
        }
        
        tam = 0;
        count_no(raiz, &tam);
        
        //Verificando tamanho da arvore apos remover
        if (tam != 9000) {
            printf("Numero de nos incorreto. %d\n\n", tam);
            raiz = free_tree(raiz);
            return 0;
        }
        
        //Verificando se eh rn
        if(is_rn(raiz) == 0){
            printf("Arvore nao eh RN.\n");
            raiz = free_tree(raiz);
            return 0;
        }

        raiz = free_tree(raiz);
    }

    printf("Arvores criadas.\n");
}
