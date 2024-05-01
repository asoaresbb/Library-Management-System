#include <stdio.h>
#include "gestao_emprestimos.h"
#include <assert.h>
#include <string.h>
#include <unistd.h>

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
    sleep(1);

    devolverLivro(&emprestimos, 123, 987);

    assert(emprestimos.lista[0].dataDevolucao > emprestimos.lista[0].data);
    assert(1 == emprestimos.quantidade);
}

void test_renovar() {
    //TODO caso se renove aumenta 15 dias na data esperada. Criar teste
}

int main() {
    test_emprestar();
    test_devolver();
    test_renovar();

    printf("✅ Testes unitários da emprestimos_livros.c passaram com sucesso!\n");
}
