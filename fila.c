#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

fila* criar_fila()
{
    fila* nova = (fila*) malloc(sizeof(fila));
    nova->inicio = NULL;
    nova->fim = NULL;
    return nova;
}

int fila_vazia(fila* fl)
{
    if(fl->inicio == NULL && fl->fim == NULL)
        return 1;
    return 0;
}

int inserir_na_fila(fila* fl, char isbn[])
{
    no_fila* novo = (no_fila*) malloc(sizeof(no_fila));
    strcpy(novo->isbn, isbn);
    novo->prox = NULL;

    if(fila_vazia(fl))
    {
        fl->inicio = novo;
        fl->fim = novo;
        return 1;
    }
    fl->fim->prox = novo;
    fl->fim = novo;
    return 1;
}

int remover_da_fila(fila* fl, char isbn[])
{
    if(fila_vazia(fl))
        return 0;
    no_fila* aux = fl->inicio;
    strcpy(isbn, aux->isbn);
    fl->inicio = aux->prox;
    if(fl->inicio == NULL)
        fl->fim = NULL;
    free(aux);
    return 1;
}
int inserir_comeco(fila* fl,char isbn[])
{
    no_fila* novo = (no_fila*) malloc(sizeof(no_fila));
    strcpy(novo->isbn,isbn);
    if(fila_vazia(fl))
    {
        novo->prox = NULL;
        fl->inicio = novo;
        fl->fim = novo;
        return 1;
    }
    novo->prox = fl->inicio;
    fl->inicio = novo;
    return 1;
}

int remover_ultimo_da_fila(fila* fl)
{
    if(fila_vazia(fl))
        return 0;
    if(fl->inicio == fl->fim)
    {
        free(fl->inicio);
        fl->inicio = NULL;
        fl->fim = NULL;
        return 1;
    }
    no_fila* aux = fl->inicio;
    while(aux->prox != fl->fim)
        aux = aux->prox;
    free(fl->fim);
    aux->prox = NULL;
    fl->fim = aux;
    return 1;
}

void imprimir_fila(fila* fl)
{
    if(fila_vazia(fl))
    {
        printf("{ vazia }");
        return;
    }
    no_fila* aux = fl->inicio;
    printf("{ ");
    while(aux != NULL)
    {
        printf("%s ", aux->isbn);
        aux = aux->prox;
    }
    printf("}");
}