#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "library.h"

void limparBufferEntrada()
{
    while ((getchar()) != '\n')
        ;
}

char pedirOpcaoMenu();

void trataAdicionarLivro(Acervo *acervo);

void trataRemoverLivro(Acervo *acervo);

void trataEditarLivro(Acervo *acervo);

void imprimirListaLivros(Acervo *acervo);

int main()
{
    Acervo acervo = {};
    // Adicionando pratos manualmente (substituir por CSV)
    Livro novoLivro1 = {"Linguagem C", "Luís Damas", "literatura técnica"};
    Livro novoLivro2 = {"jQuery", "Luís Soares", "literatura técnica"};
    adicionarLivro(&acervo, novoLivro1);
    adicionarLivro(&acervo, novoLivro2);

    printf("\n🍽️ 🍽️ 🍽️ 🍽️ 🍽️ 🍽️ 🍽️ 🍽️ 🍽️ 🍽️ 🍽️ 🍽️\n");
    printf("🍽️ 🍽️ 🍽️  Gestor de Bibilioteca  🍽️ 🍽️ 🍽️ \n");
    printf("🍽️ 🍽️ 🍽️ 🍽️ 🍽️ 🍽️ 🍽️ 🍽️ 🍽️ 🍽️ 🍽️ 🍽️ \n\n");

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
            // pesquisarLivro(acervo);
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
    printf("   l  Imprimir a lista de livros\n");
    printf("   p  Pesquisar livro\n");
    printf("   s  Sair do programa\n");
    char opcao[10];
    scanf("%s", opcao);
    return tolower(opcao[0]);
}

void trataAdicionarLivro(Acervo *acervo)
{
    limparBufferEntrada();
    Livro livroNovo;
    printf(" ❓ Escreva o título do livro: ");
    scanf(" %49[^\n]", livroNovo.titulo);
    printf(" ❓ Escreva o autor do livro: ");
    scanf(" %99[^\n]", livroNovo.autor);
    printf(" ❓ Escreva o género do livro: ");
    scanf(" %19[^\n]", livroNovo.genero);
    adicionarLivro(acervo, livroNovo);
    printf(" ℹ️ O livro %s foi adicionado.\n", livroNovo.titulo);
}

void trataRemoverLivro(Acervo *acervo)
{
    imprimirListaLivros(acervo);
    printf(" ❓ Selecione numero do livro a remover:");

    int indiceLivroARemover = 0;
    scanf("%d", &indiceLivroARemover);
    indiceLivroARemover--;
    if (indiceLivroARemover < 0 || indiceLivroARemover > acervo->quantidade)
    {
        printf(" ℹ️ O livro escolhido nao existe.\n");
        return;
    }

    removerLivro(acervo, indiceLivroARemover);
    printf(" ℹ️ Livro removido com sucesso!\n");
    return;
}

void trataEditarLivro(Acervo *acervo)
{
    imprimirListaLivros(acervo);
    printf(" ❓ Que livro quer editar? ");
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
    char textoLido[50]; // Tamanho máximo da linha a ser lida

    printf(" ❓ Escreva o novo título (enter para manter %s): ", livroEditado.titulo);
    fgets(textoLido, sizeof(textoLido), stdin);
    textoLido[strcspn(textoLido, "\n")] = '\0'; // Remove o \n se presente
    if (strlen(textoLido) > 0)                  // Verifica se foi digitado algo antes do Enter
        strcpy(livroEditado.titulo, textoLido);

    printf(" ❓ Escreva o novo autor (enter para manter %s): ", livroEditado.autor);
    fgets(textoLido, sizeof(textoLido), stdin);
    textoLido[strcspn(textoLido, "\n")] = '\0';
    if (strlen(textoLido) > 0)
        strcpy(livroEditado.autor, textoLido);

    printf(" ❓ Escreva o novo género (enter para manter %s): ", livroEditado.genero);
    fgets(textoLido, sizeof(textoLido), stdin);
    textoLido[strcspn(textoLido, "\n")] = '\0';
    if (strlen(textoLido) > 0)
        strcpy(livroEditado.genero, textoLido);

    atualizarLivro(acervo, indiceLivroEditado, livroEditado);

    printf(" ℹ️ Livro atualizado com sucesso. (enter para voltar ao menu)\n");
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
        printf("%d: %s (%s) \n", i + 1, acervo->livros[i].titulo, acervo->livros[i].autor);
        printf("   %s\n", acervo->livros[i].genero);
    }
}
