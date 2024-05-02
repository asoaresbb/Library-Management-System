#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include "gestao_livros.h"

void criarLivro(Acervo *acervo, Livro livro)
{
    acervo->livros = realloc(acervo->livros, (acervo->quantidade + 1) * sizeof(Livro));
    acervo->livros[acervo->quantidade] = livro;
    acervo->quantidade++; // Incrementar o número de livros no Acervo
}

// Ler os livros do ficheiro CSV e preencher um acervo
int lerLivrosDoCSV(const char *nomeFicheiro, Acervo *acervo) {
    FILE *ficheiro = fopen(nomeFicheiro, "r");
    if (ficheiro == NULL) return 1; // Erro ao abrir o ficheiro
    char linha[256]; // Buffer para armazenar a linha lida do ficheiro
    while (fgets(linha, sizeof(linha), ficheiro)) {
        linha[strcspn(linha, "\n")] = '\0';
        Livro tempLivro = {0};
        tempLivro.id = atoi(strtok(linha, ","));
        strcpy(tempLivro.titulo, strtok(NULL, ","));
        strcpy(tempLivro.autor, strtok(NULL, ","));
        strcpy(tempLivro.genero, strtok(NULL, ","));
        criarLivro(acervo, tempLivro);
    }
    assert(!fclose(ficheiro));
    return 0; // Sucesso
}

Livro *obterLivro(Acervo *acervo, int id) {
    // retorna o livro a partir do ID
    for (int i = 0; i < acervo->quantidade; ++i) {
        if (acervo->livros[i].id == id) {
            return &acervo->livros[i];
        }
    }
    return NULL;
}


int adicionarLivro(Acervo *acervo, char *titulo, char *autor, char *genero) {
    Livro novoLivro = {};
    // Procurar maior id
    int maiorId = 0;
    for (int i = 0; i < acervo->quantidade; ++i) {
        if (maiorId < acervo->livros[i].id) {
            maiorId = acervo->livros[i].id;
        }
    }
    novoLivro.id = maiorId + 1;
    strcpy(novoLivro.titulo, titulo);
    strcpy(novoLivro.autor, autor);
    strcpy(novoLivro.genero, genero);
    criarLivro(acervo, novoLivro);

    return novoLivro.id;
}

void removerLivro(Acervo *acervo, int id) {
    // Procura pelo livro com o ID desejado e remove
    for (int i = 0; i < acervo->quantidade; ++i) {
        if (acervo->livros[i].id == id) {
            acervo->livros[i] = acervo->livros[acervo->quantidade - 1];
            acervo->quantidade--; // Atualiza o número de livros no Acervo
            acervo->livros = realloc(acervo->livros, (acervo->quantidade) * sizeof(Livro));
            return;
        }
    }
}

char *toLowerCase(const char *str) {
    int length = strlen(str);
    char *lowercaseStr = (char *) malloc(length + 1);
    for (int i = 0; i < length; i++) {
        lowercaseStr[i] = tolower(str[i]);
    }
    lowercaseStr[length] = '\0';
    return lowercaseStr;
}

Acervo pesquisarLivros(Acervo *acervo, char *pesquisa) {
    Acervo resultados = {};
    // trata o input do utilizador para minúsculas para evitar diferenças
    char *pesquisaMinuscula = toLowerCase(pesquisa);
    // caso utilizador escreva algo então procura nos 3 campos
    for (int i = 0; i < acervo->quantidade; i++) {
        Livro livro = acervo->livros[i];
        if (strstr(toLowerCase(livro.titulo), pesquisaMinuscula) != NULL ||
            strstr(toLowerCase(livro.autor), pesquisaMinuscula) != NULL ||
            strstr(toLowerCase(livro.genero), pesquisaMinuscula) != NULL) {
            adicionarLivro(&resultados, livro.titulo, livro.autor, livro.genero);
        }
    }
    return resultados;
}

void libertarMemoriaAcervo(Acervo *acervo) {
    free(acervo->livros);
}