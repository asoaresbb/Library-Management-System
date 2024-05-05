#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "gestao_livros.h"
#include "gestao_emprestimos.h"

#define VERDE "\033[1;32m"
#define AMARELO "\033[1;33m"
#define NEGRITO "\033[1m"
#define SUBLINHADO "\033[4m"
#define OMISSAO "\033[0m"

char pedirOpcaoMenu();

void trataAdicionarLivro(Acervo *acervo);

void trataRemoverLivro(Acervo *acervo, Emprestimos *emprestimos);

void trataEditarLivro(Acervo *acervo);

void trataPesquisarLivro(Acervo *acervo);

void trataImprimirAcervo(Acervo acervo);

void trataEmprestarLivro(Acervo acervo, Emprestimos *emprestimos);

void trataDevolverLivro(Acervo acervo, Emprestimos *emprestimos);

void trataRenovarEmprestimo(Acervo acervo, Emprestimos *emprestimos);

void trataListarEmprestimos(Emprestimos emprestimos, Acervo acervo);

int main() {
    Acervo acervo = {};
    int erroLivro = lerLivrosDoCSV("./livros.csv", &acervo);
    if (erroLivro) {
        printf("❌  Erro ao abrir o ficheiro de livros.\n");
        return 1;
    }
    Emprestimos emprestimos = {};
    int erroEmprestimos = lerEmprestimosDoCSV("./emprestimos.csv", &emprestimos);
    if (erroEmprestimos) {
        printf("❌  Erro ao abrir o ficheiro de empréstimos.\n");
        return 1;
    }

    printf("\n" VERDE);
    printf("╔═════════════════════════════════════════════╗\n");
    printf("║          " AMARELO "📚 GESTOR DE BIBLIOTECA 📚" VERDE "         ║\n");
    printf("╚═════════════════════════════════════════════╝\n");
    printf(OMISSAO "\n");

    while (true) {
        char opcao = pedirOpcaoMenu();
        switch (opcao) {
            case '+':
                trataAdicionarLivro(&acervo);
                break;
            case '-':
                trataRemoverLivro(&acervo, &emprestimos);
                break;
            case 'e':
                trataEditarLivro(&acervo);
                break;
            case 'p':
                trataPesquisarLivro(&acervo);
                break;
            case 'l':
                trataImprimirAcervo(acervo);
                break;
            case 'm':
                trataEmprestarLivro(acervo, &emprestimos);
                break;
            case 'd':
                trataDevolverLivro(acervo, &emprestimos);
                break;
            case 'r':
                trataRenovarEmprestimo(acervo, &emprestimos);
                break;
            case 'i':
                trataListarEmprestimos(emprestimos, acervo);
                break;
            case 's':
                libertarMemoriaAcervo(&acervo);
                libertarMemoriaEmprestimos(&emprestimos);
                printf(" ✅  A sair do programa...\n");
                return 0;
            default:
                printf(" ⚠️ Opção inválida %c.\n", opcao);
        }
        while ((getchar()) != '\n');
    }
}

char pedirOpcaoMenu() {
    printf(NEGRITO "\n 📝 Escolha uma opção:\n" OMISSAO);
    printf("   +  Adicionar livro\n");
    printf("   -  Remover livro\n");
    printf("   e  Editar livro\n");
    printf("   p  Pesquisar livro\n");
    printf("   l  Listar livros\n");
    printf("   m  Emprestar livro\n");
    printf("   d  Devolver livro\n");
    printf("   r  Renovar empréstimo\n");
    printf("   i  Listar empréstimos\n");
    printf("   s  Sair do programa\n");

    char opcao = getchar(); // Read one character from stdin
    if (opcao == EOF) {
        printf(" ❌  Acabou o input.\n");
        exit(1);
    }
    printf("\n");
    return tolower(opcao);
}

void trataAdicionarLivro(Acervo *acervo) {
    printf(" 📝 Escreva o título do livro: ");
    char titulo[50];
    scanf(" %49[^\n]", titulo);
    printf(" 📝 Escreva o autor do livro: ");
    char autor[100];
    scanf(" %99[^\n]", autor);
    printf(" 📝 Escreva o género do livro: ");
    char genero[20];
    scanf(" %19[^\n]", genero);
    adicionarLivro(acervo, titulo, autor, genero);
    printf(" ✅  O livro %s foi adicionado.\n", titulo);
}

void trataRemoverLivro(Acervo *acervo, Emprestimos *emprestimos) {
    trataImprimirAcervo(*acervo);
    int idLivroARemover = 0;
    printf(" 📝 Qual o id. do livro a remover? ");
    if (scanf(" %d", &idLivroARemover) != 1) { // Se não foi possível ler um inteiro
        printf(" ❌  Id. de livro inválido. Por favor, insira um número inteiro.\n");
        return;
    }

    // Verifica se o id fornecido existe no acervo
    if (obterLivro(acervo, idLivroARemover) == NULL) {
        printf(" ⚠️ O livro com id. %d não existe.\n", idLivroARemover);
        return;
    }

    // Verifica se há empréstimos ativos para este livro
    if (existeEmprestimosAtivos(emprestimos, idLivroARemover)) {
        printf(" ⚠️ Não é possível remover o livro. Existem empréstimos ativos para este livro.\n");
        return;
    }

    // Se não houver empréstimos ativos, proceda com a remoção
    removerLivro(acervo, idLivroARemover);
    printf(" ✅  Livro removido.\n");
}

void trataEditarLivro(Acervo *acervo) {
    printf("\n 📝 Qual o id. do livro a editar? ");
    int id = 0;
    if (scanf(" %d", &id) != 1) { // Se não foi possível ler um inteiro
        printf(" ❌  Id. de livro inválido. Por favor, insira um número inteiro.\n");
        return;
    }

    Livro *livroEditado = obterLivro(acervo, id);
    if (!livroEditado) {
        printf(" ⚠️ O livro com id. %d não existe.\n", id);
        return;
    }

    char textoLido[100]; // Tamanho máximo da linha a ser lida
    printf(" 📝 Escreva o novo título (escreva . para manter %s): ", livroEditado->titulo);
    scanf(" %39[^\n]", textoLido);
    if (strcmp(textoLido, ".") != 0)
        strcpy(livroEditado->titulo, textoLido);

    printf(" 📝 Escreva o novo autor (escreva . para manter %s): ", livroEditado->autor);
    scanf(" %99[^\n]", textoLido);
    if (strcmp(textoLido, ".") != 0)
        strcpy(livroEditado->autor, textoLido);

    printf(" 📝 Escreva o novo género (escreva . para manter %s): ", livroEditado->genero);
    scanf(" %39[^\n]", textoLido);
    if (strcmp(textoLido, ".") != 0)
        strcpy(livroEditado->genero, textoLido);

    printf(" ✅  Livro %s atualizado.\n", livroEditado->titulo);
}

void trataPesquisarLivro(Acervo *acervo) {
    printf(" 📝 Escreva o texto a pesquisar (por título, autor ou tipo): ");
    char textoPesquisa[40];
    scanf(" %39[^\n]", textoPesquisa); // Limita a leitura para evitar que o buffer rebente
    Acervo resultados = pesquisarLivros(acervo, textoPesquisa);
    if (resultados.quantidade == 0) {
        printf(" ✅  Não há resultados para a sua pesquisa.\n");
    } else {
        trataImprimirAcervo(resultados);
    }
    // Liberta a memória alocada para os resultados da pesquisa
    libertarMemoriaAcervo(&resultados);
}

void trataImprimirAcervo(Acervo acervo) {
    for (int i = 0; i < acervo.quantidade; i++) {
        printf("%d: %s (%s)\n", acervo.livros[i].id, acervo.livros[i].titulo, acervo.livros[i].autor);
        printf("   %s\n", acervo.livros[i].genero);
    }
}

void trataEmprestarLivro(Acervo acervo, Emprestimos *emprestimos) {
    printf(" 📝 Qual o id. do livro a emprestar? ");
    int idLivro;
    if (scanf(" %d", &idLivro) != 1) { // Se não foi possível ler um inteiro
        printf("  ❌  Id. de livro inválido. Por favor, insira um número inteiro.\n");
        return;
    }
    if (!obterLivro(&acervo, idLivro)) {
        printf(" ⚠️ O livro com id. %d não existe.\n", idLivro);
        return;
    }
    printf(" 📝 Qual o id. do utilizador? ");
    int idUtilizador;
    if (scanf(" %d", &idUtilizador) != 1) { // Se não foi possível ler um inteiro
        printf("  ❌  Id. do utilizador inválido. Por favor, insira um número inteiro.\n");
        return;
    }
    // TODO verificar que ainda existe exemplares disponiveis para emprestar
    emprestarLivro(emprestimos, idLivro, idUtilizador);
}

void trataDevolverLivro(Acervo acervo, Emprestimos *emprestimos) {
    printf(" 📝 Qual o id. do livro a ser devolvido? ");
    int idLivro;
    if (scanf(" %d", &idLivro) != 1) { // Se não foi possível ler um inteiro
        printf(" ❌  Id. de livro inválido. Por favor, insira um número inteiro.\n");
        return;
    }
    if (obterLivro(&acervo, idLivro) == NULL) {
        printf(" ⚠️ O livro com id. %d não existe.\n", idLivro);
        return;
    }
    printf(" 📝 Qual o id. do utilizador? ");
    int idUtilizador;
    if (scanf(" %d", &idUtilizador) != 1) { // Se não foi possível ler um inteiro
        printf(" ❌  Id. do utilizador inválido. Por favor, insira um número inteiro.\n");
        return;
    }
    bool devolvido = devolverLivro(emprestimos, idLivro, idUtilizador);
    if (devolvido)
        printf(" ✅  Livro devolvido com sucesso.\n");
    else
        printf(" ⚠️ Empréstimo não encontrado.\n");
}

void trataRenovarEmprestimo(Acervo acervo, Emprestimos *emprestimos) {
    printf(" 📝 Qual o id. do livro a ser renovado? ");
    int idLivro;
    if (scanf(" %d", &idLivro) != 1) { // Se não foi possível ler um inteiro
        printf(" ❌  Id. de livro inválido. Por favor, insira um número inteiro.\n");
        return;
    }
    if (obterLivro(&acervo, idLivro) == NULL) {
        printf(" ⚠️ O livro com id. %d não existe.\n", idLivro);
        return;
    }
    printf(" 📝 Qual o id. do utilizador? ");
    int idUtilizador;
    if (scanf(" %d", &idUtilizador) != 1) { // Se não foi possível ler um inteiro
        printf(" ❌  Id. do utilizador inválido. Por favor, insira um número inteiro.\n");
        return;
    }
    bool renovado = renovarEmprestimo(emprestimos, idLivro, idUtilizador);
    if (renovado)
        printf(" ✅  Empréstimo renovado com sucesso.\n");
    else
        printf(" ⚠️ Empréstimo não encontrado.\n");
}

void trataListarEmprestimos(Emprestimos emprestimos, Acervo acervo) {
    printf("%-35s| %-10s | %s | %s | %s \n", "Livro", "Utilizador", "Emprestado em", "Devolvido em", "Esperado em");
    for (int i = 0; i < emprestimos.quantidade; i++) {
        Emprestimo emprestimo = emprestimos.lista[i];
        char dataEmprestimoFormatada[11]; // Data de empréstimo formatada como: "YYYY-MM-DD"
        strftime(dataEmprestimoFormatada, sizeof(dataEmprestimoFormatada), "%Y-%m-%d", localtime(&emprestimo.data));

        char dataDevolucaoFormatada[11]; // Data de devolução formatada como: "YYYY-MM-DD"
        if (emprestimo.dataDevolucao > 0) {
            strftime(dataDevolucaoFormatada, sizeof(dataDevolucaoFormatada), "%Y-%m-%d",
                     localtime(&emprestimo.dataDevolucao));
        } else {
            strcpy(dataDevolucaoFormatada, " -------- ");
        }
        char dataEsperadaFormatada[11]; // Nova data de devolução após renovação formatada como: "YYYY-MM-DD"
        if (emprestimo.dataEsperada > 0) {
            strftime(dataEsperadaFormatada, sizeof(dataEsperadaFormatada), "%Y-%m-%d",
                     localtime(&emprestimo.dataEsperada));
        } else {
            strcpy(dataEsperadaFormatada, " -------- ");
        }
        Livro *livro = obterLivro(&acervo, emprestimo.idLivro);
        printf("%-6d - %-25s | %-10d | %s    | %s   | %s \n", emprestimo.idLivro,
               livro == NULL ? "(livro apagado)" : livro->titulo,
               emprestimo.idUtilizador,
               dataEmprestimoFormatada, dataDevolucaoFormatada, dataEsperadaFormatada);
    }
}