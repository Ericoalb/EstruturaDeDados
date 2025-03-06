#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

typedef struct   // Estrutura para receber a letra + o peso/valor;
{
    char letra[3]; // char de tamanho 3, pois o caractere com acento ocupa 3 bytes
    int peso; 

}matriz;

typedef struct
{
    char nome[50];
    char codigo[8];
    int carga_horaria;
    int dias;
    char turno;
    int hora;

}disciplina;



void LowerCase(char nome[50]);
void SemPrepo(char nome[50]);
int CalcularNome(matriz tabela[3][12], char nome[50], int soma_nome[4]);
void MostrasGradeCompleta(disciplina quadro[8][5]);

int main()
{
    
    setlocale(LC_ALL, "pt_BR.UTF-8"); // Garantindo que não haverá bugs com os acentos
    char nome[50];

    // Matriz de estuturas para armazenar em cada posição a "estrutura matriz" com  
    // sua rescptiva letra e peso/valor
    matriz tabela[3][12] = {{{"q", 1}, {"w", 6}, {"e", 7}, {"r", 6}, {"t", 5}, {"y", 2}, {"u", 3}, {"i", 8}, {"o", 9}, {"p", 4}, {"á", 3}, {"ã", 4}}, 
                            {{"a", 2}, {"s", 5}, {"d", 8}, {"f", 7}, {"g", 4}, {"h", 1}, {"j", 4}, {"k", 7}, {"l", 8}, {"ç", 5}, {"é", 2}, {"í", 3}},
                            {{"z", 3}, {"x", 4}, {"c", 9}, {"v", 8}, {"b", 3}, {"n", 2}, {"m", 5}, {"ó", 6}, {"õ", 7}, {"ô", 6}, {"â", 1}, {"ê", 2}}};



    disciplina quadro[8][5] = {{{"PROGRAMAÇAO 1", "COMP359", 72, 6, 'M', 56}}};

    

    fgets(nome, 50, stdin);
    nome[strcspn(nome, "\n")] = '\0';
    LowerCase(nome);
    SemPrepo(nome);
    CalcularNome(tabela, nome, soma_nome);
    
    return 0;
}


int CalcularNome(matriz tabela[3][12], char nome[50], int soma_nome[4])
{
    int i = 0; // indice para percorrer a string do "nome"
    int l = 0; // indice para armazenar a soma dos nomes separados 
               // exp "(erico = 18) soma_nome[l] = 18" "(almeida = 29) soma_nome[l] = 29"
    int soma = 0;

    while(nome[i] != '\0')
    {
        int valido = 0;

        for(int j = 0; j < 3; j++) // Linha da matriz
        {
            for(int k = 0; k < 12; k++) // Coluna da Matriz
            {
                // Inicializando a variável temp de tamanho 3, para não bugar com acentos,
                // Ela recebe o caracter do (nome[i]) e o '\0'
                // Criei essa variável por que o C não permite comparar o caracter que esta dentro do (nome[i]), com a string (tabela[j][k].letra)
                
                char temp[3] = {nome[i], '\0'};   // temp[0] = nome[i];
                                                 //  temp[1] = '\0';
                
                if( *temp == *tabela[j][k].letra) // if com strings compara os endereços, então precisamos "desreferenciar com * "
                                                 // Desse modo, buscamos o valor que está nos endereços, que são os caracteres
                {
                    soma += tabela[j][k].peso;  // Somando os pesos das letras
                    valido = 1;                 
                    break;    // Como só comparamos uma letra por vez, não precisamos percorer todas as colunas da matriz
                }
            }

            if(valido) break; // para não percorrer todas as linhas matriz
        }

        if (nome[i] == ' ' && i != 0)
        {
            soma_nome[l] = soma;
            soma = 0;
            l++;
        }

        i++;
    }

    soma_nome[l] = soma;

    return soma;
}

void SemPrepo(char nome[50])
{
    // Função para retirar as preposições dos nomes
    // "de", "dos"... 
    int i = 0;

    while(nome[i] != '\0')
    {
        if(nome[i] == ' ')
        {

            if (nome[i + 4] == ' ')
            {
                nome[i + 1] = '*';
                nome[i + 2] = '*';
                nome[i + 3] = '*';
                nome[i + 4] = '*'; 
            }
    
            else if (nome[i + 3] == ' ')
            {
                nome[i + 1] = '*';
                nome[i + 2] = '*';
                nome[i + 3] = '*';
            }
        }

        i++;

    }

    return;
}

void LowerCase(char nome[50])
{

    // de maiusculo para minusculo, somamos mais 32;

    int i = 0;

    while(nome[i] != '\0')
    {
        if (nome[i] >= 'A' && nome[i] <= 'Z')
        {
            nome[i] += 32;
        }

        i++;
    }

    return;
}

void MostrarGradeCompleta(disciplina quadro[8][5])
{
    printf("___________________________________________________________________\n");
    printf("|        |                                                         |\n");
    printf("|SEMESTRE|                      DISCIPLINAS                        |\n");
    printf("|________|_________________________________________________________|\n");
    printf("|        |                                                         |\n");
    printf("|   01   |%s|\n",quadro[0][0].nome);
    printf("|________|");

}