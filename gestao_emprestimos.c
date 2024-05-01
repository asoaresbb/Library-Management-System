#include <time.h>
#include <stdlib.h>
#include "gestao_emprestimos.h"

#define CINCO_DIAS_EM_SEGUNDOS (5 * 24 * 60 * 60)
#define QUINZE_DIAS_EM_SEGUNDOS (15 * 24 * 60 * 60)

void emprestarLivro(Emprestimos *emprestimos, int idLivro, int idUtilizador) {
    // Realocar memoria dinamicamente
    emprestimos->lista = realloc(emprestimos->lista, (emprestimos->quantidade + 1) * sizeof(Emprestimo));
    // Obtém o último empréstimo na lista (o próximo em que será inserido)
    Emprestimo *ultimoEmprestimo = &(emprestimos->lista[emprestimos->quantidade]);
    // Preenche os detalhes do novo empréstimo
    ultimoEmprestimo->idLivro = idLivro;
    ultimoEmprestimo->idUtilizador = idUtilizador;
    ultimoEmprestimo->data = time(NULL); // Obter a data atual como data de empréstimo
    ultimoEmprestimo->dataEsperada = ultimoEmprestimo->data + QUINZE_DIAS_EM_SEGUNDOS;
    ultimoEmprestimo->dataDevolucao = 0;
    emprestimos->quantidade++;
}

bool devolverLivro(Emprestimos *emprestimos, int idLivro, int idUtilizador) {
    // Procura pelo empréstimo correspondente na lista de empréstimos
    for (int i = 0; i < emprestimos->quantidade; i++) {
        Emprestimo *emprestimo = &(emprestimos->lista[i]);
        if (emprestimo->idLivro == idLivro && emprestimo->idUtilizador == idUtilizador &&
            emprestimo->dataDevolucao == 0) {
            // Define a data de devolução como a data atual
            emprestimo->dataDevolucao = time(NULL);
            return true;
        }
    }
    return false;
}

bool renovarEmprestimo(Emprestimos *emprestimos, int idLivro, int idUtilizador) {
    // Procura pelo empréstimo correspondente na lista de empréstimos
    for (int i = 0; i < emprestimos->quantidade; ++i) {
        Emprestimo *emprestimo = &(emprestimos->lista[i]);
        if (emprestimo->idLivro == idLivro && emprestimo->idUtilizador == idUtilizador &&
            emprestimo->dataDevolucao == 0) {
            // Define a nova data esperada com mais 5 dias
            emprestimo->dataEsperada = emprestimo->dataEsperada + CINCO_DIAS_EM_SEGUNDOS;
            return true;
        }
    }
    return false;
}

void libertarMemoriaEmprestimos(Emprestimos *emprestimos) {
    free(emprestimos->lista);
}