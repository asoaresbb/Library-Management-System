#ifndef GESTAO_EMPRESTIMOS_H
#define GESTAO_EMPRESTIMOS_H

#include <time.h>

// Definição da estrutura para representar um emprestimo
typedef struct {
    int idLivro;
    int idUtilizador;
    time_t data;
} Emprestimo;

// Definição da estrutura para representar os livros emprestados
typedef struct {
    Emprestimo lista[100];
    int quantidade;
} Emprestimos;

void emprestarLivro(Emprestimos *emprestimos, int idLivro, int idUtilizador);

#endif // GESTAO_EMPRESTIMOS_H