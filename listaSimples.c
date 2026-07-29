#include "listaSimples.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Livro* criar_lista()
{
    return NULL;
}

void inserir_na_lista(Livro** lst, Livro* livro)
{
    livro->prox = *lst;
    (*lst) = livro;
}
int remover_ISBN(Livro** lst,char isbn[] )
{
    if((*lst) == NULL)
    {
        printf("Livro nao encontrado na lista!");
        return 0;
    }
    Livro* aux = *lst;
    if(strcmp(isbn,(*lst)->isbn)==0)
    {
        *lst = (*lst)->prox;
        free(aux);
        printf("livro removido com sucesso!");
        return 1;
    }
    while(aux->prox != NULL && strcmp(isbn,aux->prox->isbn)!=0)
        aux = aux->prox;
    if(aux->prox == NULL)
    {
        printf("Livro nao encontrado na lista!");
        return 0;
    }
    Livro* aux2 = aux->prox;
    aux->prox = aux2->prox;
    free(aux2);
    printf("Livro removido com sucesso!");
    return 1;

}
void imprimir_lista(Livro* l)
{
    Livro* aux = l;
    while(aux!=NULL)
    {
        printf("ISBN: %s | Titulo: %s | Autor: %s  | Quantidade: %d\n",aux->isbn,aux->titulo,aux->autor,aux->quantidade );
        aux = aux->prox;
    }
}
Livro* criar_livro(char isbn[],char titulo[],char autor[],int quantidade)
{
    Livro* livro = (Livro*) malloc(sizeof(Livro));
    strcpy(livro->isbn,isbn);
    strcpy(livro->titulo,titulo);
    strcpy(livro->autor,autor);
    livro->quantidade = quantidade;
    livro->prio = NULL;
    return livro;
}

Livro* buscar_livro(Livro* lista,char isbn[])
{
    Livro* aux = lista;
    while(aux != NULL && strcmp(aux->isbn,isbn)!=0)
        aux = aux->prox;
    return aux;
}
