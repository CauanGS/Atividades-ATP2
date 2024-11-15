/*
Grupo: Cauan Souza, Rebeca Ruivo, Felipe Pereira de Souza, Gabriel Sanches Pinto
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "lista_dinamica.h"

void helper()
{
    printf("Gereciador de listas GERENTE\n");
    printf("Funções que começam com o nome do arquivo realizam abertura do mesmo e em seguida realizam a operação descrita.\n");
    printf(" [nome.bin cria v] Cria arquivo com uma lista e inicializa primeiro item com valor v.\n");
    printf(" [nome.bin insereEm pos v] Insere valor v na posição pos. \n");
    printf(" [nome.bin removeEm pos] Remove elemento na posição pos. \n");
    printf(" [nome.bin removeValor v] Remove elemento com valor v.\n");
    printf(" [nome.bin print] Imprime elementos da lista na tela. \n");
    printf(" [nome.bin ordena_insert] ordena a lista em ordem crescente por meio do insertion sort. \n");
    printf(" [nome.bin ordena_quick] ordena a lista em ordem crescente por meio do quick sort. \n");
    printf(" [nome.bin print_id] imprime os ids dos elementos (para teste). \n");
}

void finish(bool check, char *filename, dlist L)
{
    if (check)
    {
        bool aux = to_file(filename, L);
        if (aux)
        {
            printf("\n Operação realizada com sucesso. \n");
        }
        else
        {
            printf("\n Falha ao salvar arquivo. \n");
        }
        return;
    }
    printf("\n Operação falhou. \n");
}

void cmd_invalido()
{
    printf("\n Comando inválido. Digite help para ajuda. \n");
}

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        if (strcmp(argv[1], "help") == 0)
        {
            helper();
            return 0;
        }
        cmd_invalido();
        return 0;
    }

    if (argc > 2 && argc < 6)
    {
        dlist L = new_list();
        bool check;

        // Função de criação de lista
        if (strcmp(argv[2], "cria") == 0 && argc == 4)
        {
            int v;
            sscanf(argv[3], "%d", &v);
            check = insertAt(L, &v, 0);
            finish(check, argv[1], L);
            del_list(L);
            return 0;
        }

        // Funções de manipulação
        check = from_file(argv[1], L);
        if (check)
        {
            check = false; // reinicia variável de checagem
            if (strcmp(argv[2], "insereEm") == 0 && argc == 5)
            {
                int pos, v;
                sscanf(argv[3], "%d", &pos);
                sscanf(argv[4], "%d", &v);
                check = insertAt(L, &v, pos);
            }
            if (strcmp(argv[2], "removeEm") == 0 && argc == 4)
            {
                int pos;
                sscanf(argv[3], "%d", &pos);
                check = removeAtPos(L, pos);
            }
            if (strcmp(argv[2], "removeValor") == 0 && argc == 4)
            {
                int v;
                sscanf(argv[3], "%d", &v);
                check = removeByKey(L, v);
            }
            if (strcmp(argv[2], "search") == 0 && argc == 4)
            {
                int v;
                sscanf(argv[3], "%d", &v);
                int pos = 0;
                check = search(L, v, &pos);
                if (check)
                {
                    printf("Valor %d está na posição %d.", v, pos);
                }
            }
            if (strcmp(argv[2], "print") == 0 && argc == 3)
            {
                check = print_list(L);
            }
            if (strcmp(argv[2], "print_id") == 0 && argc == 3)
            {
                check = print_id(L);
            }
            if (strcmp(argv[2], "ordena_insert") == 0 && argc == 3)
            {
                check = insertion_sort_lista(L);
            }
            if (strcmp(argv[2], "ordena_quick") == 0 && argc == 3)
            {
                check = quicksort(L);
            }
        }
        finish(check, argv[1], L);
        del_list(L);
        return 0;
    }
    cmd_invalido();
    return 0;
}