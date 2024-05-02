#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "gestao_emprestimos.h"

#define CINCO_DIAS_EM_SEGUNDOS (5 * 24 * 60 * 60)
#define QUINZE_DIAS_EM_SEGUNDOS (15 * 24 * 60 * 60)

void criarEmprestimo(Emprestimos *emprestimos, Emprestimo emprestimo)
{
    // Realocar memoria dinamicamente
    emprestimos->lista = realloc(emprestimos->lista, (emprestimos->quantidade + 1) * sizeof(Emprestimo));
    // coloca no próximo em que será inserido
    emprestimos->lista[emprestimos->quantidade] = emprestimo;
}

int lerEmprestimosDoCSV(const char *nomeFicheiro, Emprestimos *emprestimos) {
    FILE *ficheiro = fopen(nomeFicheiro, "r");
    if (ficheiro == NULL) return 1; // Erro ao abrir o ficheiro
    char linha[256];
    while (fgets(linha, sizeof(linha), ficheiro)) {
        linha[strcspn(linha, "\n")] = '\0'; // retirar o caracter de mudança de linha
        Emprestimo novoEmprestimo = {};
        // Extrair os dados do empréstimo a partir da linha
        printf("linha:-%s-\n", linha);
        if (sscanf(linha, "\"%d\",\"%d\",\"%ld\",\"%ld\",\"%ld\"",
                   &novoEmprestimo.idLivro, &novoEmprestimo.idUtilizador,
                   &novoEmprestimo.data, &novoEmprestimo.dataDevolucao, &novoEmprestimo.dataEsperada))
        {
            criarEmprestimo(emprestimos, novoEmprestimo); // Adicionar empréstimo à lista
        }
    }

    fclose(ficheiro);
    return 0; // Sucesso
}

void emprestarLivro(Emprestimos *emprestimos, int idLivro, int idUtilizador) {
    Emprestimo novoEmprestimo = {0};
    // Preenche os detalhes do novo empréstimo
    novoEmprestimo.idLivro = idLivro;
    novoEmprestimo.idUtilizador = idUtilizador;
    novoEmprestimo.data = time(NULL); // Obter a data atual como data de empréstimo
    novoEmprestimo.dataEsperada = novoEmprestimo.data + QUINZE_DIAS_EM_SEGUNDOS;
    novoEmprestimo.dataDevolucao = 0;
    criarEmprestimo(emprestimos, novoEmprestimo);
    // Realocar memoria dinamicamente
    emprestimos->lista = realloc(emprestimos->lista, (emprestimos->quantidade + 1) * sizeof(Emprestimo));
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
            emprestimo->dataEsperada = 0;
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

bool existeEmprestimosAtivos(Emprestimos *emprestimos, int idLivro) {
    for (int i = 0; i < emprestimos->quantidade; ++i) {
        Emprestimo *emprestimo = &(emprestimos->lista[i]);
        if (emprestimo->idLivro == idLivro && emprestimo->dataDevolucao == 0) {
            // Se encontrar um empréstimo ativo para o livro especificado
            return true;
        }
    }
    return false;
}

void libertarMemoriaEmprestimos(Emprestimos *emprestimos) {
    free(emprestimos->lista);
}