#ifndef GESTAO_LIVROS_H
#define GESTAO_LIVROS_H

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

// o adicionar retorna o id gerado
int adicionarLivro(Acervo *acervo, char *titulo, char *autor, char *genero);

void removerLivro(Acervo *acervo, int id);

void atualizarLivro(Acervo *acervo, int id, char *titulo, char *autor, char *genero);
Acervo pesquisarLivros(Acervo *acervo, char *pesquisa);

#endif // GESTAO_LIVROS_H