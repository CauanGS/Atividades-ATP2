#define MAX_LIST_SIZE 100

struct Item
{

    int v;             // valor armazenado
    int id;            // valor que indica sua posiçao
    struct Item *next; // ponteiro para objeto de mesmo tipo
};

// Vamos novamente trabalhar só com ponteiros
typedef struct Item *item;

typedef struct
{
    item first; // primeiro elemento da lista
    int last;
} dList;

typedef dList *dlist;

dlist new_list();
void del_list(dlist L);
bool print_list(dlist L);
bool print_id(dlist L);
bool search(dlist L, int key, int *pos);
bool search_id(dlist L, int idn, item *pos);
bool insertAt(dlist L, int *item, int pos);
bool removeAtPos(dlist L, int pos);
bool removeByKey(dlist L, int key);
bool to_file(char *filename, dlist L);
bool from_file(char *filename, dlist L);
bool insertion_sort_lista(dlist L);
void troca(dlist L, item n, item j);
int separa(dlist L, int low, int high);
bool quicksort(dlist L);
void quick_sort_recursao(dlist L, int low, int high);