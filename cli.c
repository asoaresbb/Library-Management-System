#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "gestao_livros.h"

void limparBufferEntrada()
{
    while ((getchar()) != '\n')
        ;
}

char pedirOpcaoMenu();
void trataAdicionarLivro(Acervo *acervo);
void trataRemoverLivro(Acervo *acervo);
void trataEditarLivro(Acervo *acervo);
void trataPesquisarLivro(Acervo *acervo);
void imprimirListaLivros(Acervo *acervo);

int main()
{
    Acervo acervo = {};
    // Adicionando pratos manualmente (substituir por CSV)
    adicionarLivro(&acervo, "Linguagem C", "Luís Damas", "literatura técnica");
    adicionarLivro(&acervo, "jQuery", "Luís Soares", "literatura técnica");

    printf("\n📖 📖 📖 📖 📖 📖 📖 📖 📖 📖 📖 📖 📖 📖\n");
    printf("📖 📖 📖  Gestor de Bibilioteca  📖 📖 📖 \n");
    printf("📖 📖 📖 📖 📖 📖 📖 📖 📖 📖 📖 📖 📖 📖\n\n");

    while (1)
    {
        switch (pedirOpcaoMenu())
        {
        case '+':
        case 'a':
            printf("\n");
            trataAdicionarLivro(&acervo);
            break;
        case '-':
        case 'r':
            printf("\n");
            trataRemoverLivro(&acervo);
            break;
        case 'e':
            printf("\n");
            trataEditarLivro(&acervo);
            break;
        case 'p':
            printf("\n");
            trataPesquisarLivro(&acervo);
            break;
        case 'l':
            printf("\n");
            imprimirListaLivros(&acervo);
            break;
        case 's':
        case 'q':
            printf(" ℹ️ A sair do programa...\n");
            return 0;
        default:
            printf(" ℹ️ Opção inválida. Tente novamente.\n");
        }
        limparBufferEntrada();
    }
    printf("\n");
    return 0;
}

char pedirOpcaoMenu()
{
    printf("\n ❓ Escolha uma opção:\n");
    printf("   +  Adicionar livro\n");
    printf("   -  Remover livro\n");
    printf("   e  Editar livro\n");
    printf("   p  Pesquisar livro\n");
    printf("   l  Listar livros\n");
    printf("   s  Sair do programa\n");
    char opcao[10];
    scanf("%s", opcao);
    return tolower(opcao[0]);
}

void trataAdicionarLivro(Acervo *acervo)
{
    limparBufferEntrada();
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

void trataRemoverLivro(Acervo *acervo)
{
    imprimirListaLivros(acervo);
    printf(" ❓ Selecione numero do livro a remover:");

    int idLivroARemover = 0;
    scanf("%d", &idLivroARemover);
    removerLivro(acervo, idLivroARemover);
    printf(" ℹ️ Livro removido.\n");
    return;
}

void trataEditarLivro(Acervo *acervo)
{
    imprimirListaLivros(acervo);
    printf("\n ❓ Que livro quer editar? ");
    int indiceLivroEditado = 0;
    scanf("%d", &indiceLivroEditado);
    indiceLivroEditado--;
    limparBufferEntrada();
    if (indiceLivroEditado < 0 || indiceLivroEditado > acervo->quantidade)
    {
        printf(" ℹ️ O livro escolhido nao existe.\n");
        return;
    }

    Livro livroEditado = acervo->livros[indiceLivroEditado];
    char textoLido[100]; // Tamanho máximo da linha a ser lida

    printf(" ❓ Escreva o novo título (escreva . para manter %s): ", livroEditado.titulo);
    scanf(" %49[^\n]", textoLido);
    if (strcmp(textoLido, ".") != 0)
        strcpy(livroEditado.titulo, textoLido);

    printf(" ❓ Escreva o novo autor (escreva . para manter %s): ", livroEditado.autor);
    scanf(" %99[^\n]", textoLido);
    if (strcmp(textoLido, ".") != 0)
        strcpy(livroEditado.autor, textoLido);

    printf(" ❓ Escreva o novo género (escreva . para manter %s): ", livroEditado.genero);
    scanf(" %19[^\n]", textoLido);
    if (strcmp(textoLido, ".") != 0)
        strcpy(livroEditado.genero, textoLido);

    atualizarLivro(acervo, indiceLivroEditado, livroEditado.titulo, livroEditado.autor, livroEditado.genero);

    printf(" ℹ️ Livro %s atualizado.\n", livroEditado.titulo);
}

void trataPesquisarLivro(Acervo *acervo)
{
    printf(" ❓ Escreva o texto a pesquisar (por título, autor ou tipo): ");
    char textoPesquisa[40];
    scanf("%s", textoPesquisa);
    Acervo resultados = pesquisarLivros(acervo, textoPesquisa);
    imprimirListaLivros(&resultados);
}

void imprimirListaLivros(Acervo *acervo)
{
    if (acervo->quantidade == 0)
    {
        printf(" ℹ️ A lista de livros está vazia.\n");
        return;
    }
    for (int i = 0; i < acervo->quantidade; i++)
    {
        printf("%d: %s (%s)\n", acervo->livros[i].id, acervo->livros[i].titulo, acervo->livros[i].autor);
        printf("   %s\n", acervo->livros[i].genero);
    }
}
