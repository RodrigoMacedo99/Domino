#ifndef CONTROL_C
#define CONTROL_C

#include <stdio.h>
#include <stdlib.h>
#include "model.h"
#include <time.h>
#include "pilha.h"
#include "fila.h"
#include "lista_de.h"
#include "viwer.h"

/**
 * Função para criar peças de dominó.
 * Esta função gera peças de dominó aleatórias atribuindo valores aleatórios aos lados esquerdo e direito de cada peça.
 * Também atribui um ID único a cada peça.
 */
void criar_pecas (peca* vetor_pecas[]){
    int i, j;
    srand(time(NULL));

    // Gerando peças de dominó
    for(i = 0; i <= 6; i++ )
        for(j = 0; j <= 6; j++){
        
        peca *p = (peca*) malloc(sizeof(peca));
        p->lado_direito = i;
        p->lado_esquerdo = j;
        p->id_peca = rand() % 1000;
        
        //Atribuindo a peça ao vetor de peças
        vetor_pecas[i*7+j] = p; 
        //printf(" id_peca: %hd\n",  vetor_pecas[i*7+j]->id_peca);
    }
}

/**
 * Função para embaralhar as peças de dominó.
 * Esta função embaralha as peças de dominó de forma aleatória.
 */
void  embaralhar_alg_ord (peca* vetor_pecas[]){
    int i, j, min, tam = 28;
    peca *x;

    for (i=0; i<tam-1; i++){
        min = i;
        for (j=i+1; j<tam; j++){
            if (vetor_pecas[j]->id_peca < vetor_pecas[min]->id_peca)
                min = j;
        }

        //Troca de peças
        x = vetor_pecas[min];
        vetor_pecas[min] = vetor_pecas[i];
        vetor_pecas[i] = x;
    }
}

// Função para inicializar o jogo de dominó
void inicializar_pecas (tp_pilha *pilha_pecas){

    //Alocando memória para o vetor de peças
    peca **vetor_pecas = (peca**) malloc(28 * sizeof(peca*));
    for (int i = 0; i < 28; i++){
        vetor_pecas[i] = malloc(sizeof(peca));
    }

    //Criando e embaralhando as peças
    criar_pecas(vetor_pecas);
    embaralhar_alg_ord(vetor_pecas);
    
    //Empilhando as peças
    for (int i = 0; i < 28; i++){
        push(pilha_pecas, *vetor_pecas[i]);
    }
    //free(vetor_pecas);
}

//Separar as peças entre os jogadores
void separa_pecas_jogadores(tp_fila *fila_jogadores, tp_pilha *pilha_pecas){
    peca temp;
    jogador j;
    j.mao = inicializa_listad();

    for (int i = 0; i <= tamanho_fila(*fila_jogadores)-1; i++){
        fila_jogadores->item[i].mao = inicializa_listad();
        for(int j = 0; j <= 6; j++){
            pop(pilha_pecas, &temp);
            insere_listad_no_fim(fila_jogadores->item[i].mao, temp);
        }
    }
}

// configuração inicial do jogo
void configuracao_inicial(tp_pilha *pilha_pecas, tp_fila *fila_jogadores) {
    inicializa_pilha(pilha_pecas);
    inicializa_fila(fila_jogadores);
    inicializar_pecas(pilha_pecas);
    inicializar_jogadores(fila_jogadores, introducao());
    separa_pecas_jogadores(fila_jogadores, pilha_pecas);
}

// Função para jogar uma peça
/*void jogar_peca(tp_fila *jogador, tp_listad *mesa, int vez){
    peca p;
    remover_listad(jogador->item[vez].mao, p);

    if (p.lado_direito ==  mesa->fim->info.lado_esquerdo){
        insere_listad_no_fim(mesa, p);
    }else if (p.lado_esquerdo ==  mesa->ini->info.lado_direito){
        insere_listad_no_inicio(mesa, p);
    }
}  */


 /*// Função para verificar se o jogador pode jogar
int pode_jogar(tp_listad *mao, tp_listad *mesa){
    peca p;
    p = mao->ini->info;
    if (p.lado_direito ==  mesa->fim->info.lado_esquerdo){
        return 1;
    }else if (p.lado_esquerdo ==  mesa->ini->info.lado_direito){
        return 1;
    }
    return 0;
} */
/*void rodada_de_jogadores(tp_fila *fila_jogadores, tp_listad *mesa){
    int numero_de_jogadores = tamanho_fila(*fila_jogadores);
    for (int vez = 0; vez < numero_de_jogadores; vez++){
        jogar_peca(fila_jogadores, mesa, vez);
    }
}*/
void print_mao_jogadores(tp_fila *fila_jogadores) {
    int numero_de_jogadores = tamanho_fila(*fila_jogadores);
    for (int i = 0; i < numero_de_jogadores; i++) {
        printf("Jogador %d:\n", i+1);
        tp_listad *mao = fila_jogadores->item[i].mao;
        tp_no *atual = mao->ini;
        while (atual != NULL) {
            printf("Peca: %d|%d\n", atual->info.lado_esquerdo, atual->info.lado_direito);
            atual = atual->prox;
        }
        printf("\n");
    }
}
#endif