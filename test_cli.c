#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

char *readFile(char *filename);

int main()
{
    FILE *pipe = popen("./cli.exe > /tmp/test_output.txt", "w");
    assert(pipe);
    fprintf(pipe, "+\n"); // criar livro
    fprintf(pipe, "Livro titulo\n");
    fprintf(pipe, "autor123\n");
    fprintf(pipe, "tecnico\n");
    fprintf(pipe, "l\n"); // listar
    fprintf(pipe, "q\n"); // sair
    fclose(pipe);

    char *content = readFile("/tmp/test_output.txt");

    // printf("content %s", content);
    assert(strstr(content, ": Livro titulo (autor123)\n   tecnico"));
    return 0;
}

char *readFile(char *filename)
{
    FILE *f = fopen(filename, "rt");
    assert(f);
    fseek(f, 0, SEEK_END);
    long length = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *buffer = (char *)malloc(length + 1);
    buffer[length] = '\0';
    fread(buffer, 1, length, f);
    fclose(f);
    return buffer;
}
