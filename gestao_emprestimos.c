#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "gestao_emprestimos.h"

#define MAX_EMPRESTIMOS 100
#define CINCO_DIAS_EM_SEGUNDOS (5 * 24 * 60 * 60)
#define QUINZE_DIAS_EM_SEGUNDOS (15 * 24 * 60 * 60)

int lerEmprestimosDoCSV(const char *nomeArquivo, Emprestimos *emprestimos) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        return 1; // Erro ao abrir o arquivo
    }

    char linha[256];
    const char *delim = ",";

    // Variáveis temporárias para armazenar dados lidos do CSV
    int idLivro, idUtilizador;
    time_t data, dataDevolucao, dataEsperada;

    emprestimos->quantidade = 0; // Inicializa a quantidade de empréstimos

    // Ler cada linha do arquivo CSV
    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = '\0';

        // Extrair os dados do empréstimo a partir da linha
        char *token = strtok(linha, delim); // ID do Livro
        if (token) {
            idLivro = atoi(token);
        }

        token = strtok(NULL, delim); // ID do Utilizador
        if (token) {
            idUtilizador = atoi(token);
        }

        token = strtok(NULL, delim); // Data
        if (token) {
            data = (time_t) atol(token);
        }

        token = strtok(NULL, delim); // Data de Devolução
        if (token) {
            dataDevolucao = (time_t) atol(token);
        }

        token = strtok(NULL, delim); // Data Esperada
        if (token) {
            dataEsperada = (time_t) atol(token);
        }

        // Adicionar empréstimo à lista
        if (emprestimos->quantidade < MAX_EMPRESTIMOS) {
            Emprestimo *novoEmprestimo = &emprestimos->lista[emprestimos->quantidade];
            novoEmprestimo->idLivro = idLivro;
            novoEmprestimo->idUtilizador = idUtilizador;
            novoEmprestimo->data = data;
            novoEmprestimo->dataDevolucao = dataDevolucao;
            novoEmprestimo->dataEsperada = dataEsperada;
            emprestimos->quantidade++;
        } else {
            // Capacidade máxima atingida
            break;
        }
    }

    fclose(arquivo);
    return 0; // Sucesso
}

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