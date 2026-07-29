#ifndef FILA_H
#define FILA_H
#include "listaSimples.h"
#include "listaDupla.h"
#include "listaCircular.h"

typedef struct no_fila{
    char isbn[11];
    struct no_fila* prox;
}no_fila;

typedef struct fila{
    no_fila* inicio;
    no_fila* fim;
}fila;

fila* criar_fila();
int fila_vazia(fila* fl);
int inserir_na_fila(fila* fl, char isbn[]);
int remover_da_fila(fila* fl, char isbn[]);
void imprimir_fila(fila* fl);
int inserir_comeco(fila* fl,char isbn[]);
int remover_ultimo_da_fila(fila* fl);
#endif