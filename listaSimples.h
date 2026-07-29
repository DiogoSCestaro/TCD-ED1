// Livros
#ifndef LISTA_SIMPLES_H
#define LISTA_SIMPLES_H
typedef struct Livro{
    char isbn[11];
    char titulo[100];
    char autor[100];
    int quantidade;
    struct prioridade* prio;
    struct Livro* prox;
} Livro;

Livro* criar_lista();
void inserir_na_lista(Livro** lst, Livro* livro);
int remover_ISBN(Livro** lst,char isbn[] );
void imprimir_lista(Livro* l);
Livro* criar_livro(char isbn[],char titulo[],char autor[],int quantidade);
Livro* buscar_livro(Livro* livro,char isbn[]);
#endif