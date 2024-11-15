#include <stdio.h>
#include <stdlib.h>
#include "matriz_atv.h"

int main()
{
    printf("MATRIZ DE PONTEIRO DUPLO \n");
    printf("Digite o número de linhas e colunas da matriz: ");
    int lin, col;
    scanf("%d %d", &lin, &col);
    mtz A = new_mtz(lin, col, 0);
    mtz_read(A);

    printf("Matriz multiplicada por um escalar: \n");
    mtz pps_mtz = ppscalar_mtz(A, 2);
    mtz_print(pps_mtz);
    free_mtz(&pps_mtz);

    printf("Digite o número de linhas e colunas da segunda matriz: ");
    scanf("%d %d", &lin, &col);
    mtz B = new_mtz(lin, col, 0);
    mtz_read(B);

    printf("Transposta da segunda matriz: \n");
    mtz trs_mtz = transposta_mtz(B);
    mtz_print(trs_mtz);
    free_mtz(&trs_mtz);

    printf("Soma das duas matrizes: \n");
    mtz sum_mtz = soma_mtz(A, B);
    mtz_print(sum_mtz);
    free_mtz(&sum_mtz);

    printf("Produto das duas matrizes: \n");
    mtz prod_mtz = mul_mtz(A, B);
    mtz_print(prod_mtz);
    free_mtz(&prod_mtz);

    free_mtz(&A);
    free_mtz(&B);

    //--------------------------------------------------------------------------
    //--------------------------------------------------------------------------
    //--------------------------------------------------------------------------

    printf("MATRIZ DE PONTEIRO SIMPLES \n");
    printf("Digite o número de linhas e colunas da matriz: ");
    scanf("%d %d", &lin, &col);
    mtzseq Aseq = new_mtzseq(lin, col, 0);
    mtzseq_read(Aseq);

    printf("Matriz multiplicada por um escalar: \n");
    mtzseq pps_mtzseq = ppscalar_mtzseq(Aseq, 2);
    mtzseq_print(pps_mtzseq);
    free_mtzseq(&pps_mtzseq);

    printf("Digite o número de linhas e colunas da segunda matriz: ");
    scanf("%d %d", &lin, &col);
    mtzseq Bseq = new_mtzseq(lin, col, 0);
    mtzseq_read(Bseq);

    printf("Transposta da segunda matriz: \n");
    mtzseq trs_mtzseq = transposta_mtzseq(Bseq);
    mtzseq_print(trs_mtzseq);
    free_mtzseq(&trs_mtzseq);

    printf("Soma das duas matrizes: \n");
    mtzseq sum_mtzseq = soma_mtzseq(Aseq, Bseq);
    mtzseq_print(sum_mtzseq);
    free_mtzseq(&sum_mtzseq);

    printf("Produto das duas matrizes:\n");
    mtzseq prod_mtzseq = mul_mtzseq(Aseq, Bseq);
    mtzseq_print(prod_mtzseq);
    free_mtzseq(&prod_mtzseq);

    free_mtzseq(&Aseq);
    free_mtzseq(&Bseq);

    return 0;
}