#include "listaDupla.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
hist* criar_historico()
{
    return NULL;
}

int historico_vazio(hist* hst)
{
    if(hst==NULL)
        return 1;
    return 0;
}

int usuario_pegou(user** usuario,Livro* livro)
{   
    if(livro->quantidade<=0)
    {
        int opcao;
        do
        {
            printf("\nTodos as unidades desse livro nao estao disponiveis\n");
            printf("Deseja entrar na fila de espera?\n1.sim\n2.nao\n");
            scanf("%d",&opcao); 
            switch(opcao)
            {
                case 1:
                    inserir_pessoa_prio(&livro->prio,(*usuario)->cpf);
                    break;
                case 2:
                    break;
                default:
                    printf("Opcao invalida!");
                    break;
            }
        }while(opcao!=2 && opcao!=1);
        return 0;
    }
    if(livro->prio !=NULL)
    {
        if(strcmp((*usuario)->cpf,livro->prio->prox->cpf) !=0)
        {
            printf("O usuario nao eh o primeiro da fila de prioridade para pegar o livro!");
            return 0;
        }
    }
    hist* lst_hist = (*usuario)->emprestimos;
    hist* novo = (hist*) malloc(sizeof(hist));
    strcpy(novo->cpf,(*usuario)->cpf);
    novo->devolucao = 0;
    strcpy(novo->isbn,livro->isbn);
    strcpy(novo->titulo,livro->titulo);
    strcpy(novo->nome,(*usuario)->nome);
    if(livro->prio != NULL)
        andar_prio(&livro->prio);
    livro->quantidade--;
    if(historico_vazio(lst_hist))
    {
        (*usuario)->emprestimos = novo;
        novo->ant = NULL;
        novo->prox = NULL;
        return 1;
    }
    hist* aux= lst_hist;
    while(aux->prox!=NULL)
        aux = aux->prox;
    aux->prox = novo;
    novo->prox = NULL;
    novo->ant = aux;
    return 1;
}

int usuario_devolveu(user* usuario,Livro* livro)
{
    hist* aux = usuario->emprestimos;
    while(aux!= NULL && strcmp(aux->isbn,livro->isbn)!=0)
        aux = aux->prox;
    if(aux==NULL)
    {
        printf("\nLivro nao encontrado no historico de emprestimo do usuario\n");
        return 0;
    }
    livro->quantidade++;
    aux->devolucao = 1;
    return 1;
}
void imprimir_historico(user* usuario)
{
    hist* aux = usuario->emprestimos;
    printf("\nHistorico de emprestimos do usuario:\n");
    while(aux!=NULL)
    {
        printf("\n CPF do usuario: %s | Nome do usuario: %s | Titulo do livro: %s | Devolucao: %d",aux->cpf,aux->nome,aux->titulo,aux->devolucao);
        printf("\n");
        aux = aux->prox;
    }
}
