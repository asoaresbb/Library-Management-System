#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

char *readFile(char *filename);
int main()
{
    char path[1035];
    FILE *fp = popen("echo '-\n78s' | ./cli.exe", "r");
    assert(fp);
    char output[5000] = "";
    while (fgets(path, sizeof(path), fp) != NULL)
        strcat(output, path);

    assert(strstr(output, "Livro removido"));

    pclose(fp);
    printf("✅  Testes de utilizador passaram com sucesso!");
    return 0;
}