#include <string.h>
#include <stdlib.h>
#include "gestao_livros.h"
#include <ctype.h>

Livro *obterLivro(Acervo *acervo, int id) {
    // retorna o livro a partir do ID
    for (int i = 0; i < acervo->quantidade; ++i) {
        if (acervo->livros[i].id == id) {
            return &acervo->livros[i];
        }
    }
    return NULL;
}

int adicionarLivro(Acervo *acervo, char *titulo, char *autor, char *genero)
{
    // Procurar maior id
    int maiorId = 0;
    for (int i = 0; i < acervo->quantidade; ++i) {
        if (maiorId < acervo->livros[i].id) {
            maiorId = acervo->livros[i].id;
        }
    }

    Livro *ultimoLivro = &acervo->livros[acervo->quantidade];
    ultimoLivro->id = maiorId + 1; // id do próximo livro será maior que o anterior
    strcpy(ultimoLivro->titulo, titulo);
    strcpy(ultimoLivro->autor, autor);
    strcpy(ultimoLivro->genero, genero);
    acervo->quantidade++; // Incrementar o número de livros no Acervo

    return ultimoLivro->id;
}

void removerLivro(Acervo *acervo, int id)
{
    // Procura pelo livro com o ID desejado e remove
    for (int i = 0; i < acervo->quantidade; ++i) {
        if (acervo->livros[i].id == id) {
            acervo->livros[i] = acervo->livros[acervo->quantidade - 1];
            acervo->quantidade--; // Atualiza o número de livros no Acervo
            return;
        }
    }
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