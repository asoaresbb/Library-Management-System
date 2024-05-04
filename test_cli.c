#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

char *readFile(char *filename);

void test_remover_livro();

void test_emprestar_livro();

int main() {

    test_remover_livro();
    test_emprestar_livro();
    printf("✅  Testes de utilizador passaram com sucesso!");
    return 0;
}

void test_remover_livro() {
    char path[1035];
    FILE *fp = popen("echo '-\n78s' | ./cli.exe", "r");
    assert(fp);
    char output[5000] = "";
    while (fgets(path, sizeof(path), fp) != NULL)
        strcat(output, path);

    assert(strstr(output, "Livro removido"));
    assert(strstr(output, "A sair do programa..."));

    pclose(fp);
}

void test_emprestar_livro() {
    char path[1035];
    FILE *fp = popen("echo 'm1\n2\nis' | ./cli.exe", "r");
    assert(fp);
    char output[5000] = "";
    while (fgets(path, sizeof(path), fp) != NULL)
        strcat(output, path);

    assert(strstr(output, "1      - A Arte da Guerra          | 1 "));
    assert(strstr(output, "A sair do programa..."));

    pclose(fp);
}

