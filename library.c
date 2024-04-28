#include <string.h>
#include <stdlib.h>
#include "library.h"

void adicionarLivro(Acervo *acervo, Livro livroNovo)
{
    strcpy(acervo->livros[acervo->quantidade].titulo, livroNovo.titulo);
    strcpy(acervo->livros[acervo->quantidade].autor, livroNovo.autor);
    strcpy(acervo->livros[acervo->quantidade].genero, livroNovo.genero);
    acervo->quantidade++; // Incrementar o número de livros no Acervo
}

void removerLivro(Acervo *acervo, int indiceLivroARemover)
{
    acervo->livros[indiceLivroARemover] = acervo->livros[acervo->quantidade - 1];
    acervo->quantidade--; // Atualizar o número de livros no Acervo
}

void atualizarLivro(Acervo *acervo, int indice, Livro livro)
{
    Livro *livroAEditar = &acervo->livros[indice];
    strcpy(livroAEditar->titulo, livro.titulo);
    strcpy(livroAEditar->autor, livro.autor);
    strcpy(livroAEditar->genero, livro.genero);
}

Acervo pesquisarLivros(Acervo *acervo, char *pesquisa)
{
}