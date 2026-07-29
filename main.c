#include <stdio.h>
#include "listaSimples.h"
#include "listaDupla.h"
#include "pilha.h"
#include "listaCircular.h"
#include "fila.h"
#include <string.h>
#include <stdlib.h>
int main()
{   
    int opcao;
    Livro* lista = criar_lista();
    user* usuario = (user*) malloc(sizeof(user));
    usuario->emprestimos = criar_historico();
    int id_historico = 0;
    acao* pilha = criar_pilha();
    fila* prioridade_maxima = criar_fila();
    fila* prioridade_media = criar_fila();
    fila* prioridade_minima = criar_fila();
    char nome_usuario[25];
    char isbn[11];
    char nome_do_livro[100];
    char nome_do_autor[100];
    int quantidade_do_livro;
    inserir_na_lista(&lista,criar_livro("8535928359", "Jantar secreto", "Raphael Montes", 1));
    inserir_na_lista(&lista,criar_livro("8535929444", "Suicidas","Raphael Montes", 1));
    inserir_na_lista(&lista,criar_livro("6555658789", "Filho perfeito","Freida McFadden", 1));
    inserir_na_lista(&lista,criar_livro("8580417236", "A grande ilusao","Harlan Coben", 1));
    inserir_na_lista(&lista,criar_livro("6555662336", "Homem de palha","Pablo Zorzi", 1));
    printf("\n ====== Menu de Login ======\n");
    printf("Insira o cpf do usuario: \n");
    scanf("%11s",&usuario->cpf);
    while ((getchar()) != '\n');
    printf("\nInsira o nome do usuario: \n");
    scanf("%24s",&usuario->nome);
    while ((getchar()) != '\n');
     do
    {
        printf("\n=== BIBLIOTECA ===\n");
        printf("1. Ver livros\n");
        printf("2. Cadastrar livro\n");
        printf("3. Remover livro por isbn\n");
        printf("4. Realizar emprestimo\n");
        printf("5. Devolver livro\n");
        printf("6. Ver historico de emprestimo do usuario\n");
        printf("7. Fila de prioridade de um livro\n");
        printf("8. Desfazer a ultima acao\n");
        printf("9. Consultar filas de prioridade de livros\n");
        printf("10. Inserir livro em uma fila de prioridade\n");
        printf("0. Sair\n");
        scanf("%d", &opcao);
        while ((getchar()) != '\n');
        switch(opcao)
        {
            case 1: 
                imprimir_lista(lista);
                break;
            case 2: 
            {
                int prioridade = -1;

                printf("\nInsira o isbn 10 do livro:");
                scanf("%10s",&isbn);
                while ((getchar()) != '\n');
                fila* fila_alvo = NULL;
                if(!fila_vazia(prioridade_maxima)){
                    fila_alvo = prioridade_maxima;
                    prioridade = 2;
                }
                else if(!fila_vazia(prioridade_media)){
                    fila_alvo = prioridade_media;
                    prioridade = 1;
                }
                else if(!fila_vazia(prioridade_minima)){
                    fila_alvo = prioridade_minima;
                    prioridade = 0;
                }
                if(fila_alvo != NULL && strcmp(isbn, fila_alvo->fim->isbn) != 0)
                {
                    printf("\nEsse livro nao pode ser cadastrado agora! Existem filas de prioridade pendentes e o isbn deve ser %s\n", fila_alvo->fim->isbn);
                    break;
                }
                printf("\nInsira o nome do livro:");
                scanf("%99s",&nome_do_livro);
                while ((getchar()) != '\n');
                printf("\nInsira o nome do autor:");
                scanf("%99s",&nome_do_autor);
                while ((getchar()) != '\n');
                printf("\nInsira a quantidade desse livro a ser adicionado:");
                scanf("%d",&quantidade_do_livro); 
                inserir_na_lista(&lista,criar_livro(isbn,nome_do_livro,nome_do_autor,quantidade_do_livro));
                empilhar(&pilha,criar_acao(cadastrar,isbn,nome_do_livro,nome_do_autor,quantidade_do_livro,"","",prioridade));
                if(fila_alvo != NULL)
                    remover_ultimo_da_fila(fila_alvo);
                break;
            }
            case 3:
                printf("\nInsira o isbn 10 do livro: ");
                char n[12];
                scanf("%10s",&n);
                while ((getchar()) != '\n');
                Livro* alvo = buscar_livro(lista,n);
                if(alvo != NULL)
                {
                    char isbn_bkp[11], titulo_bkp[100], autor_bkp[100];
                    int qtd_bkp = alvo->quantidade;
                    strcpy(isbn_bkp, alvo->isbn);
                    strcpy(titulo_bkp, alvo->titulo);
                    strcpy(autor_bkp, alvo->autor);
                    if(remover_ISBN(&lista,n))
                        empilhar(&pilha, criar_acao(remover, isbn_bkp, titulo_bkp, autor_bkp, qtd_bkp, "", "",-1));
                }
                else
                    printf("Livro nao encontrado na lista!");
                break;
            
                
            case 4:
                printf("\nInsira o isbn do livro:\n");
                scanf("%10s",&isbn);
                while ((getchar()) != '\n');
                Livro* livro0 = buscar_livro(lista,isbn);
                if(livro0 != NULL)
                {
                    char titulo_bkp[100];
                    strcpy(titulo_bkp, livro0->titulo);
                    if(usuario_pegou(&usuario,livro0))
                        empilhar(&pilha, criar_acao(emprestimo, isbn, titulo_bkp, "", 0, usuario->cpf, usuario->nome,-1));
                }
                else
                    printf("\nLivro nao encontrado!\n");
                break;
            case 5:
                printf("\nInsira o isbn do livro:\n");
                scanf("%10s",&isbn);
                while ((getchar()) != '\n');
                Livro* livro = buscar_livro(lista,isbn);
                if(livro != NULL)
                {
                    char titulo_bkp[100];
                    strcpy(titulo_bkp, livro->titulo);
                    if(usuario_devolveu(usuario,livro))
                        empilhar(&pilha, criar_acao(devolucao, isbn, titulo_bkp, "", 0, usuario->cpf, usuario->nome,-1));
                }
                else
                    printf("\nLivro nao encontrado!\n");
                break;
            case 6:
                imprimir_historico(usuario);
                break;
            case 7:
                printf("\nInsira o isbn do livro\n");
                scanf("%10s",&isbn);
                while((getchar())!='\n');
                print_prio((buscar_livro(lista,isbn))->prio);
                break;
            case 8:
                desfazer_acao(&pilha, &lista, usuario, prioridade_maxima, prioridade_media, prioridade_minima);
                break;
            case 9:
                printf("\n=== Fila de prioridade MAXIMA ===\n");
                imprimir_fila(prioridade_maxima);
                printf("\n=== Fila de prioridade MEDIA ===\n");
                imprimir_fila(prioridade_media);
                printf("\n=== Fila de prioridade MINIMA ===\n");
                imprimir_fila(prioridade_minima);
                printf("\n");
                break;
            case 10:
            {
                int nivel;
                printf("\nInsira o isbn do livro a entrar na fila de prioridade:\n");
                scanf("%10s",&isbn);
                while((getchar())!='\n');
                printf("\nEscolha a fila de prioridade:\n1. Maxima\n2. Media\n3. Minima\n");
                scanf("%d",&nivel);
                while((getchar())!='\n');
                switch(nivel)
                {
                    case 1:
                        inserir_na_fila(prioridade_maxima, isbn);
                        printf("\nLivro inserido na fila de prioridade maxima!\n");
                        break;
                    case 2:
                        inserir_na_fila(prioridade_media, isbn);
                        printf("\nLivro inserido na fila de prioridade media!\n");
                        break;
                    case 3:
                        inserir_na_fila(prioridade_minima, isbn);
                        printf("\nLivro inserido na fila de prioridade minima!\n");
                        break;
                    default:
                        printf("\nOpcao invalida!\n");
                        break;
                }
                break;
            }
            case 0:
                break;
            default:
                printf("\nOpcao invalida!\n");
                break;
        }

    }while(opcao!=0);
}