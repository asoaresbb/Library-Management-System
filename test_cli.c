#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include <regex.h>

void executarCli(char *output, ...);

void assertContemTexto(const char *resultado, const char *texto);

void assertRegexCoincide(const char *resultado, const char *regex);

void test_adicionar_livro();

void test_remover_livro();

void test_emprestar_livro();

void test_devolver_livro();

int main() {
    test_adicionar_livro();
    test_remover_livro();
    test_emprestar_livro();
    test_devolver_livro();
    printf("✅  Testes de utilizador passaram com sucesso!\n");
    return 0;
}

void test_adicionar_livro() {
    char output[5000];

    executarCli(output,
                "+", "Java Basics", "Helbert", "técnico", // criar livro
                "L", "s",                                 // listar livros e sair
                NULL);

    assertRegexCoincide(output, "[0-9]+: Java Basics \\(Helbert\\)");
    assertContemTexto(output, "A sair do programa...");
}

void test_remover_livro() {
    char output[5000];

    executarCli(output,
                "-", "78", // remover
                "L", "s",  // listar livros e sair
                NULL);

    assertContemTexto(output, "Livro removido");
    assertContemTexto(output, "A sair do programa...");
}

void test_emprestar_livro() {
    char output[5000];

    executarCli(output,
                "m", "3", "110", // emprestar
                "I", "S",        // listar empréstimos e sair
                NULL);

    assertRegexCoincide(output, "3      - Linguagem C               | 110        | \\d{4}-\\d{2}-\\d{2}");
    assertContemTexto(output, "A sair do programa...");
}

void test_devolver_livro() {
    char output[5000];

    executarCli(output,
                "d", "12", "115", // devolver
                "I", "S",        // listar empréstimos e sair
                NULL);

    assertRegexCoincide(output, "12     - 1984                      | 115        | \\d{4}-\\d{2}-\\d{2}");
    assertContemTexto(output, "A sair do programa...");
}

void executarCli(char *outputPrograma, ...) {
    // prepara comandos: converte ["m","3","103","S"] em "m\n3\n103\nS"
    va_list comandosUt;
    va_start(comandosUt, outputPrograma);
    char comandosUtComNewline[300] = "";
    char *arg;
    while ((arg = va_arg(comandosUt, char *)) != NULL)
        sprintf(comandosUtComNewline + strlen(comandosUtComNewline), "%s\n", arg);
    va_end(comandosUt);
    // executa programa: converte "m\n3\n103\nS" em "echo '"m\n3\n103\nS"' | cli ./cli.exe" e corre
    char comandoComExecutavel[320] = "";
    sprintf(comandoComExecutavel, "echo '%s' | ./cli.exe", comandosUtComNewline);
    FILE *pipe = popen(comandoComExecutavel, "r");
    assert(pipe);
    // coleta output do programa (com um pipe de leitura)
    outputPrograma[0] = '\0';
    char path[1000];
    while (fgets(path, sizeof(path), pipe))
        strcat(outputPrograma, path);
    pclose(pipe);
}

void assertContemTexto(const char *resultado, const char *texto) {
    if (!strstr(resultado, texto)) {
        printf("------------------------------------------\n");
        printf("%s\n", resultado);
        printf("------------------------------------------\n");
        printf("❌  O resultado acima não contém o texto:\n%s\n", texto);
        exit(1);
    }
}

void assertRegexCoincide(const char *resultado, const char *expressao) {
    regex_t regex;
    assert(regcomp(&regex, expressao, REG_EXTENDED) != REG_NOMATCH);
    if (regexec(&regex, resultado, 0, NULL, 0)) {
        printf("------------------------------------------\n");
        printf("%s\n", resultado);
        printf("------------------------------------------\n");
        printf("❌  O resultado acima não contém a expressão:\n%s\n", expressao);
        exit(1);
    }
    regfree(&regex);
}
