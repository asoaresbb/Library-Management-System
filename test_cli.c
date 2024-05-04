#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include <regex.h>
#include <stdbool.h>

void executarCli(char *output, ...);

bool contemTexto(const char *resultado, const char *texto);

bool regexCoincide(const char *resultado, const char *regex);

void test_adicionar_livro();

void test_remover_livro();

void test_emprestar_livro();

void test_devolver_livro();

int main() {
    test_adicionar_livro();
    test_remover_livro();
    test_emprestar_livro();
    test_devolver_livro();
    return 0;
}

void test_adicionar_livro() {
    char output[5000];

    executarCli(output,
                "+", "Java Basics", "Helbert", "técnico", // criar livro
                "L", "s",                                 // listar livros
                NULL);                                    // sair

    assert(regexCoincide(output, "[0-9]+: Java Basics \\(Helbert\\)"));
    assert(contemTexto(output, "A sair do programa..."));
}

void test_remover_livro() {
    char output[5000];

    executarCli(output,
                "-", "78",  // remover livro
                "L",        // listar livros
                "s", NULL); // sair

    assert(contemTexto(output, "Livro removido"));
    assert(contemTexto(output, "A sair do programa..."));
}

void test_emprestar_livro() {
    char output[5000];

    executarCli(output,
                "m", "3", "110", // emprestar
                "I",             // listar empréstimos
                "S", NULL);      // sair

    assert(regexCoincide(output, 
        "3      - Linguagem C               \\| 110        \\| [0-9]{4}-[0-9]{2}-[0-9]{2}    \\|  --------    \\| [0-9]{4}-[0-9]{2}-[0-9]{2}"));
    assert(contemTexto(output, "A sair do programa..."));
}

void test_devolver_livro() {
    char output[5000];

    executarCli(output,
                "d", "12", "115", // devolver
                "I",              // listar empréstimos
                "S", NULL);       // sair

    assert(regexCoincide(output, 
        "12     - 1984                      \\| 115        \\| [0-9]{4}-[0-9]{2}-[0-9]{2}    \\| [0-9]{4}-[0-9]{2}-[0-9]{2}   \\|  --------"));
    assert(contemTexto(output, "A sair do programa..."));
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

bool contemTexto(const char *resultado, const char *texto) {
    bool contido = strstr(resultado, texto);
    if (!contido) 
        printf("%s\n", resultado);
    return contido;
}

bool regexCoincide(const char *text, const char *pattern) {
    regex_t regex;
    int compilada = regcomp(&regex, pattern, REG_EXTENDED);
    assert(compilada == 0);
    int reti = regexec(&regex, text, 0, NULL, 0);
    if (reti)
        printf("%s\n", text);
    regfree(&regex);
    return reti == 0;
}
