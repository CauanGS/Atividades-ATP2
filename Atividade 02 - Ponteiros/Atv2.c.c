/*
    Atividade 2 - Ponteiros
    Membros do grupo: Gabriel Sanches, Felipe Pereira de Souza, Rebeca Ruivo, Cauan Souza
*/
#include <stdio.h>

/*---------------------------------------------------
    Funcoes para teste do algoritmo
----------------------------------------------------*/
float func1(int i)
{
    float fun = 1.0 / ((4.0 * i + 1.0) * (4.0 * i + 3.0));
    return fun;
}

float func2(int i)
{
    float fun = 1.0 / ((i + 1.0) * (i + 1.0));
    return fun;
}

float func3(int i)
{
    float fun = 1.0 / ((2.0 * i + 1.0) * (2.0 * i + 1.0));
    return fun;
}

float somatorio(int N, float (*qual)(int))
/*
    Recebe o termo final 'N' e a função escolhida atraves do ponteiro 'qual'
    indicando qual entre func1, func2 e func3 serao utilizadas para o somatorio
*/
{
    float soma = 0.0;
    // Realiza a soma utilizando 'i' como variavel e itereando-o ate o termo final 'N'
    for (int i = 0; i <= N; i++)
    {
        soma = soma + qual(i);
    }
    return soma;
}

int main()
{
    int N, opc;
    N = -1;
    opc = -1;

    while (N <= -1)
    /*
        Entra no loop com o valor default N = -1, e o mantem ate que o
        usuario insira um valor valido 'N' (positivo ou 0)
    */
    {
        printf("\nInsira o valor maximo de N desejado: \n");
        scanf("%d", &N);
        if (N <= -1)
        {
            printf("O numero inserido eh invalido ( o numero deve ser inteiro positivo)\n");
        }
    }

    while (opc < 1 || opc > 3)
    // Repete o loop ate que o usuario escolha uma opcao valida
    {
        printf("\nDigite 1, 2 ou 3 para escolher entre as funcoes: \n1) 1/(4n+1)(4n+3) \n2) 1/(n+1)^2 \n3) 1/(2n+1)^2\n");
        scanf("%d", &opc);

        // Verifica se a opcao selecionada e valida
        if (opc < 1 || opc > 3)
        {
            printf("Entrada invalida \n");
        }
    }

    /*
        Define qual funcao sera utilizada com base nas opcoes disponiveis
    */
    if (opc == 1)
    {
        printf("O somatorio ate o valor desejado eh: %f\n", somatorio(N, func1));
    }
    else if (opc == 2)
    {
        printf("O somatorio ate o valor desejado eh: %f\n", somatorio(N, func2));
    }
    else
    {
        printf("O somatorio ate o valor desejado eh: %f\n", somatorio(N, func3));
    }

    return 0;
}