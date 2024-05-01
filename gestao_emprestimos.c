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

            // Remove o empréstimo da lista de empréstimos
            // Move o último empréstimo para a posição do empréstimo que está a ser devolvido
            Emprestimo *ultimoEmprestimo = &(emprestimos->lista[emprestimos->quantidade - 1]);
            *emprestimo = *ultimoEmprestimo; // Copia o último empréstimo para a posição atual
            emprestimos->quantidade--; // Reduz a quantidade de empréstimos na lista
            return;
        }
    }
}

void renovarEmprestimo(Emprestimos *emprestimos, int idLivro, int idUtilizador) {

}



