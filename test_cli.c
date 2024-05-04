#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include <regex.h>

void executarCli(char *resultadoEsperado, ...);
void assertContemTexto(const char *resultado, const char *texto);
void assertRegexCoincide(const char *resultado, const char *regex);
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

    assertRegexCoincide(resultadoEsperado, "[0-9]+: Java Basics \\(Helbert\\)");
    assertContemTexto(resultadoEsperado, "A sair do programa...");
}

void test_remover_livro()
{
    char resultadoEsperado[5000];

    executarCli(resultadoEsperado,
                "-", "78", // remover
                "l", "s",  // listar livros e sair
                NULL);

    assertContemTexto(resultadoEsperado, "Livro removido");
    assertContemTexto(resultadoEsperado, "A sair do programa...");
}

void test_emprestar_livro()
{
    char resultadoEsperado[5000];

    executarCli(resultadoEsperado,
                "m", "3", "103", // emprestar
                "i", "s",        // listar empréstimos e sair
                NULL);

    assertContemTexto(resultadoEsperado, "3      - Linguagem C               | 103");
    assertContemTexto(resultadoEsperado, "A sair do programa...");
}

void executarCli(char *resultadoEsperado, ...)
{
    // prepara comandos
    va_list comandosUt;
    va_start(comandosUt, resultadoEsperado);
    char comandosUtComNewline[300] = "";
    char *arg;
    while ((arg = va_arg(comandosUt, char *)) != NULL)
        sprintf(comandosUtComNewline + strlen(comandosUtComNewline), "%s\n", arg);
    va_end(comandosUt);
    // executa programa
    char comandoComExecutavel[320] = "";
    sprintf(comandoComExecutavel, "echo '%s' | ./cli.exe", comandosUtComNewline);
    FILE *pipe = popen(comandoComExecutavel, "r");
    assert(pipe);
    // coleta output (com um pipe de leitura)
    resultadoEsperado[0] = '\0';
    char path[1000];
    while (fgets(path, sizeof(path), pipe))
        strcat(resultadoEsperado, path);
    pclose(pipe);
}

void assertContemTexto(const char *resultado, const char *texto)
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

void assertRegexCoincide(const char *resultado, const char *regexPattern)
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
