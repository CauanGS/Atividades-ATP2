/*
   Membros do Grupo: 
   Rebeca Ruivo, Cauan Souza, Gabriel Sanches, Felipe Pereira
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "matriz_atv.h"

/*------------------------------------------------------------------------------
    Funções da matriz com ponteiro simples
------------------------------------------------------------------------------*/

mtzseq new_mtzseq(int lin, int col, float init)
/*
    Retorna nova matriz mtzseq
*/
{
    mtzseq m;

    if (lin > 0 && col > 0) // verificação se a matriz é válida (possui número positivo não-nulo de linhas e colunas)
    {
        m.lin = lin;
        m.col = col;
        // Alocação única
        m.data = malloc(lin * col * sizeof(float)); // aloca na memória o tamanho da matriz
        if (m.data != NULL) // verificação se os elementos que serão inseridos dentro da matriz são válidos (não NULL) 
        {
            // Inicialização das entradas
            for (int i = 0; i < m.lin * m.col; i++)
            {
                m.data[i] = init; // atribui valor "init" em seu respectivo lugar da matriz
            }
        }
        else
        {
            printf("Memória insuficiente para alocação.\n"); // caso em que o elemento a ser inserido na matriz é inválido (NULL) 
        }
    }
    // Retorna matriz NULL
    else
    {
        m.lin = 0;
        m.col = 0;
        m.data = NULL;
    }

    return m;
}

bool mtzseq_is_null(mtzseq m) // verificação se os elementos da matriz são NULL (true) ou não (false)
{
    if (m.data == NULL)
    {
        return true;
    }
    return false;
}

void free_mtzseq(mtzseq *m) 
{
    if (m->data != NULL)
    {
        free(m->data); // liberação do espaço da memória 
        m->data = NULL; 
    }
}

void mset(mtzseq m, int i, int j, float v)
/*
    Função para definir a entrada [i,j] de m com valor v
*/
{
    if (mtzseq_is_null(m))
    {
        printf("Matriz é NULL");
        return; // Uma forma de encerrar uma função void a qualquer momento
    }

    if (i >= 0 && i < m.lin && j >= 0 && j < m.col) // verificação se 'i' e 'j' representam uma posição possível dentro da matriz
    {
        m.data[i * m.col + j] = v; // atribuição do elemento 'v' em sua respectiva posição na matriz
    }
    else // casos em que 'i' e/ou 'j' não representam linhas e/ou colunas, respectivamente, válidas para a matriz
    {
        printf("Índice inacessível para mset.\n"); 
    }
}

float mget(mtzseq m, int i, int j)
/*
    Função para retornar a entrada [i,j] de m
*/
{
    if (mtzseq_is_null(m)) // verificação se existe uma matriz válida (não NULL)
    {
        printf("Matriz é NULL\n"); 
        return 0;
    }

    if (i >= 0 && i < m.lin && j >= 0 && j < m.col) // verificação se 'i' e 'j' representam, de fato, uma posição possível dentro da matriz
    {
        return m.data[i * m.col + j]; // retorna o elemento presente na posição [i,j]
    }
    else
    {
        printf("Índice inacessível para mget.\n"); // casos em que 'i' e/ou 'j' não representam linhas e/ou colunas, respectivamente, válidas para a matriz
        return 0;
    }
}

/*------------------------------------------------------------------------------

------------------------------------------------------------------------------*/

void mtzseq_read(mtzseq m)
/*
    Pede para o usuário inserir elementos da matriz
*/
{
    if (mtzseq_is_null(m)) // verificação se a matriz existe e é válida (não NULL)
    {
        printf("Matriz é NULL.\n");
        return;
    }

    for (int i = 0; i < m.lin; i++)
        for (int j = 0; j < m.col; j++) // percorrimento da matriz (primeiro 'for' para as linhas e o segundo para as colunas)
        {
            printf("Digite a entrada [%d,%d]: ", i, j); // pede ao usuário que insira um elemento (indicado por 'aux') para cada posição da matriz
            float aux;
            scanf("%f", &aux);
            mset(m, i, j, aux); // define o elemento 'aux' inserido em sua respectiva posição [i,j] na matriz m
        }
}

void mtzseq_print(mtzseq m)
/*
    Imprime elementos da matriz na tela
*/
{
    if (mtzseq_is_null(m))
    {
        printf("Matriz é NULL.\n");
        return;
    }

    for (int i = 0; i < m.lin; i++) // percorrimento das linhas da matriz
    {
        for (int j = 0; j < m.col; j++) // percorrimento das colunas de cada linha 'i' da matriz
        {
            printf("%f ", mget(m, i, j)); // impressão do elemento da respectiva posição [i,j] da matriz m
        }
        printf("\n");
    }
}

mtzseq soma_mtzseq(mtzseq A, mtzseq B)
/*
    Soma de duas matrizes
*/
{
    if (!mtzseq_is_null(A) && !mtzseq_is_null(B))
    {
        if (A.lin == B.lin && A.col == B.col) // verificação se o pré-requisito para soma de matrizes é satisfeito 
        {
            mtzseq res = new_mtzseq(A.lin, A.col, 0); // criação de matriz de mesmo tamanho que A e B e com todos os elementos iguais a 0
            if (mtzseq_is_null(res))
            {
                printf("Memória insuficiente para matriz de resultado.\n");
                return new_mtzseq(0, 0, 0);
            }
            /*Note que não há necessidade de saber o tipo de ordenação desde que
            todas estejam ordenadas da mesma forma.*/
            for (int i = 0; i < A.lin * A.col; i++)
            {
                res.data[i] = A.data[i] + B.data[i]; // define cada elemento da matriz res como o resultado da soma dos elementos da mesma posição de A e B
            }
            return res;
        }
        printf("Matrizes incompatíveis para soma.\n");
        return new_mtzseq(0, 0, 0);
    }
    printf("Matriz de entrada é null.\n");
    return new_mtzseq(0, 0, 0);
}

mtzseq transposta_mtzseq(mtzseq A)
{
    if (!mtzseq_is_null(A))
    {
        mtzseq trans = new_mtzseq(A.col, A.lin, 0); // criação de matriz do tamanho da transposta de A e com todos os elementos iguais a 0
        if (mtzseq_is_null(trans))
        {
            printf("Memória insuficiente para matriz de resultado.\n"); 
            return new_mtzseq(0, 0, 0);
        }
        for (int i = 0; i < A.lin; i++) 
        {
            for (int j = 0; j < A.col; j++)
            {
                float aux = mget(A, i, j);
                mset(trans, j, i, aux); // inversão dos elementos para montagem da transposta ([i,j] vira [j,i])
            }
        }
        return trans;
    }
    printf("Matriz de entrada é null.\n");
    return new_mtzseq(0, 0, 0);
}

mtzseq ppscalar_mtzseq(mtzseq m, int num)
{
    /*
        Multiplicacao de uma matriz por um escalar
    */
    if (!mtzseq_is_null(m))
    {
        // Ver se a matriz entrada eh NULL
        mtzseq res = new_mtzseq(m.lin, m.col, 0);
        if (mtzseq_is_null(res))
        {
            printf("Memória insuficiente para matriz de resultado.\n");
            return new_mtzseq(0, 0, 0);
        }
        // nao se precisa saber ordenacao
        for (int i = 0; i < m.lin * m.col; i++)
        {
            res.data[i] = num * m.data[i]; // multiplicação dos elementos matriz m pelo escalar num 
        }
        return res;
    }
    printf("A matriz inserida eh NULL\n");
    return new_mtzseq(0, 0, 0);
}

mtzseq mul_mtzseq(mtzseq A, mtzseq B)
{
    /*
        Multiplicacao de duas matrizes
    */
    // lembrando que, por conta do struct, podemos referenciar A.col, A.lin, B.col e B.lin
    if (!mtzseq_is_null(A) && !mtzseq_is_null(B))
    {
        // ver se ambas as matrizes entradas nao sao NULL
        if (A.col == B.lin)
        {
            // verifica se as matrizes podem ser multiplicadas
            mtzseq res = new_mtzseq(A.lin, B.col, 0);
            if (mtzseq_is_null(res))
            {
                printf("Memoria insuficiente para a matriz resultado.\n");
                return new_mtzseq(0, 0, 0);
            }
            float aux;
            // loop que percorre linha de A
            for (int i = 0; i < A.lin; i++)
            {
                aux = 0.0;
                // loop que percorre coluna de B
                for (int j = 0; j < B.col; j++)
                {
                    /*loop que percorre coluna de A e linha de B, pode tanto ser A.col ou B.lin pois
                    esses valores sao iguais*/
                    for (int k = 0; k < A.col; k++)
                    {
                        /*usa de uma variavel auxiliar para somar o produto de todos os elementos advindos da linha i de A
                        com todos os elementos da coluna j de B*/
                        aux = aux + (mget(A, i, k) * mget(B, k, j));
                    }
                    mset(res, i, j, aux);
                    aux = 0.0;
                    // atribui valor de aux ao elemento na posicao linha i, coluna j da matriz resultado
                }
                aux = 0.0;
            }
            return res;
        }
        printf("As matrizes sao incompativeis\n");
        return new_mtzseq(0, 0, 0);
    }
    printf("Ao menos uma das matrizes entradas eh NULL\n");
    return new_mtzseq(0, 0, 0);
}

/*------------------------------------------------------------------------------
    Funções da matriz com ponteiro duplo
------------------------------------------------------------------------------*/

mtz new_mtz(int lin, int col, float init)
/*
    Inicializa mtz.
*/
{
    mtz m;

    if (lin > 0 && col > 0)
    {
        m.lin = lin;
        m.col = col;
        // Alocação das linhas: aloca ponteiros simples
        m.data = malloc(lin * sizeof(float *));
        if (m.data != NULL)
        {
            // Alocação das colunas: aloca variável comum
            for (int i = 0; i < lin; i++)
            {
                m.data[i] = malloc(col * sizeof(float));
                if (m.data[i] != NULL)
                    // Inicialização das entradas
                    for (int j = 0; j < col; j++)
                    {
                        m.data[i][j] = init;
                    }
                else
                {
                    printf("Memória insuficiente para alocação.");
                }
            }
        }
        else
        {
            printf("Memória insuficiente para alocação.");
        }
    }
    else
    {
        m.lin = 0;
        m.col = 0;
        m.data = NULL;
    }

    return m;
}

bool mtz_is_null(mtz m)
/*
    Checa se alguma das alocações de mtz falhou.
*/
{
    if (m.data == NULL)
    {
        return true;
    }
    for (int i = 0; i < m.lin; i++)
        if (m.data[i] == NULL)
        {
            return true;
        }
    return false;
}

void free_mtz(mtz *m)
/*
    Libera memória de mtz. Para cada malloc, é feito um free.
*/
{
    if (m->data != NULL)
    {
        for (int i = 0; i < m->lin; i++)
        {
            if (m->data[i] != NULL)
            {
                free(m->data[i]);
            }
        }
        free(m->data);
        m->data = NULL;
    }
}

void mtz_read(mtz m)
/*
    Pede para usuário inserir elementos na matriz.
*/
{
    if (mtz_is_null(m))
    {
        printf("Matriz é NULL.");
        return;
    }

    for (int i = 0; i < m.lin; i++)
        for (int j = 0; j < m.col; j++)
        {
            printf("Digite a entrada [%d,%d]: ", i, j);
            scanf("%f", &m.data[i][j]);
        }
}

void mtz_print(mtz m)
/*
    Imprime na tela os elementos da matriz.
*/
{
    if (mtz_is_null(m))
    {
        printf("Matriz é NULL.\n");
        return;
    }

    for (int i = 0; i < m.lin; i++)
    {
        for (int j = 0; j < m.col; j++)
        {
            printf("%f ", m.data[i][j]);
        }
        printf("\n");
    }
}

mtz soma_mtz(mtz A, mtz B)
/*
    Soma de duas matrizes
*/
{
    if (!mtz_is_null(A) && !mtz_is_null(B)) // verificação se ambas as matrizes A e B são ou não NULL
    {
        if (A.lin == B.lin && A.col == B.col) // verificação se o princípio para soma de matrizes é satisfeito 
        {
            mtz res = new_mtz(A.lin, A.col, 0); // criação de matriz de mesmo tamanho que A e B e com todos os elementos iguais a 0
            if (mtz_is_null(res)) // verificação se a matriz res é NULL
            {
                printf("Memória insuficiente para matriz de resultado.\n");
                return new_mtz(0, 0, 0);
            }
            for (int i = 0; i < A.lin; i++)
                for (int j = 0; j < A.col; j++) // percorrimento da mesma posição [i,j] nas matrizes A, B e res
                {
                    res.data[i][j] = A.data[i][j] + B.data[i][j]; // atribuição dos elementos de 'res' como sendo a soma dos elementos de mesma posição de A e B
                }
            return res;
        }
        printf("Matrizes incompatíveis para soma.\n");
        return new_mtz(0, 0, 0);
    }
    printf("Matriz de entrada é null.\n");
    return new_mtz(0, 0, 0);
}

/*
    Atividade Matriz Transposta
*/

mtz transposta_mtz(mtz A)
/*
    Retorna a matriz transposta
*/
{
    if (!mtz_is_null(A))
    // Testa se a matriz é NULL
    {
        // Define uma matriz mxn onde m e o numero de colunas da matriz original
        // e n e o numero de linhas da matriz original
        mtz trans = new_mtz(A.col, A.lin, 0); // cria uma matriz com o tamanho da transposta de A e todos os elementos iguais a 0
        if (mtz_is_null(trans))
        {
            printf("Memória insuficiente para matriz de resultado.\n"); // verifica se a matriz resultado é NULL
            return new_mtz(0, 0, 0); 
        }
        for (int i = 0; i < A.col; i++)
        {
            for (int j = 0; j < A.lin; j++) 
            {
                trans.data[i][j] = A.data[j][i]; // insere na matriz resultado os valores da transposta de A (os elementos [i,j] de A se tornam [j,i] da matriz resultado)
            }
        }
        return trans;
    }
    printf("Matriz de entrada é null.\n");
    return new_mtz(0, 0, 0);
}

mtz ppscalar_mtz(mtz A, int num)
// multiplica a matriz por um escalar 
{
    if (mtz_is_null(A)) // verifica se a matriz é NULL
    {
        printf("A matriz de entrada é NULL.\n");
        return new_mtz(0, 0, 0);
    }
    mtz res = new_mtz(A.lin, A.col, 0); // cria matriz com o mesmo tamanho de A e todos os elementos iguais a 0 
    if (mtz_is_null(res))
    {
        printf("Memória insuficiente para matriz de resultado.\n");
        return new_mtz(0, 0, 0);
    }
    for (int i = 0; i < A.lin; i++)
    {
        for (int j = 0; j < A.col; j++)
        {
            res.data[i][j] = num * A.data[i][j]; // preenche a matriz resultado com o produto dos elementos respectivos de A (mesma posição) com o escalar
        }
    }
    return res;
}

mtz mul_mtz(mtz A, mtz B)
{
    if (!mtz_is_null(A) && !mtz_is_null(B)) // verifica se as matrizes A e B são NULL
    {
        if (A.col == B.lin) // verifica se as matrizes são elegíveis para multiplicação (ou seja, se o número de colunas da primeira é igual ao de linhas da segunda)
        {
            mtz res = new_mtz(A.lin, B.col, 0); // cria matriz com número de linhas igual ao de A, colunas igual ao de B e todos os elementos iguais a 0
            if (mtz_is_null(res))
            {
                printf("Memoria insuficiente para a matriz resultado.\n");
                return new_mtz(0, 0, 0);
            }
            float aux = 0.0; 
            for (int i = 0; i < A.lin; i++) // percorrimento das linhas da matriz A e da matriz res
            {
                aux = 0.0;
                for (int j = 0; j < B.col; j++) // percorrimento das colunas da matriz B e da matriz res
                {
                    for (int k = 0; k < A.col; k++) // percorrimento das colunas de A e linhas de B (que são iguais em número)
                    {
                        aux = aux + (A.data[i][k] * B.data[k][j]); 
                        // a variável auxiliar assume o resultado da operação realizada em cada linha de A e coluna de B e, posteriormente, insere na matriz 
                        //resultado em sua respectiva posição (esta, referente ao número da linha de A e coluna de B em res) 
                    }
                    res.data[i][j] = aux;
                }
            }
            return res;
        }
        printf("As matrizes sao incompativeis\n");
        return new_mtz(0, 0, 0);
    }
    printf("Ao menos uma das matrizes entradas eh NULL\n");
    return new_mtz(0, 0, 0);
}