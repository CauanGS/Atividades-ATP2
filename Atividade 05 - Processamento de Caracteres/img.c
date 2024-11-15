#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "img.h"

imgb read_img(FILE *fimg)
 //lê uma imagem em formato PGM de um arquivo e a armazena na estrutura de dados imgb
{   
    //Tipo de imagem. Vamos fixar essa linha como "P2"
    char ver[5]; 
    fscanf(fimg,"%s",ver);
    //Define as dimensões da imagem com base no arquivo
    imgb I;
    fscanf(fimg,"%d ",&I.h);
    fscanf(fimg,"%d ",&I.w);
    fscanf(fimg,"%d ",&I.cinza);

    // Aloca dinamicamente memória para a matriz de pixels da imagem com base na altura e largura
    I.pixel = malloc(I.h*I.w*sizeof(int));

    // Verifica se a alocação de memória deu certo
    if (I.pixel!=NULL)
    {
        for (int i=0; i<I.h; i++)
            for (int j=0; j<I.w; j++)
            {
                fscanf(fimg,"%d ",&I.pixel[i*I.w+j]);
            }
    }
    else
    {
        printf("Falha na alocação de memória.\n");
    }

    //Retorna a estrutura imgb que contém as informações da imagem
    return I;
}

void free_imgb(imgb *I)
/*
    Libera memória em imgb
*/
{
    if (I->pixel!=NULL)
    {
        free(I->pixel);
        I->pixel = NULL;
    }
}

void inversa(imgb *I)
// inverte os valores dos pixels
{
    if (I->pixel!=NULL)
    {
        // loop pra percorrer os pixels
       for(int i = 0; i<I->h;i++) {
        for (int j = 0; j<I->w; j++){
            //Aplica a inversão, substituindo o valor do pixel pela diferença entre o valor máximo de tons de cinza e o valor atual do pixel.
            I->pixel[i*I->w+j] = I->cinza - I->pixel[i*I->w+j];
        }
       }
    }
    else
    {
        printf("Imagem de entrada é NULL.");
    }
}



void limiar(imgb *I, int lim)
/*
    Aplica limiarização a cada pixel.
*/
{
    if (I->pixel!=NULL)
    {
        for (int i=0; i<I->h; i++)
            for (int j=0; j<I->w; j++)
            {
                //Verifica se o valor do pixel é menor que o limiar
                if (I->pixel[i*I->w+j]<lim)
                {
                    // Se for menor que o limiar, define o valor do pixel como 0
                    I->pixel[i*I->w+j] = 0;
                }
                else
                {
                    // Caso contrário, define o valor do pixel como o valor máximo de tons de cinza da imagem
                    I->pixel[i*I->h+j] = I->cinza;
                }
            }
    }
    else
    {
        printf("Imagem de entrada é NULL.");
    }
}

void write_imgb(char *filename, imgb *I)
/*
    Escreve imgb a um arquivo com nome filename.
*/
{
    FILE *fp = fopen(filename,"w");
    if (fp!=NULL)
    {
        if (I->pixel!=NULL)
        {
            //Informações de cabeçalho e seguido das dimensões e do valor máximo de tons de cinza
            fprintf(fp,"P2\n");
            fprintf(fp,"%d %d \n",I->h,I->w);
            fprintf(fp,"%d \n",I->cinza);

            // Dados dos pixels: escreve os valores dos pixels da imagem no arquivo
            for (int i=0; i<I->h; i++)
            {
                for (int j=0; j<I->w; j++) // percorre a matriz
                {
                    fprintf(fp,"%d ",I->pixel[i*I->w+j]); // copia o valor da respectiva posição da matriz no arquivo 
                }
                fprintf(fp,"\n");
            }
            printf("Processo feito com sucesso!\n");
        }
        else
        {
            printf("Imagem de entrada é NULL. \n");
        }
    }
    else
    {
        printf("Não foi possível criar arquivo de saída.\n");
    }
}