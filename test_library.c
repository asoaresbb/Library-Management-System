#include <stdio.h>
#include "library.h"
#include <assert.h>
#include <string.h>

void assertStrEqual(char *expected, char *actual)
{
    assert(strcmp(expected, actual) == 0);
}

void test_adicionar_livro()
{
    Acervo acervo = {};
    Livro livro1 = {"Linguagem C", "Luís Damas", "literatura técnica"};

    adicionarLivro(&acervo, livro1);

    assert(acervo.quantidade == 1);
    assertStrEqual("Linguagem C", acervo.livros[0].titulo);
    assertStrEqual("Luís Damas", acervo.livros[0].autor);
    assertStrEqual("Luís Damas", acervo.livros[0].genero);
}

void test_atualizar_livro()
{
    Acervo acervo = {};
    Livro livro1 = {"Linguagem C", "Luís Damas", "literatura técnica"};
    adicionarLivro(&acervo, livro1);
    Livro livroSubstituto = {"Java Beginner's Guide", "Herbert Schildt", "literatura técnica"};

    atualizarLivro(&acervo, 0, livroSubstituto);

    assert(1 == acervo.quantidade);
    assertStrEqual("Java Beginner's Guide", acervo.livros[0].titulo);
    assertStrEqual("Herbert Schildt", acervo.livros[0].autor);
    assertStrEqual("literatura técnica", acervo.livros[0].genero);
}

void test_remover_livro()
{
    Acervo acervo = {};
    Livro livro1 = {"jQuery", "Luís Soares", "literatura técnica"};
    adicionarLivro(&acervo, livro1);

    removerLivro(&acervo, 0);

    assert(acervo.quantidade == 0);
}

void test_pesquisar_livros()
{
    Acervo acervo = {};
    Livro livro1 = {"Linguagem C", "Luís Damas", "literatura técnica"};
    adicionarLivro(&acervo, livro1);
    // Livro livro2 = {"teste 123", "abc", "bla"};
    // adicionarLivro(&acervo, livro2);
    // Livro livro3 = {"foobar LING", "autor 123", "literatura técnica"};
    // adicionarLivro(&acervo, livro3);

    Acervo resultado = pesquisarLivros(&acervo, "Linguagem C");

    assert(resultado.quantidade == 1);
    assertStrEqual("Linguagem C", resultado.livros[0].titulo);
}

int main()
{
    test_adicionar_livro();
    printf("Teste adicionar livro: OK\n");
    test_atualizar_livro();
    printf("Teste atualizar livro: OK\n");
    test_remover_livro();
    printf("Teste remover livro: OK\n");
    test_pesquisar_livros();
    printf("Teste pesquisar livros: OK\n");

    printf("Todos os testes passaram com sucesso! ✅\n");
}
