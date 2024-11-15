/*
    Membros do grupo
    Cauan Souza, Rebeca Ruivo, Felipe Pereira, Gabriel Sanches
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "img.h"

void help() // explicar como usar as funções limiar e inversa
{
    printf("./main limiar (nome do arquivo com .pgm) (valor do limiar)\n");
    printf("./main inversa (nome do arquivo com pgm)\n");
}

int main(int argc, char *argv[])
{

    if ((strcmp(argv[1], "limiar") == 0) && (argc == 4)) //verifica se o primeiro argumento de argv é limiar e se argc contou 4 argumentos
    {
        FILE *pgm = fopen(argv[2], "r"); // abre o arquivo e lê o terceiro argumento de argv
        imgb I = read_img(pgm); // atribui o conteúdo do arquivo à struct I
        int x;
        sscanf(argv[3], "%d", &x); // transforma o char de argv[3] em int 
        limiar(&I, x); // chama a função limiar 
        write_imgb(argv[2], &I); // o I atualizado pela limiarização é escrito no arquivo 
        free_imgb(&I); // libera a memória
        fclose(pgm); 
        return 0;
    }
    else
    {
        if ((strcmp(argv[1], "inversa") == 0) && (argc == 3)) //verifica se o primeiro argumento de argv é inversa e se argc contou 3 argumentos
        {
            FILE *pgm = fopen(argv[2], "r"); // abre o arquivo e lê o terceiro argumento de argv
            imgb I = read_img(pgm); // atribui o conteúdo do arquivo à struct I
            inversa(&I); // chama a função inversa
            write_imgb(argv[2], &I); // o I atualizado pela função inversa é escrito no arquivo
            free_imgb(&I); // libera a memória
            fclose(pgm);
            return 0;
        }
    }
    if ((strcmp(argv[1], "help") == 0) && (argc == 2)) // chama a função help 
    {
        help();
        return 0;
    }
    printf("Comando Invalido, digite './main help' para ajuda");
    return 0;
}
