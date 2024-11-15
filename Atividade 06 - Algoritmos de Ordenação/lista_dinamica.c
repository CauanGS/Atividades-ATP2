#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "lista_dinamica.h"

dlist new_list()
// função para criar nova lista
{
    dlist L = malloc(sizeof(dList)); // alocação de memória
    L->last = -1; 
    L->first = NULL; // vetor existirá (terá espaço alocado) mas nenhuum valor atribuído 
    return L;
}

void del_list(dlist L)
// função para deletar uma lista
{
    if (L != NULL) // checagem se há valor atribuído a L
    {
        item current = L->first;
        while (current != NULL)
        {
            // cuidado para não perder o próximo elemento
            L->first = current->next;
            L->last--;
            free(current);
            // Atualiza current
            current = L->first;
        }
        free(L);
    }
}

int size(dlist L)
// função para contar os elementos da lista, retornando seu tamanho
{
    if (L != NULL) // checagem se, de fato, existe elemento a ser contado
        return L->last + 1;
    return 0;
}

bool empty(dlist L)
// função para saber se a lista está vazia (0) ou não (1)
{
    return size(L) == 0;
}

bool full(dlist L) 
// função que define o tamanho da lista, no máximo, 100 
{
    return size(L) == MAX_LIST_SIZE;
}

bool print_list(dlist L)
/*
    Imprime elementos da lista.
*/
{
    if (empty(L))
    {
        printf("Lista vazia.");
        return false;
    }

    // Você pode iterar até que a variável ponteiro não seja NULL
    for (item i = L->first; i != NULL; i = i->next)
        printf("%d ", i->v);
    return true;
}

bool print_id(dlist L)
/*
    Imprime o id dos elementos da lista (para teste).
*/
{
    if (empty(L))
    {
        printf("Lista vazia.");
        return false;
    }

    // Você pode iterar até que a variável ponteiro não seja NULL
    for (item i = L->first; i != NULL; i = i->next)
        printf("%d ", i->id);
    return true;
}

bool search(dlist L, int key, int *pos)
/*
    Busca por elemento a partir de uma chave. Retorna inderetamente através da
    variável pos.
*/
{
    if (empty(L))
    {
        printf("Lista vazia.");
        return false;
    }

    item aux = L->first;
    while (aux != NULL)
    {
        *pos += 1;
        if (aux->v == key)
        {
            return true;
        }
        aux = aux->next;
    }
    *pos = -1;
    return false;
}

bool search_id(dlist L, int idn, item *pos)
/*
    Busca por elemento a partir do Id inserido. Retorna um ponteiro para a posiçao.
    O id depende unicamente da posiçao do elemento e nao seu valor.
*/
{
    if (empty(L))
    {
        printf("Lista vazia.");
        return false;
    }

    if (idn > L->last)
    {
        printf("Id escolhido maior que existentes.");
        return false;
    }

    if (idn == 0)
    { // caso trivial, Id = 0
        *pos = L->first;
        return true;
    }

    item aux = L->first;

    while (aux->next != NULL)
    {
        if (aux->next->id == idn)
        {
            *pos = aux->next;
            return true;
        }
        aux = aux->next;
    }
    pos = NULL;
    return false;
}

bool insertAt(dlist L, int *v, int pos)
/*
    Inserção de item em uma posição especificada.
    Note que a implementação aqui demanda movimentar ponteiros ao invés de ints
*/
{
    if (full(L))
    {
        printf("Lista está cheia.");
        return false;
    }
    if (pos < 0 || pos > L->last + 1)
    {
        printf("Posição inválida");
        return false;
    }
    item in_item = malloc(sizeof(struct Item));
    item i = L->first; // Ponteiro para primeiro elemento
    in_item->v = *v;
    in_item->next = NULL;
    in_item->id = -1;
    int k = 0;
    L->last++;
    if (pos == 0) // Inserção na primeira posição é caso particular
    {
        in_item->next = L->first;
        L->first = in_item;
        in_item->id = 0;
        i = L->first;
    }
    else
    {
        while (k < pos - 1) // itera até alcançar lugar a ser inserido
        {
            k++;
            i = i->next;
        }
        in_item->next = i->next; // Insere in_item atrás de i->next
        in_item->id = k + 1;     // Torna o Id de in_item equivalente a K, o contador de posiçao
        i->next = in_item;       // Inserte in_item à frente de i;
        k++;
    }
    if (k != L->last)
    {
        /*
        Agora é necessário alterar o ID de todos os elementos seguintes
        */

        while (k < L->last)
        {
            in_item = in_item->next;
            in_item->id = k + 1;
            k++;
        }
    }

    return true;
}

bool removeAtPos(dlist L, int pos)
/*
    Remove item em uma posição especificada, de certa forma remove pelo ID.
*/
{
    if (empty(L))
    {
        printf("Lista vazia.");
        return false;
    }
    if (pos < 0 || pos > L->last + 1)
    {
        printf("Posição inválida");
        return false;
    }

    item aux = NULL;
    item prev = NULL; // armazena anterior a aux;
    L->last--;
    int k = 0;    // variável de contagem
    if (pos == 0) // Novamente, caso particular
    {
        aux = L->first->next;
        free(L->first);
        L->first = aux;
        aux->id = 0;
        prev = L->first; // colocar prev como first sera util para mudar o id de itens seguintes
    }
    if (pos != 0)
    {
        aux = L->first; // aux será utilizada pra iterar sobre a lista
        while (k < pos)
        {
            prev = aux;
            k++;
            aux = aux->next;
        }
        prev->next = aux->next;
        prev->id = k - 1;
        free(aux);
    }
    while (k < L->last + 1)
    { // lembrando, L->last comeca em 0
        prev = prev->next;
        prev->id--;
        k++;
    }

    return true;
}

bool removeByKey(dlist L, int key)
// função para remover um item da lista pela chave (v)
{
    int pos = -1;
    if (search(L, key, &pos))
    {
        printf("%d", pos);
        removeAtPos(L, pos);
        return true;
    }
    printf("Chave não encontrada.");
    return false;
}

bool to_file(char *filename, dlist L)
/*
    Escreve conteúdo de L para um arquivo.
*/
{
    if (empty(L))
    {
        printf("Lista vazia.");
        return false;
    }

    FILE *fp = fopen(filename, "wb");
    if (fp == NULL)
    {
        printf("Não foi possível criar arquivo.");
        fclose(fp);
        return false;
    }

    item aux = L->first;
    while (aux != NULL)
    {
        fwrite(aux, sizeof(struct Item), 1, fp); // escrevendo o conteúdo de L no arquivo 
        aux = aux->next; // percorre o próximo elemento da lista 
    }
    fclose(fp);
    return true;
}

bool from_file(char *filename, dlist L)
/*
    Lê uma L de um arquivo.
*/
{
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) // caso em que o arquivo é NULL
    {
        printf("Não foi possível abrir arquivo.");
        fclose(fp);
        return false;
    }

    item aux = (item)malloc(sizeof(struct Item)); // alocação de memória
    item last_item = NULL;
    while (fread(aux, sizeof(struct Item), 1, fp)) // lê o arquivo enquanto fread é diferente de eof
    {
        L->last++; // atualiza a posição do último percorrido da lista
        if (L->first == NULL) // checagem se a lista acabou de ser percorrida
        {
            L->first = malloc(sizeof(struct Item));
            last_item = L->first;
        }
        else
        {
            last_item->next = malloc(sizeof(struct Item));
            last_item = last_item->next;
        }
        last_item->v = aux->v;
        last_item->id = aux->id;
        // atualiza aux para o último elemento da lista lido e sua respectiva posição 
        last_item->next = NULL;
        // encerra a lista deixando o próximo elemento como NULL
    }
    fclose(fp);
    return true;
}

bool insertion_sort_lista(dlist L)
// função que ordena os elementos de maneira crescente
{
    if (empty(L))
    {
        printf("Lista vazia");
        return false;
    }
    item current = L->first; // current eh o pivô movel, tudo na esquerda e a posição dele é alterável em uma dada iteração
    current = current->next;
    item prev = L->first; // prev eh um elemento anterior a current, nao necessariamente um anterior

    for (int i = 1; i <= L->last; i++)
    {
        int aux_v = current->v; // aux_v esta relacionado pega o valor de current, o atual, para nao perde-lo
        int j = i - 1;
        while (j >= 0 && prev->v > aux_v)
        {
            prev->next->v = prev->v; // o valor do elemento seguinte a j (ou seja, na posicao i) recebe o valor de prev

            j--;
            if (j != -1)
            {
                search_id(L, j, &prev);
                /*
                como j eh a posiçao de prev e teve j--, search_id retorna em prev o item
                anterior ao antigo prev. Nao ocorre se j=0 para evitar acesso indevido
                */
            }
        }
        if (j == -1)
        {                    // cuidado especial para j sendo 0 visto que o prev nao reduziu de posicao nesse caso
            prev->v = aux_v; // insere o valor dos auxs para a posicao j, aquela que passou seu valor ao seguinte
        }
        else
        {
            prev->next->v = aux_v;
        }
        prev = current;
        current = current->next;
    }
    print_list(L);
    return true;
}

void troca(dlist L, item n, item j)
// função que troca o elemento j pelo n e vice-versa dento da lista L
{
    int aux_v = n->v;

    n->v = j->v;

    j->v = aux_v;
}

int separa(dlist L, int low, int high)
/* 
função que recebe uma lista de números desorganizados e divide essa lista em duas partes: 
uma parte com números menores ou iguais a um valor especial chamado "pivô" e outra parte com números maiores que o pivô.
*/
{
    item pivo = L->first;  // utilizado para o high
    item aux_j = L->first; // utilizado para j
    item aux_i = L->first; // utilizado para i
    search_id(L, high, &pivo);
    search_id(L, low, &aux_j);
    int i = low;
    search_id(L, low, &aux_i);
    for (int j = low; j < high; j++)
    {
        if (aux_j->v <= pivo->v) // Testa qual valor é menor
        {
            troca(L, aux_i, aux_j); // Troca os valores
            i++;
            aux_i = aux_i->next;
        }
        aux_j = aux_j->next;
    }
    troca(L, aux_i, pivo);
    return i;
}

void quick_sort_recursao(dlist L, int low, int high)
/* 
função que divide a lista em partes menores com base em um elemento de referência (pivô) e, em seguida, 
ordena essas partes separadamente. O processo é repetido até que toda a lista esteja ordenada.
*/
{
    if (empty(L))
    {
        printf("Lista vazia");
    }
    if (low < high)
    {
        int pivo = separa(L, low, high);
        quick_sort_recursao(L, low, pivo - 1);
        quick_sort_recursao(L, pivo + 1, high);
    }
}

bool quicksort(dlist L)
/* 
chama a função de ordenação rápida para ordenar a lista L e, 
após a ordenação, a lista é mostrada com os elementos organizados.
*/
{
    print_list(L);
    int high = 0;
    for (item count = L->first; count->next != NULL; high++)
    {
        count = count->next;
    }
    // for para atribuir a high o id da maior posicao
    quick_sort_recursao(L, 0, high);
    return true;
}