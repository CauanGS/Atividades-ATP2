// Matriz armazenada em ponteiro simples
typedef struct
{
    int lin, col; // linhas e colunas
    float *data;  // dados
} mtzseq;

// Matriz armazenada em ponteiro duplo
typedef struct
{
    int lin, col; // linhas e colunas
    float **data; // dados
} mtz;

mtzseq new_mtzseq(int lin, int col, float init);
mtz new_mtz(int lin, int col, float init);
void free_mtzseq(mtzseq *m);
void free_mtz(mtz *m);
void mset(mtzseq m, int i, int j, float v);
float mget(mtzseq m, int i, int j);
void mtzseq_read(mtzseq m);
void mtz_read(mtz m);
void mtzseq_print(mtzseq m);
void mtz_print(mtz m);
mtzseq soma_mtzseq(mtzseq A, mtzseq B);
mtz soma_mtz(mtz A, mtz B);

mtzseq transposta_mtzseq(mtzseq A);
mtz transposta_mtz(mtz A);

mtzseq ppscalar_mtzseq(mtzseq m, int num);
mtz ppscalar_mtz(mtz A, int num);
mtzseq mul_mtzseq(mtzseq A, mtzseq B);
mtz mul_mtz(mtz A, mtz B);

