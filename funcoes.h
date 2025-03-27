#include "structs.h"

// FUNCOES DE ENTRADA
void LowerCase(char nome[50]);
void SemPrepo(char nome[50]);
int CalcularNome(matriz tabela[3][12], char nome[50], int soma_nome[4]);
float Entrada(int TAM, float soma, Aluno *discet);
int MaiorClasse(int *clas);

// FUNÇÕES DE TABELA
void MontarGrade(int i, disciplina[8][5], disciplina minha_grade[8][8]);
void MostrasGradeCompleta(disciplina quadro[8][5]);


//Funções de Ordenação;
void Ordene(int TAM, Aluno *discet);



// Scrit das Funcoes

float Entrada(int TAM, float soma, Aluno *discet)
{
    // lendo meus períodos
    for (int i = 0; i < 1; i++)
    {
        scanf("%d", &discet->periodo[i]);
    }
 
    // lendo meus códigos da turma;
    for(int i = 0; i < TAM; i++)
    {
        scanf("%s", discet->cod[i]);
        discet->cod[i][strcspn(discet->cod[i], "\n")] = '\0';
    }
 
    // Lendo minhas notas:
    int tot = 0; // total de entradas válidas para média
    for(int i = 0; i < TAM; i++)
    {
        scanf("%f", &discet->media[i]);
        if(discet->media[i] != -1) soma += discet->media[i], tot += 1;
             
    }

    return soma / tot;
}


void Ordene(int TAM, Aluno *discet)
{
    // Ordenando da média em ordem decrescente
    for(int i = 0; i < TAM - 1; i++)
    {
        for(int j = i + 1; j < TAM; j++)
        {
            if(discet->media[i] < discet->media[j])
            {
                float auxi = discet->media[i];
                discet->media[i] = discet->media[j];
                discet->media[j] = auxi;


                char temp[20];
                strcpy(temp, discet->cod[i]);
                strcpy(discet->cod[i], discet->cod[j]);
                strcpy(discet->cod[j], temp);

                // Ao ordenar a média, também ordeno o código da disciplina
                // assim a ao acessa a posição discet.media[0] e discent.cod[0]
                // nota e matéria serão correspondentes;  
                
            }
        }

    }

    return;
}

int MaiorClasse(int *clas)
{
    // retornar  a  maior classe (na qual o aluno se saiu melhor, com base na quatida de vezes que ela apreceu)
    int maior = 0;
    if (clas[1] > clas[0])
    {
        if(clas[1] > clas[2]) maior = 1;
        else maior = 2;
    }

    else if ( clas[2] > clas[0])
    {
        if (clas[2] > clas[1]) maior = 2;
        else maior = 1;
    }

    else maior = 3; // empate; (todas as classes aparecem a mesma quantidade de vezes)

    return maior;
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