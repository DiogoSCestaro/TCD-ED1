#include "pilha.h"
#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

acao* criar_pilha()
{
    return NULL;
}

int pilha_vazia(acao* pilha)
{
    if(pilha == NULL)
        return 1;
    return 0;
}

acao* criar_acao(tipoacao tipo,char isbn[],char titulo[],char autor[],int quantidade,char cpf[],char nome[],int prioridade)
{
    acao* nova = (acao*) malloc(sizeof(acao));
    nova->tipo = tipo;
    nova->quantidade = quantidade;
    strcpy(nova->isbn,isbn);
    strcpy(nova->autor,autor);
    strcpy(nova->titulo,titulo);
    strcpy(nova->cpf,cpf);
    strcpy(nova->nome,nome);
    nova->prox = NULL;
    nova->prioridade = prioridade;
    return nova;
}

void empilhar(acao** pilha, acao* nova)
{
    nova->prox = *pilha;
    *pilha = nova;
}

acao* desempilhar(acao** pilha)
{
    if(*pilha==NULL)
        return NULL;
    acao* aux = *pilha;
    *pilha = (*pilha)->prox;
    aux->prox = NULL;
    return aux;
}

int desfazer_acao(acao** pilha, Livro** lista, user* usuario, fila* prioridade_maxima, fila* prioridade_media, fila* prioridade_minima)
{
    if(pilha_vazia(*pilha))
    {
        printf("\n====Nao ha acoes para desfazer!====\n");
        return 0;
    }
    acao* item = desempilhar(pilha);
    switch(item->tipo)
    {
        case cadastrar:
            remover_ISBN(lista,item->isbn);
            if(item->prioridade == 2)
                inserir_na_fila(prioridade_maxima,item->isbn);
            else if(item->prioridade == 1)
                inserir_na_fila(prioridade_media,item->isbn);
            else if(item->prioridade == 0)
                inserir_na_fila(prioridade_minima,item->isbn);
            printf("\nCadastro de livro desfeito!\n");
            break;
        case remover:
        {
            Livro* livro0 = criar_livro(item->isbn , item->titulo , item->autor, item->quantidade);
            inserir_na_lista(lista,livro0);
            printf("\nRemocao do livro foi desfeita!\n");
            break;
        }
        case emprestimo:
        {
            Livro* livro = buscar_livro(*lista,item->isbn);
            if(livro!=NULL)
                livro->quantidade++;
            hist* aux = usuario->emprestimos;
            hist* aux2 = NULL;
            while(aux!=NULL)
            {
                if(strcmp(aux->isbn,item->isbn)==0 && aux->devolucao == 0)
                    aux2 = aux;
                aux = aux->prox;
            }
            if(aux2 != NULL)
            {
                if(aux2->ant != NULL)
                    aux2->ant->prox = aux2->prox;
                else
                    usuario->emprestimos = aux2->prox;
                if(aux2->prox != NULL)
                    aux2->prox->ant = aux2->ant;
                free(aux2);
            }
            printf("\nEmprestimo desfeito!\n");
            break;
        }
        case devolucao:
        {
            Livro* livro2 = buscar_livro(*lista,item->isbn);
            hist* aux = usuario->emprestimos;
            while(aux!=NULL && !(strcmp(aux->isbn,item->isbn)==0 && aux->devolucao==1))
                aux = aux->prox;
            if(aux!=NULL)
                aux->devolucao=0;
            if(livro2 != NULL)
                livro2->quantidade--;
            printf("\nDevolucao do livro desfeita!\n");
            break;   
        } 
    }
    free(item);
    return 1;
}