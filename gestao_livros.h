#ifndef GESTAO_LIVROS_H
#define GESTAO_LIVROS_H

// Definição da estrutura para representar um livro
typedef struct {
    char titulo[50];
    char autor[100];
    char genero[20];
    int id;
} Livro;

// Definição da estrutura para representar o acervo
typedef struct {
    Livro *livros;
    int quantidade;
} Acervo;

int lerLivrosDoCSV(const char *nomeArquivo, Acervo *acervo);

Livro *obterLivro(Acervo *acervo, int id);

int adicionarLivro(Acervo *acervo, char *titulo, char *autor, char *genero); // o adicionar retorna o id gerado
void removerLivro(Acervo *acervo, int id);

Acervo pesquisarLivros(Acervo *acervo, char *pesquisa);

void libertarMemoriaAcervo(Acervo *acervo);

#endif // GESTAO_LIVROS_H