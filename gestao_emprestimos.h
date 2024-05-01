#ifndef GESTAO_EMPRESTIMOS_H
#define GESTAO_EMPRESTIMOS_H

#include <time.h>
#include <stdbool.h>

// Definição da estrutura para representar um emprestimo
typedef struct {
    int idLivro;
    int idUtilizador;
    time_t data;
    time_t dataDevolucao;
    time_t dataEsperada;
} Emprestimo;

// Definição da estrutura para representar os livros emprestados
typedef struct {
    Emprestimo lista[100];
    int quantidade;
} Emprestimos;

void emprestarLivro(Emprestimos *emprestimos, int idLivro, int idUtilizador);

bool devolverLivro(Emprestimos *emprestimos, int idLivro, int idUtilizador);

bool renovarEmprestimo(Emprestimos *emprestimos, int idLivro, int idUtilizador);

#endif // GESTAO_EMPRESTIMOS_H