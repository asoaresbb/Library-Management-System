#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h> // Para usar varargs
#include <assert.h>

void executarCli(char *resultadoEsperado, ...);
void resultadoContem(const char *resultado, const char *textoEsperado);
void test_adicionar_livro();
void test_remover_livro();
void test_emprestar_livro();

int main()
{
    test_adicionar_livro();
    test_remover_livro();
    test_emprestar_livro();
    printf("✅  Testes de utilizador passaram com sucesso!\n");
    return 0;
}

void resultadoContem(const char *resultado, const char *textoEsperado)
{
    if (!strstr(resultado, textoEsperado))
    {
        printf("❌ O resultado não contém o texto esperado:\n%s\n", resultado);
        exit(1);
    }
}

void test_adicionar_livro()
{
    char resultadoEsperado[5000];

    executarCli(resultadoEsperado,
                "+", "Java Basics", "Helbert", "técnico", // criar
                "l", "s",                                 // listar livros e sair
                NULL);

    resultadoContem(resultadoEsperado, "79: Java Basics (Helbert)");
    resultadoContem(resultadoEsperado, "A sair do programa...");
}

void test_remover_livro()
{
    char resultadoEsperado[5000];

    executarCli(resultadoEsperado,
                "-", "78", // remover
                "l", "s",  // listar livros e sair
                NULL);

    resultadoContem(resultadoEsperado, "Livro removido");
    resultadoContem(resultadoEsperado, "A sair do programa...");
}

void test_emprestar_livro()
{
    char resultadoEsperado[5000];

    executarCli(resultadoEsperado,
                "m", "3", "103", // emprestar
                "i", "s",        // listar empréstimos e sair
                NULL);

    resultadoContem(resultadoEsperado, "3      - Linguagem C               | 103");
    resultadoContem(resultadoEsperado, "A sair do programa...");
}

void executarCli(char *resultadoEsperado, ...)
{
    va_list textosUtilizador;
    va_start(textosUtilizador, resultadoEsperado);
    char comandoComExecutavel[1035];
    char comando[5000] = "";
    char *arg;
    while ((arg = va_arg(textosUtilizador, char *)) != NULL)
    {
        strcat(comando, arg);
        strcat(comando, "\n");
    }

    sprintf(comandoComExecutavel, "echo '%s' | ./cli.exe", comando);
    FILE *pipe = popen(comandoComExecutavel, "r");
    assert(pipe);
    resultadoEsperado[0] = '\0'; // Inicializa a string vazia
    char path[1035];
    while (fgets(path, sizeof(path), pipe))
        strcat(resultadoEsperado, path);
    pclose(pipe);
    va_end(textosUtilizador);
}
