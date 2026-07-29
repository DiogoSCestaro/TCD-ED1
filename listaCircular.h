#ifndef LISTA_CIRCULAR_H
#define LISTA_CIRCULAR_H
typedef struct prioridade{
    char cpf[12];
    struct prioridade* prox;
}prioridade;

prioridade* criar_prio();

int prio_vazia(prioridade* lst);

int inserir_pessoa_prio(prioridade** lst, char cpf[]);

int andar_prio(prioridade** lst);

void print_prio(prioridade* lst);

#endif