#ifndef LISTA_DUPLA_H
#define LISTA_DUPLA_H
#include "listaSimples.h"
#include "listaCircular.h"
typedef struct hist{
    struct hist* prox;
    struct hist* ant;
    char isbn[11];
    char titulo[100];
    char cpf[12];
    char nome[25];
    int devolucao;
}hist;
typedef struct user{
    char cpf[12];
    char nome[25];
    struct hist* emprestimos;
}user;

hist* criar_historico();
int historico_vazio(hist* hst);
int usuario_pegou(user** usuario,Livro* livro);
int usuario_devolveu(user* usuario,Livro* livro);
void imprimir_historico(user* usuario);
#endif