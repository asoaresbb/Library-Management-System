#include <time.h>
#include "gestao_emprestimos.h"

void emprestarLivro(Emprestimos *emprestimos, int idLivro, int idUtilizador) {
    Emprestimo *ultimoEmprestimo = &(emprestimos->lista[emprestimos->quantidade]);
    ultimoEmprestimo->idLivro = idLivro;
    ultimoEmprestimo->idUtilizador = idUtilizador;
    ultimoEmprestimo->data = time(NULL);
    emprestimos->quantidade++;
}



