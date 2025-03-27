#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>


typedef struct   // Estrutura para receber a letra + o peso/valor;
{
    char letra[3]; // char de tamanho 3, pois o caractere com acento ocupa 3 bytes
    int peso; 

}matriz;


typedef struct main
{
   char requi [3][8]; // codigo das disciplinas requisitadas
   int quant; // quantidad de pre-requisitos;
}requisitos;


typedef struct
{
    char nome[50];
    char codigo[8];
    int carga_horaria;
    char horario[10];
    int  class;       // 0 materias teorica, 1 materias de calculo e 2 materias de programa
    int pre;          // 1 tem pre-requisito, 0 não tem pre-requisito
    requisitos requi;

}disciplina;



// FUNCOES DE ENTRADA
void LowerCase(char nome[50]);
void SemPrepo(char nome[50]);
int CalcularNome(matriz tabela[3][12], char nome[50], int soma_nome[4]);
void Entrada(char nome[50], int soma_nome[4], matriz tabela[3][12], int *periodo, char copia_nome[50]);

// FUNÇÕES DE TABELA
void MontarGrade(int i, disciplina[8][5], disciplina minha_grade[8][8]);
void MostrasGradeCompleta(disciplina quadro[8][5]);

int main()
{
    char nome[50];
    char copia_nome[50];
    int soma_nome[4];
    int periodo;
    disciplina minha_grade[8][8];

    setlocale(LC_ALL, "pt_BR.UTF-8"); // Garantindo que não haverá bugs com os acentos
    
    // Matriz de estuturas para armazenar em cada posição a "estrutura matriz" com  
    // sua rescptiva letra e peso/valor
    matriz tabela[3][12] = {{{"q", 1}, {"w", 6}, {"e", 7}, {"r", 6}, {"t", 5}, {"y", 2}, {"u", 3}, {"i", 8}, {"o", 9}, {"p", 4}, {"á", 3}, {"ã", 4}}, 
                            {{"a", 2}, {"s", 5}, {"d", 8}, {"f", 7}, {"g", 4}, {"h", 1}, {"j", 4}, {"k", 7}, {"l", 8}, {"ç", 5}, {"é", 2}, {"í", 3}},
                            {{"z", 3}, {"x", 4}, {"c", 9}, {"v", 8}, {"b", 3}, {"n", 2}, {"m", 5}, {"ó", 6}, {"õ", 7}, {"ô", 6}, {"â", 1}, {"ê", 2}}};


    // FALTA COMPLETAR COM AS ACEs E ALGUMAS DICIPLINAS DO 6,7 E 8 PERÍODO
    disciplina quadro[8][5] = {{{"LOGICA PARA COMPUTACAO", "COMP360", 72, "02M34", 0, 0}, {"COMPUTACAO SOCIEDADE E ETICA", "COMP361", 72, "02M56", 0, 0}, {"CALCULO DIFERENCIAL E INTEGRAL", "COMP363", 144, "356T234", 1, 0}, {"PROGRAMAÇAO 1", "COMP359", 72,"06M3456", 2, 0}, {"MATEMÁTICA DISCRETA", "ECOM003", 72, "24M12", 1, 0}},
                               {{"GEOMETRIA ANALITICA", "COMP367", 72, "24M34", 1, 0}, {"BANCO DE DADOS", "COMP365", 72, "35T12", 2, 0}, {"ESTRUTURA DE DADOS", "COMP364", 72, "24T34", 2, 1,"COMP359","*","*",1}, {"ORG. E ARQ. DE COMPUTADORES","COMP366", 72, "24T12", 0, 0}},
                               {{"ALGEBRA LINEAR", "COMP371", 72, "24T34", 0, 1, "COMP367", "*", "*", 1}, {"PROBABILIDADE E ESTATISTICA", "COMP370", 72, "24T12", 0, 1, "COMP363", "*", "*", 1}, {"TEORIA DOS GRAFOS", "COMP369", 72,"25M34", 2, 1, "COMP364", "COMP362","*", 2}, {"REDES DE COMPUTADORES", "COMP368", 72, "34M56", 0, 1, "COMP359", "*", "*", 1}},
                               {{"TEORIA DA COMPUTACAO", "COMP376", 72, "24T12", 0, 0}, {"PROJETO E ANALISE DE ALGORITMOS", "COMP374", 72, "25M56", 2, 1, "COMP364", "COMP369", "*", 2}, {"PROGRAMACAO 3", "COMP373", 72, "34T34", 2, 1, "COMP364", "COMP365", "COMP368", 3}, {"PROGRAMACAO 2", "COMP372", 72, "35T12", 2, 1, "COMP364", "COMP365", "COMP368", 3}},
                               {{"SISTEMAS OPERACIONAIS", "COMP378", 72,"24M34", 0, 1, "COMP366", "*", "*", 1}, {"COMPILADORES", "COMP379", 72, "24M56", 2, 1, "COMP364", "COMP376", "*", 2}, {"INTELIGENCIA ARTIFICIAL", "COMP380", 72, "35M34", 2, 1, "COMP364", "COMP360", "*", 2},{"COMPUTACAO GRAFICA", "COMP381", 72, "36M56", 2, 0}},
                               {{"PROJETO E DESENVOLVIMENTO DE SISTEMAS", "COMP382", 288, "2356T1234", 2, 1,"COMP364","COMP370", "COMP374", 3}},
                               {{"MET. DA PESQ. E DO TRABALHO", "COMP386", 72, "35M34", 0, 0}, {"NOCOES DE DIREITO", "COMP387", 72, "05T1234", 0, 0}}};



    
    printf("%d ", quadro[1][2].requi.quant);                   
    /*
    Entrada(nome, soma_nome, tabela, &periodo, copia_nome);
    
    switch(periodo)
    {
        case 1:
        {
            MontarGrade(periodo, quadro, minha_grade);
            break;
        }

    }

    for(int i = 1; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {

            printf("%s \n", minha_grade[i][j].nome);
        }

        printf("\n");
    }
    */
    return 0;
}

void Entrada(char nome[50], int soma_nome[4], matriz tabela[3][12], int *periodo, char copia_nome[50])
{
    fgets(nome, 50, stdin);
    nome[strcspn(nome, "\n")] = '\0';
    strcpy(copia_nome, nome);
    LowerCase(nome);
    SemPrepo(nome);
    CalcularNome(tabela, nome, soma_nome);
    scanf("%d", periodo);
    return;
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

void MontarGrade(int i, disciplina quadro[8][5], disciplina minha_grade[8][8])
{

    int soma = 0; // soma da carga horária

    while(i < 8) // linha da matriz minha_grade, como também referência de indice para acessar as linhas da matriz quadro
    {
        for(int k = 0; k < 8; k++) // coluna da matriz minha_grade
        {
            if (k < 4 && i < 5)                 // Adicionando as 4 disciplinas obrigatórias e indo até o 5 período
            {
                minha_grade[i][k] = quadro[i][k];
                soma += quadro[i][k].carga_horaria;
            }

            else if (i < 5)                 // Já adicionamos na grade todas as 4 disciplinas obrigatórias até o 5 período;
            {
                if(soma <= 576)
                {
                    for (int l = i + 1; l < 3; l++) // indice do Próximo período
                    {
                        for(int m = 0; m < 5; m++)  // Verificando se as disciplinas terão choque de horário, indice da coluna da matriz quadro
                        {
                            int choque = 0;

                            for(int o = 0; o < k; o++) /// Indice da coluna da matriz minha_grade;
                            {
                                if(strcmp(quadro[l][m].horario, minha_grade[i][o].horario) == 0) choque = 1;
                                if(choque == 1 ) break;
                            }

                            if(choque == 0)
                            {
                                soma += quadro[l][m].carga_horaria;

                                if(soma <= 576)
                                {
                                    minha_grade[i][k] = quadro[l][m];
                                }

                                else soma -= quadro[l][m].carga_horaria;
                            }
                        }
                    }
                }
            }

        }

        i++;
    }
}