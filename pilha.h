#ifndef PILHA_H
#define PILHA_H
#include "listaSimples.h"
#include "listaDupla.h"
#include "listaCircular.h"
#include "fila.h"

typedef enum tipoacao{
    cadastrar, remover, emprestimo, devolucao 
}tipoacao;

typedef struct acao{
    tipoacao tipo;
    char isbn[11];
    char titulo[100];
    char autor[100];
    int quantidade;
    char cpf[12];
    char nome[25];
    int prioridade;
    struct acao* prox;
}acao;
acao* criar_pilha();
int pilha_vazia(acao* pilha);
acao* criar_acao(tipoacao tipo,char isbn[],char titulo[],char autor[],int quantidade,char cpf[],char nome[],int prioridade);
void empilhar(acao** pilha, acao* nova);
acao* desempilhar(acao** pilha);
int desfazer_acao(acao** pilha, Livro** lista, user* usuario, fila* prioridade_maxima, fila* prioridade_media, fila* prioridade_minima);


#endif