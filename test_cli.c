#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void LerEntrada(const char *comando, char *resultadoEsperado);

void test_remover_livro();

void test_emprestar_livro();

int main() {
    //test_remover_livro();
    test_emprestar_livro();
    printf("✅  Testes de utilizador passaram com sucesso!\n");
    return 0;
}

void LerEntrada(const char *comando, char *resultadoEsperado) {
    char path[1035];
    FILE *fp = popen(comando, "r");
    assert(fp);
    resultadoEsperado[0] = '\0'; // Inicializa a string vazia
    while (fgets(path, sizeof(path), fp) != NULL) {
        strcat(resultadoEsperado, path);
    }
    pclose(fp);
}

void test_remover_livro() {
    char resultadoEsperado[5000];
    LerEntrada("echo '-\n78\nl\ns' | ./cli.exe", resultadoEsperado);
    //printf("Conteúdo de resultado esperado:\n%s\n", resultadoEsperado);
    assert(strstr(resultadoEsperado, "Livro removido"));
    assert(strstr(resultadoEsperado, "A sair do programa..."));
}

void test_emprestar_livro() {
    char resultadoEsperado[5000];
    LerEntrada("echo 'm\n3\n103\ni\ns' | ./cli.exe", resultadoEsperado);
    //printf("Conteúdo de resultado esperado:\n%s\n", resultadoEsperado);
    assert(strstr(resultadoEsperado, "3      - Linguagem C               | 103"));
    assert(strstr(resultadoEsperado, "A sair do programa..."));
}
