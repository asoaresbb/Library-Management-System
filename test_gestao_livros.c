#include <stdio.h>
#include "gestao_livros.h"
#include <assert.h>
#include <string.h>

void test_adicionar_livro()
{
    Acervo acervo = {};

    int id = adicionarLivro(&acervo, "Linguagem C", "Luís Damas", "literatura técnica");

    assert(1 == acervo.quantidade);
    assert(id == acervo.livros[0].id);
    assert(strcmp("Linguagem C", acervo.livros[0].titulo) == 0);
    assert(strcmp("Luís Damas", acervo.livros[0].autor) == 0);
    assert(strcmp("literatura técnica", acervo.livros[0].genero) == 0);
}

void test_atualizar_livro()
{
    Acervo acervo = {};
    adicionarLivro(&acervo, "Linguagem C", "Luís Damas", "literatura técnica");

    atualizarLivro(&acervo, 0, "Java Beginner's Guide", "Herbert Schildt", "literatura técnica");

    assert(1 == acervo.quantidade);
    assert(strcmp("Java Beginner's Guide", acervo.livros[0].titulo) == 0);
    assert(strcmp("Herbert Schildt", acervo.livros[0].autor) == 0);
    assert(strcmp("literatura técnica", acervo.livros[0].genero) == 0);
}

void test_remover_livro()
{
    Acervo acervo = {};
    int idAdicionado = adicionarLivro(&acervo, "jQuery", "Luís Soares", "literatura técnica");

    removerLivro(&acervo, idAdicionado);

    assert(0 == acervo.quantidade);
}

void test_remover_livro_ids_nao_repetem() {
    Acervo acervo = {};
    int idAdicionado = adicionarLivro(&acervo, "jQuery", "Luís Soares", "literatura técnica");
    adicionarLivro(&acervo, "JS", "Luís", "literatura");
    removerLivro(&acervo, idAdicionado);

    adicionarLivro(&acervo, "JS", "Luís", "literatura");

    assert(acervo.livros[0].id != acervo.livros[1].id);
}

void test_pesquisar_livros()
{
    Acervo acervo = {};
    adicionarLivro(&acervo, "Linguagem C", "Luís Damas", "literatura técnica");
    adicionarLivro(&acervo, "teste 123", "abc", "bla");
    adicionarLivro(&acervo, "foobar LING", "autor 123", "literatura scifi");
    adicionarLivro(&acervo, "foo bar fooo bar", "lingling", "literatura técnica");
    adicionarLivro(&acervo, "biblioteca JS", "Andre", "linguistico");

    Acervo resultado = pesquisarLivros(&acervo, "LING");

    assert(4 == resultado.quantidade);
    assert(strcmp("Linguagem C", resultado.livros[0].titulo) == 0);
    assert(strcmp("foobar LING", resultado.livros[1].titulo) == 0);
    assert(strcmp("foo bar fooo bar", resultado.livros[2].titulo) == 0);
    assert(strcmp("biblioteca JS", resultado.livros[3].titulo) == 0);
}

int main()
{
    test_adicionar_livro();
    printf("Teste adicionar livro: OK\n");
    test_atualizar_livro();
    printf("Teste atualizar livro: OK\n");
    test_remover_livro();
    test_remover_livro_ids_nao_repetem();
    printf("Teste remover livro: OK\n");
    test_pesquisar_livros();
    printf("Teste pesquisar livros: OK\n");

    printf("✅ Testes unitários da gestao_livros.c passaram com sucesso!\n");
}
