#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

typedef struct   // Estrutura para receber a letra + o peso/valor;
{
    char letra[3]; // char de tamanho 3, pois o caractere com acento ocupa 3 bytes
    int peso; 

}matriz;

int CalcularNome(matriz tabela[3][12], char nome[50]);

int main()
{
    
    setlocale(LC_ALL, "pt_BR.UTF-8"); // Garantindo que não haverá bugs com os acentos
    char nome[50];

    // Matriz de estuturas para armazenar em cada posição a "estrutura matriz" com  
    // sua rescptiva letra e peso/valor
    matriz tabela[3][12] = {{{"q", 1}, {"w", 6}, {"e", 7}, {"r", 6}, {"t", 5}, {"y", 2}, {"u", 3}, {"i", 8}, {"o", 9}, {"p", 4}, {"á", 3}, {"ã", 4}}, 
                            {{"a", 2}, {"s", 5}, {"d", 8}, {"f", 7}, {"g", 4}, {"h", 1}, {"j", 4}, {"k", 7}, {"l", 8}, {"ç", 5}, {"é", 2}, {"í", 3}},
                            {{"z", 3}, {"x", 4}, {"c", 9}, {"v", 8}, {"b", 3}, {"n", 2}, {"m", 5}, {"ó", 6}, {"õ", 7}, {"ô", 6}, {"â", 1}, {"ê", 2}}};



    fgets(nome, 50, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int retorno = CalcularNome(tabela, nome);

    printf("%d\n", retorno);
    
    return 0;
}

int CalcularNome(matriz tabela[3][12], char nome[50])
{
    int i = 0;
    int soma = 0;
    
    while(nome[i] != '\0')
    {
        int valido = 0;

        for(int j = 0; j < 3; j++) // Linha da matriz
        {
            for(int k = 0; k < 12; k++) // Coluna da Matriz
            {
                // Inicializando uma variável temporária de tamanho 3, para não bugar com acentos,
                // Ela recebe o caracter do nome[i] e o '\0'
                // Criei essa variável por que o C não permite comparar um caracter: nome[i], com uma string, tabela[j][k].letra
                
                char temp[3] = {nome[i], '\0'};   // temp[0] = nome[i];
                                                 //  temp[1] = '\0';
                
                if( *temp == *tabela[j][k].letra) // if com strings compara os endereços, então precisamos "desreferenciar com * "
                                                 // Desse modo, buscamos o valor que está nos endereços, que são os caracteres
                {
                    soma += tabela[j][k].peso;  // Somando os pesos das letras
                    valido = 1;                 
                    break;    // Como só comparamos uma letra por vez, não precisamos percorer toda a matriz
                }
            }

            if(valido) break; // para não percorrer toda a matriz
        }

        i++;
    }

    return soma;
}


