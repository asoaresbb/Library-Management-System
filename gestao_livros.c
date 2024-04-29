#include <string.h>
#include <stdlib.h>
#include "gestao_livros.h"
#include <ctype.h>

void adicionarLivro(Acervo *acervo, char *titulo, char *autor, char *genero)
{
    Livro *novoLivro = &acervo->livros[acervo->quantidade];
    novoLivro->id = acervo->quantidade;
    strcpy(novoLivro->titulo, titulo);
    strcpy(novoLivro->autor, autor);
    strcpy(novoLivro->genero, genero);
    acervo->quantidade++; // Incrementar o número de livros no Acervo
}

void removerLivro(Acervo *acervo, int indiceLivroARemover)
{
    acervo->livros[indiceLivroARemover] = acervo->livros[acervo->quantidade - 1];
    acervo->quantidade--; // Atualizar o número de livros no Acervo
}

void atualizarLivro(Acervo *acervo, int indice, char *titulo, char *autor, char *genero)
{
    Livro *livroAEditar = &acervo->livros[indice];
    strcpy(livroAEditar->titulo, titulo);
    strcpy(livroAEditar->autor, autor);
    strcpy(livroAEditar->genero, genero);
}

char *toLowerCase(const char *str)
{
    int length = strlen(str);
    char *lowercaseStr = (char *)malloc(length + 1);
    for (int i = 0; i < length; i++)
    {
        lowercaseStr[i] = tolower(str[i]);
    }
    lowercaseStr[length] = '\0';
    return lowercaseStr;
}

Acervo pesquisarLivros(Acervo *acervo, char *pesquisa)
{
    Acervo resultados = {};
    char *pesquisaMinuscula = toLowerCase(pesquisa);
    for (int i = 0; i < acervo->quantidade; i++)
    {
        Livro livro = acervo->livros[i];
        if (strstr(toLowerCase(livro.titulo), pesquisaMinuscula) != NULL ||
            strstr(toLowerCase(livro.autor), pesquisaMinuscula) != NULL ||
            strstr(toLowerCase(livro.genero), pesquisaMinuscula) != NULL)
        {
            adicionarLivro(&resultados, livro.titulo, livro.autor, livro.genero);
        }
    }
    return resultados;
}