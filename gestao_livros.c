#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gestao_livros.h"
#include <ctype.h>

// Função para ler os livros do arquivo CSV e preencher o acervo
int lerLivrosDoCSV(const char *nomeArquivo, Acervo *acervo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        return 1; // Erro ao abrir o arquivo
    }

    char linha[256]; // Buffer para armazenar a linha lida do arquivo
    char *token;
    const char *delim = ",\"";
    int id = 1; // Identificador inicial para os livros

    // Ler cada linha do arquivo CSV
    while (fgets(linha, sizeof(linha), arquivo)) {
        // Remover o caractere de nova linha (se presente)
        linha[strcspn(linha, "\n")] = '\0';

        // Extrair cada campo da linha
        token = strtok(linha, delim); // Título
        char *titulo = token;

        token = strtok(NULL, delim); // Autor
        char *autor = token;

        token = strtok(NULL, delim); // Gênero
        char *genero = token;

        // Se todos os campos foram lidos corretamente, adicionar o livro ao acervo
        if (titulo && autor && genero) {
            adicionarLivro(acervo, titulo, autor, genero);
            id++; // Incrementar o identificador para o próximo livro
        }
    }

    fclose(arquivo);
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
    // Procurar maior id
    int maiorId = 0;
    for (int i = 0; i < acervo->quantidade; ++i) {
        if (maiorId < acervo->livros[i].id) {
            maiorId = acervo->livros[i].id;
        }
    }

    acervo->livros = realloc(acervo->livros, (acervo->quantidade + 1) * sizeof(Livro));

    Livro *ultimoLivro = &(acervo->livros[acervo->quantidade]);
    ultimoLivro->id = maiorId + 1; // id do próximo livro será maior que o anterior
    strcpy(ultimoLivro->titulo, titulo);
    strcpy(ultimoLivro->autor, autor);
    strcpy(ultimoLivro->genero, genero);
    acervo->quantidade++; // Incrementar o número de livros no Acervo

    return ultimoLivro->id;
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