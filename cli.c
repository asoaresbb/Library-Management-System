#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "gestao_livros.h"
#include "gestao_emprestimos.h"

char pedirOpcaoMenu();

void trataAdicionarLivro(Acervo *acervo);

void trataRemoverLivro(Acervo *acervo);

void trataEditarLivro(Acervo *acervo);

void trataPesquisarLivro(Acervo *acervo);

void trataImprimirAcervo(Acervo acervo);

void trataEmprestarLivro(Acervo acervo, Emprestimos *emprestimos);

void trataDevolverLivro(Acervo acervo, Emprestimos *emprestimos);

void trataRenovarEmprestimo(Acervo acervo, Emprestimos *emprestimos);

void trataListarEmprestimos(Emprestimos emprestimos, Acervo acervo);

int main() {
    Acervo acervo = {};
    // Adicionando pratos manualmente (substituir por CSV)
    adicionarLivro(&acervo, "Linguagem C", "Luís Damas", "literatura técnica");
    adicionarLivro(&acervo, "jQuery", "Luís Soares", "literatura técnica");

    Emprestimos emprestimos = {};

    printf("\n📖 📖 📖 📖 📖 📖 📖 📖 📖 📖 📖 📖 📖 📖\n");
    printf("📖 📖 📖  Gestor de Bibilioteca  📖 📖 📖 \n");
    printf("📖 📖 📖 📖 📖 📖 📖 📖 📖 📖 📖 📖 📖 📖\n");

    while (1) {
        printf("\n");
        switch (pedirOpcaoMenu()) {
            case '+':
                trataAdicionarLivro(&acervo);
                break;
            case '-':
                trataRemoverLivro(&acervo);
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
                printf(" ℹ️ A sair do programa...\n");
                return 0;
            default:
                printf(" ℹ️ Opção inválida.\n");
        }
    }
    printf("\n");
    return 0;
}

char pedirOpcaoMenu() {
    printf("\n ❓ Escolha uma opção:\n");
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
    char opcao[10];
    scanf("%s", opcao);
    printf("\n");
    return tolower(opcao[0]);
}

void trataAdicionarLivro(Acervo *acervo) {
    printf(" ❓ Escreva o título do livro: ");
    char titulo[50];
    scanf(" %49[^\n]", titulo);
    printf(" ❓ Escreva o autor do livro: ");
    char autor[100];
    scanf(" %99[^\n]", autor);
    printf(" ❓ Escreva o género do livro: ");
    char genero[20];
    scanf(" %19[^\n]", genero);
    adicionarLivro(acervo, titulo, autor, genero);
    printf(" ℹ️ O livro %s foi adicionado.\n", titulo);
}

void trataRemoverLivro(Acervo *acervo) {
    trataImprimirAcervo(*acervo);
    int idLivroARemover = 0;
    printf(" ❓ Qual o id. do livro a remover? ");
    if (scanf("%d", &idLivroARemover) != 1) {
        // Se não foi possível ler um inteiro
        printf(" ❌ Id. do livro inválido. Por favor, insira um número inteiro.\n");
        // Limpa o buffer de entrada para evitar loops infinitos
        while (getchar() != '\n'); // Descarta a restante entrada
        return;
    }

    if (obterLivro(acervo, idLivroARemover) == NULL) {
        printf(" ℹ️ O livro com id. %d não existe.\n", idLivroARemover);
        return;
    }
    removerLivro(acervo, idLivroARemover);
    printf(" ℹ️ Livro removido.\n");
    return;
}

void trataEditarLivro(Acervo *acervo) {
    trataImprimirAcervo(*acervo);
    printf("\n ❓ Qual o id. do livro a editar? ");
    int id = 0;
    if (scanf("%d", &id) != 1) {
        // Se não foi possível ler um inteiro
        printf(" ❌ Id. do livro inválido. Por favor, insira um número inteiro.\n");
        // Limpa o buffer de entrada para evitar loops infinitos
        while (getchar() != '\n'); // Descarta a restante entrada
        return;
    }

    Livro *livroEditado = obterLivro(acervo, id);
    if (livroEditado == NULL) {
        printf(" ℹ️ O livro com id. %d não existe.\n", id);
        return;
    }
    char textoLido[100]; // Tamanho máximo da linha a ser lida

    printf(" ❓ Escreva o novo título (escreva . para manter %s): ", livroEditado->titulo);
    scanf(" %49[^\n]", textoLido);
    if (strcmp(textoLido, ".") != 0)
        strcpy(livroEditado->titulo, textoLido);

    printf(" ❓ Escreva o novo autor (escreva . para manter %s): ", livroEditado->autor);
    scanf(" %99[^\n]", textoLido);
    if (strcmp(textoLido, ".") != 0)
        strcpy(livroEditado->autor, textoLido);

    printf(" ❓ Escreva o novo género (escreva . para manter %s): ", livroEditado->genero);
    scanf(" %19[^\n]", textoLido);
    if (strcmp(textoLido, ".") != 0)
        strcpy(livroEditado->genero, textoLido);

    printf(" ℹ️ Livro %s atualizado.\n", livroEditado->titulo);
}

void trataPesquisarLivro(Acervo *acervo) {
    printf(" ❓ Escreva o texto a pesquisar (por título, autor ou tipo): ");
    char textoPesquisa[40];
    scanf("%s", textoPesquisa);
    Acervo resultados = pesquisarLivros(acervo, textoPesquisa);
    trataImprimirAcervo(resultados);
}

void trataImprimirAcervo(Acervo acervo) {
    if (acervo.quantidade == 0)
        printf(" ℹ️ A lista de livros está vazia.\n");

    for (int i = 0; i < acervo.quantidade; i++) {
        printf("%d: %s (%s)\n", acervo.livros[i].id, acervo.livros[i].titulo, acervo.livros[i].autor);
        printf("   %s\n", acervo.livros[i].genero);
    }
}

void trataEmprestarLivro(Acervo acervo, Emprestimos *emprestimos) {
    printf(" ❓ Qual o id. do livro a emprestar? ");
    int idLivro;
    if (scanf("%d", &idLivro) != 1) {
        // Se não foi possível ler um inteiro
        printf(" ❌ Id. do livro inválido. Por favor, insira um número inteiro.\n");
        // Limpa o buffer de entrada para evitar loops infinitos
        while (getchar() != '\n'); // Descarta a restante entrada
        return;
    }
    if (obterLivro(&acervo, idLivro) == NULL) {
        printf(" ℹ️ O livro com id. %d não existe.\n", idLivro);
        return;
    }

    printf(" ❓ Qual o id. do utilizador? ");
    int idUtilizador;
    if (scanf("%d", &idUtilizador) != 1) {
        // Se não foi possível ler um inteiro
        printf(" ❌ Id. do utilizador inválido. Por favor, insira um número inteiro.\n");
        // Limpa o buffer de entrada para evitar loops infinitos
        while (getchar() != '\n'); // Descarta a restante entrada
        return;
    }

    emprestarLivro(emprestimos, idLivro, idUtilizador);
}

void trataDevolverLivro(Acervo acervo, Emprestimos *emprestimos) {
    printf(" ❓ Qual o id. do livro a ser devolvido? ");
    int idLivro;
    if (scanf("%d", &idLivro) != 1) {
        // Se não foi possível ler um inteiro
        printf(" ❌ ID do livro inválido. Por favor, insira um número inteiro.\n");
        // Limpa o buffer de entrada para evitar loops infinitos
        while (getchar() != '\n');  // Descarta a restante entrada
        return;
    }
    if (obterLivro(&acervo, idLivro) == NULL) {
        printf(" ℹ️ O livro com id. %d não existe.\n", idLivro);
        return;
    }

    printf(" ❓ Qual o id. do utilizador? ");
    int idUtilizador;
    if (scanf("%d", &idUtilizador) != 1) {
        // Se não foi possível ler um inteiro
        printf(" ❌ ID do utilizador inválido. Por favor, insira um número inteiro.\n");
        // Limpa o buffer de entrada para evitar loops infinitos
        while (getchar() != '\n');  // Descarta a restante entrada
        return;
    }

    devolverLivro(emprestimos, idLivro, idUtilizador);
    printf(" ℹ️ Livro devolvido com sucesso.\n");
}

void trataRenovarEmprestimo(Acervo acervo, Emprestimos *emprestimos) {

}

void trataListarEmprestimos(Emprestimos emprestimos, Acervo acervo) {
    printf("%-35s| %-10s | %s \n", "Livro", "Utilizador", "Data");
    for (int i = 0; i < emprestimos.quantidade; i++) {
        Emprestimo emprestimo = emprestimos.lista[i];
        char dataEmprestimoFormatada[11]; // Data de empréstimo formatada como: "YYYY-MM-DD"
        strftime(dataEmprestimoFormatada, sizeof(dataEmprestimoFormatada), "%Y-%m-%d", localtime(&emprestimo.data));
        Livro *livro = obterLivro(&acervo, emprestimo.idLivro);
        printf("%-6d - %-25s | %-10d | %s \n", emprestimo.idLivro, livro->titulo, emprestimo.idUtilizador,
               dataEmprestimoFormatada);
    }
}