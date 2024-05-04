#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include <regex.h>

void executarCli(char *resultadoEsperado, ...);
void resultadoContemTexto(const char *resultado, const char *texto);
void resultadoContemRegex(const char *resultado, const char *regex);
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

void test_adicionar_livro()
{
    char resultadoEsperado[5000];

    executarCli(resultadoEsperado,
                "+", "Java Basics", "Helbert", "técnico", // criar livro
                "l", "s",                                 // listar livros e sair
                NULL);

    resultadoContemRegex(resultadoEsperado, "[0-9]+: Java Basics \\(Helbert\\)");
    resultadoContemTexto(resultadoEsperado, "A sair do programa...");
}

void test_remover_livro()
{
    char resultadoEsperado[5000];

    executarCli(resultadoEsperado,
                "-", "78", // remover
                "l", "s",  // listar livros e sair
                NULL);

    resultadoContemTexto(resultadoEsperado, "Livro removido");
    resultadoContemTexto(resultadoEsperado, "A sair do programa...");
}

void test_emprestar_livro()
{
    char resultadoEsperado[5000];

    executarCli(resultadoEsperado,
                "m", "3", "103", // emprestar
                "i", "s",        // listar empréstimos e sair
                NULL);

    resultadoContemTexto(resultadoEsperado, "3      - Linguagem C               | 103");
    resultadoContemTexto(resultadoEsperado, "A sair do programa...");
}

void executarCli(char *resultadoEsperado, ...)
{
    va_list textosUtilizador;
    va_start(textosUtilizador, resultadoEsperado);
    char comandoComExecutavel[1035];
    char comando[5000] = "";
    char *arg;
    // envia comandos
    while ((arg = va_arg(textosUtilizador, char *)) != NULL)
        sprintf(comando + strlen(comando), "%s\n", arg);
    va_end(textosUtilizador);
    sprintf(comandoComExecutavel, "echo '%s' | ./cli.exe", comando);
    // coleta output do programa com um pipe de leitura
    FILE *pipe = popen(comandoComExecutavel, "r");
    assert(pipe);
    resultadoEsperado[0] = '\0';
    char path[1000];
    while (fgets(path, sizeof(path), pipe))
        strcat(resultadoEsperado, path);
    pclose(pipe);
}

void resultadoContemTexto(const char *resultado, const char *texto)
{
    if (!strstr(resultado, texto))
    {
        printf("------------------------------------------\n");
        printf("%s\n", resultado);
        printf("------------------------------------------\n");
        printf("❌ O resultado acima não contém o texto:\n%s\n", texto);
        exit(1);
    }
}

void resultadoContemRegex(const char *resultado, const char *regexPattern)
{
    regex_t regex;
    assert(regcomp(&regex, regexPattern, REG_EXTENDED) != REG_NOMATCH);
    if (regexec(&regex, resultado, 0, NULL, 0))
    {
        printf("------------------------------------------\n");
        printf("%s\n", resultado);
        printf("------------------------------------------\n");
        printf("❌ O resultado acima não contém o padrão:\n%s\n", regexPattern);
        exit(1);
    }
    regfree(&regex);
}
