#include <stdio.h>
#include "gestao_livros.h"
#include <assert.h>
#include <string.h>

void test_obter_livro_a_partir_de_id() {
    Acervo acervo = {};
    int id = adicionarLivro(&acervo, "Linguagem C", "Luís Damas", "literatura técnica");

    Livro *livro = obterLivro(&acervo, id);

    assert(strcmp("Linguagem C", livro->titulo) == 0);
}

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

void test_atualizar_livro() {
    Acervo acervo = {};
    int idCriado = adicionarLivro(&acervo, "Linguagem C", "Luís Damas", "literatura técnica");
    Livro *livroEditado = obterLivro(&acervo, idCriado);

    strcpy(livroEditado->titulo, "abc");

    assert(1 == acervo.quantidade);
    assert(strcmp("abc", acervo.livros[0].titulo) == 0);
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
    test_obter_livro_a_partir_de_id();
    test_adicionar_livro();
    test_atualizar_livro();
    test_remover_livro();
    test_remover_livro_ids_nao_repetem();
    test_pesquisar_livros();

    printf("✅ Testes unitários da gestao_livros.c passaram com sucesso!\n");
}
