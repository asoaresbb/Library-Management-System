#include <string.h>
#include <stdlib.h>
#include "library.h"
#include <ctype.h>

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
            adicionarLivro(&resultados, livro);
        }
    }
    return resultados;
}