#include <stdio.h>
#include <stdlib.h>
#include "limiar.h"


imgb read_img(FILE *fimg)
/*
    Lê imagem de um arquivo.
*/
{
    imgb I;
    //Tipo de imagem. Vamos fixar essa linha como "P2"
    if(fimg != NULL){
        char ver[5];
        fscanf(fimg,"%s",ver);

        //Dimensões da imagem
        fscanf(fimg,"%d ",&I.h);
        fscanf(fimg,"%d ",&I.w);
        fscanf(fimg,"%d ",&I.cinza);

        //Leitura dos dados da matriz
        I.pixel = malloc(I.h*I.w*sizeof(int));
        if (I.pixel!=NULL)
        {
            for (int i=0; i<I.h; i++)
                for(int j=0; j<I.w; j++)
                {
                    fscanf(fimg,"%d ",&I.pixel[i*I.w+j]);
                }
        }
        else
        {
            printf("Falha na alocação de memória.\n");
        }
    }
    else
    {
        printf("Não foi possível abrir o arquivo. \n");
        I.h = 0;
        I.w = 0;
        I.cinza = 0;
        I.pixel = NULL;
    }
    fclose(fimg);//Fecha arquivo de imagem
    return I;

}

//Libera o espaço na memória
void free_imgb(imgb *I)
{
    if (I->pixel != NULL)
    {
        free(I->pixel);
        I->pixel = NULL;
    }
}

//Altera os dados da matriz
void limiar(imgb I, int lim)
{
    for (int i = 0; i < I.h; i++)
    {
        for (int j = 0; j < I.w; j++)
        {
            if (I.pixel[i*I.w + j] < lim)
            {
                I.pixel[i*I.w + j] = 0;
            }
            else
            {
                I.pixel[i*I.w + j] = I.cinza;
            }
        }
    }
}

//Escreve imagem do arquivo
void write_imgb(char *filename, imgb I)
{
    FILE *fimg = fopen(filename, "w"); //Abre arquivo da imagem alterada

    fprintf(fimg,"P2 \n");

    //Dados da nova imagem
    fprintf(fimg,"%d ",I.h);
    fprintf(fimg,"%d \n",I.w);
    fprintf(fimg,"%d \n",I.cinza);

    for (int i=0; i<I.h; i++)
    {
        for(int j=0; j<I.w; j++)
        {
            fprintf(fimg,"%d  ",I.pixel[i*I.w+j]);
        }
    }
    fclose(fimg);//Fecha arquivo de imagem
}
