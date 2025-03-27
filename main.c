#include "funcoes.h"
#define TAM 9

int main ()
{
    Aluno discet;
    float media;
    float soma = 0;
    int clas[3] = {0}; // array para armazenar a classe da disciplina

    media = Entrada(TAM, 0, &discet);
    

    // Printatndo // desordenado
    for(int i = 0; i < TAM; i++)
    {
        if (i == 0)
        {
            int j = 0;
            printf("(");
            while(j < TAM)
            {
                printf("%d, ", discet.periodo[j]);
                j++;
            }
            printf(")\n");
        }


        printf("%s %.2f\n", discet.cod[i], discet.media[i]);    
        
    }

    // Ordenando as médias em ordem decrescente
    Ordene(TAM, &discet);

    printf("\n\n");

    // Printatndo // Ordenado
    for(int i = 0; i < TAM; i++)
    {
        if (i == 0)
        {
            int j = 0;
            printf("(");
            while(j < TAM)
            {
                printf("%d, ", discet.periodo[j]);
                j++;
            }
            printf(")\n");
        }


        printf("%s %.2f\n", discet.cod[i], discet.media[i]);    
        
    }

    printf("Essa é a média: %.2f", media);


    // Buscando as melhores diciplinas do aluno com base na nota e classe da matéria;
    for(int i = 0; i < TAM; i++)
    {
        if(discet.media[i] > media)  // caso a nota seja maior que a médias das notas;
        {
            for(int j = 0; j < 8; j++) // Percorrendo toda a tabela de disciplinas 
            {
                for (int k = 0; k < 5; k++)
                {
                    if(strcmp(discet.cod[i], quadro[j][k].codigo) == 0) // verificando se o código da dicipina que o aluno cursou é igual ao código que está na tabela de disciplinas( se são igauis) 
                    {
                        switch(quadro[j][k].classe) // Somando quantas vezes uma materias de cada classe aparece;
                        {
                            case 0:                 //Como também alocando na posição correta do vetor 
                            {
                                clas[0] += 1;
                                break; 
                            }

                            case 1:
                            {
                                clas[1] += 1;
                                break;
                            }

                            case 2:
                            {
                                clas[2] += 1;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    printf("\n");

    for (int i = 0; i < 3; i++)
    {
        printf("%d ", clas[i]);
    }

    
    // retornar  a  maior classe (na qual o aluno se saiu melhor, com base na quatida de vezes que ela apreceu)
    int maior_c = MaiorClasse(clas);
    printf("\n%d\n", maior_c);

    // Verificando quais matérias podemos alocar(adiantar) para o aluno;
    int indi = 0;
    for(int i = (discet.periodo[0] + 1); i < 8; i++) // Percorrendo as diciplinas a partir do semestre informado + 1
    {
        for (int j = 0; j < 5; j++)
        {
            if(quadro[i][j].pre == 0) // Verificando se existe pre-requisito, nesse caso não tem;
            {
                int cont = 0;
                for(int k = 0; k < 5; k++) // Irei comparar a diciplina da linha i, com todas as diciplinas das linha i - 1, 
                {                          // para achar algum choque de horário
                    
                    if(strcmp(quadro[i][j].horario, quadro[i - 1][k].horario) == 0) cont = 1; // Verificando se ha choque de horários;

                    if (cont == 1) break;
                }

                if (cont == 0)
                {
                    strcpy(discet.disc[indi], quadro[i][j].codigo); // copiando o código da materia para as diciplinas que podem se adiantadas 
                    indi++; // salvando a quantida de de disciplinas;
                }
            }

            else if (quadro[i][j].pre == 1) // existe o pre-requisito
            {
               int sum = 0;
               switch(quadro[i][j].requi.quant) // Escolhendo quantas matérias de pre-requisitos são necessárias;
               {
                    case 1: // Somente 1 pre-requisito
                    {
                        for(int l = 0; l < TAM; l++) // Percorrendo as materias cursadas pelo Aluno;
                        {
                            for(int m = 0; m < 3; m++) // Percorrendo as pre-requisitos das materias que o aluno pretende cursar;
                            {
                                if(strcmp(discet.cod[l], quadro[i][j].requi.requi[m]) == 0) // Verificando se o aluno tem a matérias necessária
                                {
                                    int cont = 0;
                                    for(int n = 0; n = 5; n ++) // Verificando se ha choque de horário com as diciplinas;
                                    {
                                        if(strcmp(quadro[i][j].horario, quadro[i - 1][n].horario) == 0) cont = 1; 
                                        if (cont = 1) break;

                                    }

                                    if (cont == 0)
                                    {
                                        strcpy(discet.disc[indi], quadro[i][j].codigo); // Copiando a matérias da tabela de disciplinas para o lista de disciplinas que o aluno pode cursar!
                                        indi++;
                                    }
                                }
                            }
                        }

                        break;
                    }

                    case 2: // 2 pre-requisitos
                    {
                        for(int l = 0; l < TAM; l++) // Percorrendo as materias cursadas pelo Aluno;
                        {
                            for( int m = 0; m < 3; m++) // Percorrendo as pre-requisitos das materias que o aluno pretende cursar;
                            {
                                if(strcmp(discet.cod[l], quadro[i][j].requi.requi[m]) == 0) sum++;
                                
                            }
                        }

                        if (sum == 2) // verificando se os 2 pre-requisitos foram atendidos
                        {
                            int cont = 0;
                            for(int n = 0; n = 5; n ++) // Verificando se ha choque de horário com as diciplinas;
                            {
                                if(strcmp(quadro[i][j].horario, quadro[i - 1][n].horario) == 0) cont = 1; // Verificando se ha choque de horário
                                if (cont = 1) break;

                            }

                            if (cont == 0)
                            {
                                strcpy(discet.disc[indi], quadro[i][j].codigo); // Copiando a matérias da tabela de disciplinas para o lista de disciplinas que o aluno pode cursar!
                                indi++;
                            }


                        }

                        break;
                    }

                    case 3: // 3 matérias são postas como pre-requisito, porém somente duas são necessárias
                    {
                        int check = 0;
                        for(int l = 0; l < TAM; l++) // Percorrendo as materias cursadas pelo Aluno;
                        {
                            for(int m = 0; m < 3; m++) // Percorrendo as pre-requisitos das materias que o aluno pretende cursar;
                            { 
                                if (m != 2) // as duas primeiras materias são um (OU), o aluno só precisar ter uma das duas 
                                {
                                    if(strcmp(discet.cod[l], quadro[i][j].requi.requi[m]) == 0) sum++;
                                }

                                else // Essa matéria é obrigarótóri
                                {
                                    if(strcmp(discet.cod[l], quadro[i][j].requi.requi[m]) == 0) check = 1;
                                }
                            }

                            if(sum > 0 && check > 0) // Verificando se o aluno já cursou pelo menos uma das duas primeiras && se cursou a terceira
                            {
                                int cont = 0;
                                for(int n = 0; n = 5; n ++)
                                {
                                    if(strcmp(quadro[i][j].horario, quadro[i - 1][n].horario) == 0) cont = 1; // Verificando se ha choque de horário
                                    if (cont = 1) break;

                                }

                                if (cont == 0)
                                {
                                    strcpy(discet.disc[indi], quadro[i][j].codigo); // Copiando a matérias da tabela de disciplinas para o lista de disciplinas que o aluno pode cursar!
                                    indi++;
                                }
                            }
                        }

                        break;
                    }
                }
            }
        }
    }

    printf("\n%d\n", indi);
    for(int i = 0; i < indi; i ++)
    {
        printf("%s ", discet.disc[i]);
    }

    return 0;
}

