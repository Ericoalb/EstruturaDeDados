#include <stdio.h>

typedef struct
{
    char letra[1];
    int peso;    
}matriz;


int main()
{

    matriz tabela[3][12] = {{{'q', 1}, {'w', 6}, {'e', 7}, {'r',6}, {'t', 5}, {'y', 2}, {'u', 3}, {'i', 8}, {'o', 9}, {'p', 4}, {'á', 3}, {'ã', 4}}, {{'a', 2}}};

    printf("%s %d", tabela[0][0].letra, tabela[0][0].peso);
    return 0;
}