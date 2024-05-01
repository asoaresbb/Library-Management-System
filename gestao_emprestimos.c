#include <time.h>
#include "gestao_emprestimos.h"

void emprestarLivro(Emprestimos *emprestimos, int idLivro, int idUtilizador) {
    // Obtém o último empréstimo na lista (o próximo em que será inserido)
    Emprestimo *ultimoEmprestimo = &(emprestimos->lista[emprestimos->quantidade]);
    // Preenche os detalhes do novo empréstimo
    ultimoEmprestimo->idLivro = idLivro;
    ultimoEmprestimo->idUtilizador = idUtilizador;
    ultimoEmprestimo->data = time(NULL); // Obter a data atual como data de empréstimo
    emprestimos->quantidade++;
}

void devolverLivro(Emprestimos *emprestimos, int idLivro, int idUtilizador) {
    // Procura pelo empréstimo correspondente na lista de empréstimos
    for (int i = 0; i < emprestimos->quantidade; i++) {
        Emprestimo *emprestimo = &(emprestimos->lista[i]);
        if (emprestimo->idLivro == idLivro && emprestimo->idUtilizador == idUtilizador) {
            // Define a data de devolução como a data atual
            emprestimo->dataDevolucao = time(NULL);
            return;
        }
    }
}

void renovarEmprestimo(Emprestimos *emprestimos, int idLivro, int idUtilizador) {

}



