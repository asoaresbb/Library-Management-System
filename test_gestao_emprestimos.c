#include <stdio.h>
#include "gestao_emprestimos.h"
#include <assert.h>
#include <string.h>
#include <unistd.h>

#define QUINZE_DIAS_EM_SEGUNDOS (15 * 24 * 60 * 60) // criada novamente para reduzir acoplamento entre testes e implementação
#define CINCO_DIAS_EM_SEGUNDOS (5 * 24 * 60 * 60)

void test_emprestar() {
    Emprestimos emprestimos = {};

    emprestarLivro(&emprestimos, 123, 987);

    assert(1 == emprestimos.quantidade);
    assert(123 == emprestimos.lista[0].idLivro);
    assert(987 == emprestimos.lista[0].idUtilizador);
    assert(emprestimos.lista[0].data > 0);
    assert(0 == emprestimos.lista[0].dataDevolucao);
    assert(emprestimos.lista[0].dataEsperada == emprestimos.lista[0].data + QUINZE_DIAS_EM_SEGUNDOS);
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
    Emprestimos emprestimos = {};
    emprestarLivro(&emprestimos, 123, 987);
    assert(emprestimos.lista[0].dataEsperada == emprestimos.lista[0].data + QUINZE_DIAS_EM_SEGUNDOS);

    renovarEmprestimo(&emprestimos, 123, 987);

    assert(emprestimos.lista[0].dataEsperada ==
           emprestimos.lista[0].data + QUINZE_DIAS_EM_SEGUNDOS + CINCO_DIAS_EM_SEGUNDOS);
}

int main() {
    test_emprestar();
    test_devolver();
    test_renovar();

    printf("✅ Testes unitários da emprestimos_livros.c passaram com sucesso!\n");
}
