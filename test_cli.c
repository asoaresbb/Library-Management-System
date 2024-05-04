#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void executarCli(const char *comando, char *resultadoEsperado);

void test_adicionar_livro();

void test_remover_livro();

void test_emprestar_livro();

int main() {
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
        printf("%s\n", resultado);
        printf("❌ O resultado não contém o texto:\n%s\n", textoEsperado);
        exit(1);
    }
}

void executarCli(const char *comando, char *resultadoEsperado) {
    char comandoComExecutavel[1035];
    sprintf(comandoComExecutavel, "echo '%s' | ./cli.exe", comando);
    FILE *fp = popen(comandoComExecutavel, "r");
    assert(fp);
    resultadoEsperado[0] = '\0'; // Inicializa a string vazia
    char path[1035];
    while (fgets(path, sizeof(path), fp) != NULL) {
        strcat(resultadoEsperado, path);
    }
    pclose(fp);
}

void test_adicionar_livro() {
    char resultadoEsperado[5000];
    
    executarCli("+\nJava Basics\nHelbert\ntécnico\nl\ns", resultadoEsperado);

    resultadoContem(resultadoEsperado, "79: Java Basics (Helbert)");
    resultadoContem(resultadoEsperado, "A sair do programa...");
}

void test_remover_livro() {
    char resultadoEsperado[5000];
    
    executarCli("-\n78\nl\ns", resultadoEsperado);

    resultadoContem(resultadoEsperado, "Livro removido");
    resultadoContem(resultadoEsperado, "A sair do programa...");
}

void test_emprestar_livro() {
    char resultadoEsperado[5000];
    
    executarCli("m\n3\n103\ni\ns", resultadoEsperado);

    resultadoContem(resultadoEsperado, "3      - Linguagem C               | 103");
    resultadoContem(resultadoEsperado, "A sair do programa...");
}


