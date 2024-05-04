#include <stdio.h>
#include "gestao_emprestimos.h"
#include <assert.h>
#include <stdbool.h>

#define QUINZE_DIAS_EM_SEGUNDOS (15 * 24 * 60 * 60) // criada novamente para reduzir acoplamento entre testes e implementação
#define CINCO_DIAS_EM_SEGUNDOS (5 * 24 * 60 * 60)

void test_emprestar() {
    Emprestimos emprestimos = {0};

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
    while (time(NULL) == emprestimos.lista[0].data);

    bool devolvido = devolverLivro(&emprestimos, 123, 987);

    assert(devolvido);
    assert(emprestimos.lista[0].dataEsperada == 0);
    assert(emprestimos.lista[0].dataDevolucao > emprestimos.lista[0].data);
    assert(1 == emprestimos.quantidade);
}

void test_devolver_livro_ja_devolvido() {
    Emprestimos emprestimos = {};
    emprestarLivro(&emprestimos, 123, 987);
    bool devolvido = devolverLivro(&emprestimos, 123, 987);
    assert(devolvido);
    time_t dataDevolucao = emprestimos.lista[0].dataDevolucao;

    devolvido = devolverLivro(&emprestimos, 123, 987);

    assert(!devolvido);
    assert(dataDevolucao == emprestimos.lista[0].dataDevolucao); // como falhou, data deve permanecer a mesma
}

void test_devolver_livro_por_outro_utilizador() {
    Emprestimos emprestimos = {};
    emprestarLivro(&emprestimos, 123, 987);

    bool devolvido = devolverLivro(&emprestimos, 123, 444);

    assert(!devolvido);
}

void test_devolver_livro_nao_emprestado() {
    Emprestimos emprestimos = {};
    emprestarLivro(&emprestimos, 123, 987);

    bool devolvido = devolverLivro(&emprestimos, 111, 987);

    assert(!devolvido);
}

void test_devolver_mesmo_livro_2vezes() {
    Emprestimos emprestimos = {};
    emprestarLivro(&emprestimos, 123, 987);
    devolverLivro(&emprestimos, 123, 987);
    emprestarLivro(&emprestimos, 123, 987);

    devolverLivro(&emprestimos, 123, 987);

    assert(2 == emprestimos.quantidade);
    assert(emprestimos.lista[0].dataDevolucao > 0);
    assert(emprestimos.lista[1].dataDevolucao > 0);
}

void test_renovar() {
    Emprestimos emprestimos = {};
    emprestarLivro(&emprestimos, 123, 987);
    assert(emprestimos.lista[0].dataEsperada == emprestimos.lista[0].data + QUINZE_DIAS_EM_SEGUNDOS);

    bool renovado = renovarEmprestimo(&emprestimos, 123, 987);

    assert(renovado);
    assert(emprestimos.lista[0].dataDevolucao == 0);
    assert(emprestimos.lista[0].dataEsperada ==
           emprestimos.lista[0].data + QUINZE_DIAS_EM_SEGUNDOS + CINCO_DIAS_EM_SEGUNDOS);
}

void test_renovar_ja_devolvido() {
    Emprestimos emprestimos = {};
    emprestarLivro(&emprestimos, 123, 987);
    devolverLivro(&emprestimos, 123, 987);
    time_t dataEsperada = emprestimos.lista[0].dataEsperada;

    bool renovado = renovarEmprestimo(&emprestimos, 123, 987);

    assert(!renovado);
    assert(dataEsperada == emprestimos.lista[0].dataEsperada); // como falhou, data deve permanecer a mesma
}

int main() {
    test_emprestar();
    test_devolver();
    test_devolver_livro_ja_devolvido();
    test_devolver_livro_por_outro_utilizador();
    test_devolver_livro_nao_emprestado();
    test_devolver_mesmo_livro_2vezes();
    test_renovar();
    test_renovar_ja_devolvido();

    printf("✅  Testes unitários da emprestimos_livros.c passaram com sucesso!\n");
}
