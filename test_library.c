#include <stdio.h>
#include "library.h"
#include <assert.h>
#include <string.h>

void assertStrEqual(char *expected, char *actual) {
    assert(strcmp(expected, actual) == 0);
}

void test_adicionar_livro() {
    Acervo *acervo = criarAcervo();
    Livro livro1 = {"Linguagem C", "Luís Damas", "literatura técnica"};

    adicionarLivro(acervo, livro1);

    assert(acervo->quantidade == 1);
    assertStrEqual(acervo->livros[0].titulo, "Linguagem C");
    assertStrEqual(acervo->livros[0].autor, "Luís Damas");
    assertStrEqual(acervo->livros[0].genero, "literatura técnica");

    printf("Teste adicionarLivro: OK\n");
}

void test_atualizar_livro() {
    Acervo *acervo = criarAcervo();
    Livro livro1 = {"Linguagem C", "Luís Damas", "literatura técnica"};
    adicionarLivro(acervo, livro1);
    Livro livroSubstituto = {"Java Beginner's Guide", "Herbert Schildt", "literatura técnica"};

    atualizarLivro(acervo, 0, livroSubstituto);

    assert(acervo->quantidade == 1);
    assertStrEqual(acervo->livros[0].titulo, "Java Beginner's Guide");
    assertStrEqual(acervo->livros[0].autor, "Herbert Schildt");
    assertStrEqual(acervo->livros[0].genero, "literatura técnica");

    printf("Teste atualizarLivro: OK\n");
}

void test_remover_livro() {
    Acervo *acervo = criarAcervo();
    Livro livro1 = {"jQuery", "Luís Soares", "literatura técnica"};
    adicionarLivro(acervo, livro1);

    removerLivro(acervo, 0);

    assert(acervo->quantidade == 0);

    printf("Teste removerLivro: OK\n");
}

void test_pesquisar_livro() {


    printf("Teste pesquisar_livro: OK\n");
}

int main() {
    test_adicionar_livro();
    test_atualizar_livro();
    test_remover_livro();

    printf("Todos os testes passaram com sucesso!\n");
}
