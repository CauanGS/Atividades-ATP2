typedef struct
{
    int h, w; //altura e largura da imagem
    int cinza; //quantidade de tons de cinza
    int *pixel; //Matriz de pixels
} imgb;

imgb read_img(FILE *fimg);
void free_imgb(imgb *I);
void limiar(imgb I, int lim);
void write_imgb(char *filename, imgb I);
