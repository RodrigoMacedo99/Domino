#ifndef FILA_H
#define FILA_H

#include <stdio.h>
#include "lista_de.h"
#include "model.h"
#define MAX 28


typedef struct {
    jogador item[MAX];
    int ini, fim;
 // int tam;
} tp_fila;

void inicializa_fila(tp_fila *f) {
    f->ini = f->fim = MAX-1;
    //f->tam=0;
}

int fila_vazia(tp_fila *f){
    if(f->ini == f->fim) return 1;
    return 0;
}

int proximo (int pos){
    if(pos== MAX-1) return 0;
    return ++pos;
}

int fila_cheia (tp_fila *f){
    if(proximo(f->fim)==f->ini)
        return 1;
    return 0;
}

int insere_fila (tp_fila *f, jogador e){
    if(fila_cheia(f)) 
        return 0; //Não foi possível adicionar a fila
    /*if (f->item[f->fim].mao != NULL && f->item[f->ini].mao != NULL)
        f->item[f->fim].mao = inicializa_listad();*/
    f->fim = proximo(f->fim);
    f->item[f->fim]=e;
 // f->tam++;
    return 1;
}

int remove_fila (tp_fila *f, jogador *e){
    if(fila_vazia(f)) 
        return 0; //Não foi possível remover da fila
    f->ini = proximo(f->ini);
    *e = f->item[f->ini];
    //f->tam--;
    return 1;
}

/*void inicio_fila(tp_fila *f){
    if(fila_vazia(f)){
        printf("Fila vazia\n");
        return;
    }
    jogador e = f->item[f->ini];
    printf("Informações do dado no início da fila:\n");
    printf("ID: %hd\n", e.id_do_jogador);
    printf("Nome: %s\n", e.nome);
}*/

//Tamanho da fila
 int tamanho_fila(tp_fila f){
    short int cont=0;
	jogador e;
    while(!fila_vazia(&f)){
        remove_fila(&f, &e);
        cont++;
    }	
    return cont;
 }

//Imprime a fila
void imprime_fila (tp_fila f){
    printf("id| nome  | mao");
    printf("\n--+------+---------------------------\n");
    for(int i = 0; i < tamanho_fila(f); i++){
        printf("%hd | %s | ", f.item[i].id_do_jogador, f.item[i].nome);
        imprime_listad(f.item[i].mao, 1);
    }
    system("pause");
    system("cls");
}

// Duas opções de código do tamanho_fila     
/*int tamanho_fila(tp_fila *f){
	if (fila_vazia(f)) return 0;
	if (f->ini < f->fim) return f->fim - f->ini;
	return MAX - 1 - f->ini + f->fim + 1;
 }*/  

//  libera memoria alocada
void libera_memoria(tp_fila *jogadores) {
    jogador j;
    while (!fila_vazia(jogadores)) {
        remove_fila(jogadores, &j);
        // Libera a memória para a mão do jogador
        tp_listad *atu = j.mao;
        tp_listad *p;
        while (atu != NULL) {
            p = atu->fim;
            free(atu);
            atu = p;
        }
        // Libera a memória para a estrutura do jogador
        free(j.mao);
    }
}

#endif // FILA_H
