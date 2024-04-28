#ifndef LIBRARY_H
#define LIBRARY_H

// Definição da estrutura para representar um livro
typedef struct
{
    char titulo[50];
    char autor[100];
    char genero[20];
    int id;
} Livro;

// Definição da estrutura para representar o acervo
typedef struct
{
    Livro livros[100];
    int quantidade;
} Acervo;

void adicionarLivro(Acervo *acervo, Livro livroNovo);

void removerLivro(Acervo *acervo, int indice);

void atualizarLivro(Acervo *acervo, int indice, Livro livro);

Acervo pesquisarLivros(Acervo *acervo, char *pesquisa);

#endif // LIBRARY_H
