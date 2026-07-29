#include "listaCircular.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


prioridade* criar_prio()
{
    return NULL;
}

int prio_vazia(prioridade* lst)
{
    if(lst == NULL)
        return 1;
    return 0;
}

int inserir_pessoa_prio(prioridade** lst, char cpf[])
{
    prioridade* novo = (prioridade*) malloc(sizeof(prioridade));
    strcpy(novo->cpf,cpf);
    if(*lst == NULL)
    {
        novo->prox = novo;
        *lst = novo;
        return 1;
    }
    novo->prox = (*lst)->prox;
    (*lst)->prox = novo;
    *lst = novo;
    return 1;
}

int andar_prio(prioridade** lst)
{
    if((*lst) == NULL)
        return 0;
    prioridade* aux = (*lst)->prox;
    (*lst)->prox = aux->prox;
    free(aux);
    return 1;
}

void print_prio(prioridade* lst)
{
    if(lst==NULL)
    {
        printf("\n====Fila de prioridade vazia====\n");
        return ;
    }
    prioridade* aux = lst->prox;
    printf("\n====fila de prioridade de reserva do livro====\n");
    while(aux!=lst)
    {
        printf("%s\n",aux->cpf);
        aux = aux->prox;
    }
    printf("%s",lst->cpf);
}