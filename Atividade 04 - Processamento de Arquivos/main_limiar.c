/*Nome: Cauan Gabriel de Souza
        Felipe Pereira de Souza
        Layna Dias
        Letícia Dias
        Letícia Yuri Hiratsuka*/

#include <stdio.h>
#include <stdlib.h>
#include "limiar.h"

int main(){
    //Leitura da imagem
    char filename[20];
    char newname[20];
    printf("Insira o arquivo de imagem (com .pgm): \n");

    scanf("%s", filename);
    FILE *fimg = fopen(filename, "r"); //Abre arquivo de imagem
    if (fimg == NULL)
    {
        printf("Não foi possível abrir o arquivo");
    }
    else
    {
        imgb I =  read_img(fimg);

        //Entrada do limiar
        int lim;
        printf("Informe o limiar: \n");
        scanf("%d", &lim);
        limiar(I, lim);

        //Entrada do nome
        printf("Digite o nome da nova imagem (com .pgm):\n");
        scanf("%s",newname);

        //Saída da imagem alterada
        write_imgb(newname, I);

        printf("Nova imagem gerada!\n");

        free_imgb(&I);
    }

}
