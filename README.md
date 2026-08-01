# TCD-ED1
Sistema de biblioteca utilizando algumas das principais estruturas de dados

# Systeca

Sistema de terminal em C para gerenciar acervo, empréstimos, reservas e cadastro
priorizado de livros, integrando lista simples, lista dupla, lista circular, pilha
e fila para controlar todo o ciclo de vida de um exemplar.

Trabalho Final de Estrutura de Dados I.


## Estruturas de dados implementadas

| Estrutura | Onde está | Funcionalidade |
|---|---|---|
| Lista simplesmente encadeada | `listaSimples.c` / `listaSimples.h` | Catálogo de livros do acervo (`Livro`) — inserção, busca e remoção por ISBN |
| Lista duplamente encadeada | `listaDupla.c` / `listaDupla.h` | Histórico de empréstimos de cada usuário (`hist`) — navegação em `ant`/`prox` |
| Lista circular | `listaCircular.c` / `listaCircular.h` | Fila de reserva de um livro específico (`prioridade`) quando todos os exemplares estão emprestados |
| Pilha (dinâmica) | `pilha.c` / `pilha.h` | Desfazer a última ação — cadastro, remoção, empréstimo ou devolução (`acao`) |
| Fila (dinâmica) | `fila.c` / `fila.h` | Três filas de prioridade (máxima, média, mínima) que controlam a ordem de cadastro de novos livros |


## Estrutura de arquivos

```
.
├── main.c              # menu, login e orquestração geral
├── listaSimples.c/.h    # struct Livro — acervo (lista simplesmente encadeada)
├── listaDupla.c/.h       # struct hist / user — histórico de empréstimos (lista dupla)
├── listaCircular.c/.h    # struct prioridade — fila de reserva por livro (lista circular)
├── pilha.c/.h            # struct acao — desfazer a última ação (pilha dinâmica)
├── fila.c/.h             # struct fila / no_fila — filas de prioridade de cadastro (fila dinâmica)
└── README.md
```

## Como compilar

Pré-requisito: `gcc` instalado.

Não há Makefile nesta etapa — a compilação é feita manualmente, compilando todos os
`.c` juntos:

```bash
gcc -Wall -o biblioteca main.c fila.c listaCircular.c listaDupla.c listaSimples.c pilha.c
```

Isso gera o executável `biblioteca` na pasta atual.

## Como executar

```bash
./biblioteca
```

O programa pede primeiro o **CPF** e o **nome** do usuário (login simples, sem
senha) e depois abre o menu principal, repetido a cada operação.

## Como usar — menu principal

```
1. Ver livros
2. Cadastrar livro
3. Remover livro por isbn
4. Realizar emprestimo
5. Devolver livro
6. Ver historico de emprestimo do usuario
7. Fila de prioridade de um livro
8. Desfazer a ultima acao
9. Consultar filas de prioridade de livros
10. Inserir livro em uma fila de prioridade
0. Sair
```

Observações de uso:

- **Opção 2 (Cadastrar livro):** se alguma das três filas de prioridade (máxima,
  média ou mínima) tiver livros pendentes, o ISBN digitado precisa ser igual ao
  ISBN que está no **fim** da fila de maior prioridade não vazia — senão o
  cadastro é recusado e o sistema informa qual ISBN é esperado. Se as três filas
  estiverem vazias, qualquer livro pode ser cadastrado livremente.
- **Opção 4 (Realizar empréstimo):** se o livro não tiver unidades disponíveis, o
  usuário pode optar por entrar na fila de reserva daquele título (lista
  circular). Se o livro tiver fila de reserva, só o primeiro da fila pode
  pegá-lo emprestado.
- **Opção 8 (Desfazer a última ação):** desfaz cadastro, remoção, empréstimo ou
  devolução mais recentes, na ordem inversa (pilha — LIFO). Um cadastro
  desfeito que veio de uma fila de prioridade devolve o ISBN para a fila
  correta.
- **Opções 9 e 10:** consultam e alimentam as três filas de prioridade de
  cadastro (máxima, média, mínima), usadas pela opção 2.
- **ISBN:** sempre até 10 caracteres.

## Roteiro de teste sugerido

1. Faça login com um CPF e nome quaisquer.
2. Escolha **1** para ver os 5 livros pré-cadastrados no sistema.
3. Escolha **10**, informe um ISBN novo (ex.: `1112223334`) e escolha a fila
   **1 (Máxima)**.
4. Escolha **9** para conferir que o ISBN aparece na fila máxima.
5. Escolha **2** e tente cadastrar um livro com um ISBN diferente do que está
   na fila — o sistema deve recusar e informar o ISBN esperado.
6. Escolha **2** de novo, agora com o ISBN correto (`1112223334`), preencha
   título/autor/quantidade — o cadastro deve ser aceito e a fila máxima deve
   esvaziar (confira com a opção **9** novamente).
7. Escolha **4** e empreste um dos livros pré-cadastrados (ex.: `8535928359`).
8. Escolha **6** para ver o histórico de empréstimos do usuário.
9. Escolha **8** para desfazer o empréstimo — o histórico deve voltar ao
   estado anterior.
10. Escolha **8** de novo para desfazer o cadastro do passo 6 — o livro deve
    sumir da lista (confira com **1**) e o ISBN deve voltar para a fila
    máxima (confira com **9**).
11. Escolha **0** para sair.

## Dados de exemplo

O acervo já é iniciado com 5 livros pré-cadastrados diretamente em `main.c`,
não sendo necessário nenhum arquivo externo para rodar o programa:

| ISBN | Título | Autor | Quantidade |
|---|---|---|---|
| 8535928359 | Jantar secreto | Raphael Montes | 1 |
| 8535929444 | Suicidas | Raphael Montes | 1 |
| 6555658789 | Filho perfeito | Freida McFadden | 1 |
| 8580417236 | A grande ilusão | Harlan Coben | 1 |
| 6555662336 | Homem de palha | Pablo Zorzi | 1 |
