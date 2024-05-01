#include <stdio.h>
#include "gestao_emprestimos.h"
#include <assert.h>
#include <string.h>

void test_emprestar() {
    Emprestimos emprestimos = {};

    emprestarLivro(&emprestimos, 123, 987);

    assert(1 == emprestimos.quantidade);
    assert(123 == emprestimos.lista[0].idLivro);
    assert(987 == emprestimos.lista[0].idUtilizador);
    assert(emprestimos.lista[0].data > 0);
}

void test_devolver() {
    Emprestimos emprestimos = {};

    emprestarLivro(&emprestimos, 123, 987);
    devolverLivro(&emprestimos, 123, 987);

    assert(0 == emprestimos.quantidade);
    assert(123 == emprestimos.lista[0].idLivro);
    assert(987 == emprestimos.lista[0].idUtilizador);
    assert(emprestimos.lista[0].dataDevolucao > 0);
}

int main() {
    test_emprestar();

    printf("✅ Testes unitários da emprestimos_livros.c passaram com sucesso!\n");
}
