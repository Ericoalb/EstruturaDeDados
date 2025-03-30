#include "funcoes.h"
#define TAM 5

int main ()
{
    Aluno discet;
    float media;
    float soma = 0;
    int clas[3] = {0}; // array para armazenar a classe da disciplina
    int cond;

    Preencha(&discet);

    media = Entrada(TAM, 0, &discet, 0, 0);

    /*
    // Printatndo // desordenado
    for(int i = 0; i < TAM; i++)
    {
        if (i == 0)
        {
            int j = 0;
            printf("(");
            while(j < 1)
            {
                printf("%d ", discet.periodo[j]);
                j++;
            }
            printf(")\n");
        }


        printf("%s %.2f\n", discet.temp_cod[i], discet.media[i]);    
        
    }
    */

    // Ordenando as médias em ordem decrescente
    Ordene(TAM, &discet);
    Separe(&discet, TAM);
    printf("\n\n");

    /*

    // Printatndo // Ordenado
    for(int i = 0; i < TAM; i++)
    {
        if (i == 0)
        {
            int j = 0;
            printf("(");
            while(j < 1)
            {
                printf("%d ", discet.periodo[j]);
                j++;
            }
            printf(")\n");
        }


        printf("%s %.2f\n", discet.temp_cod[i], discet.media[i]);    
        
    }

    printf("Essa é a média: %.2f", media);
    */
    /*
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

    */


    // retornar  a  maior classe (na qual o aluno se saiu melhor, com base na quatida de vezes que ela apreceu)
    int maior_c = MaiorClasse(clas);
    //printf("\n%d\n", maior_c);

    // Verificando quais matérias podemos alocar(adiantar) para o aluno;
    
    if(discet.periodo[0] < 8)
    {
        switch(discet.fluxo)
        {
            case 1:
            {
                Grade(&discet);
                Aloque(&discet, 1);
                printf("\n");

                if(discet.id > 0)
                {
                    printf("Disciplinas que você pode adiantar:\n");
                    ImprimaDisc(&discet);
                    printf("\n");
                }
    
                printf("Prioridades de escolhas Com Base no Desempenho Acadêmico\n");
                ClasPriori(maior_c, clas, &discet);
                printf("\n");

                ChoqueHorario(&discet);
                printf("\n");
                
                int soma = 0;
                for(int i = 0; i < discet.id; i++)
                {
                    soma += discet.disc[i].carga_hora;
                }

                printf("%d", soma);

                break;
            }
    
            case 2:
            {
                int count;
                Grade(&discet);
                Aloque(&discet, 0);
                printf("\n");
    
                if(discet.id > 0)
                {
                    printf("DISCIPLINAS QUE VOCÊ PODE ADIANTAR:\n");
                    ImprimaDisc(&discet);
                    printf("\n");
                }
    
                ChoqueHorario(&discet);
                printf("\n\n");

                printf("DISCIPLINAS PENDENTES:\n");

                for(int i = 0; i < discet.ip; i++)
                {
                    printf("%s ", discet.cod_p[i]);

                    for (int j = 0; j < 7; j++)
                    {
                        for(int k = 0; k < discet.dis_obg[j]; k++)
                        {
                            if(strcmp(discet.cod_p[i], quadro[j][k].codigo) == 0)
                            {   
                                printf("%s\n", quadro[j][k].nome);
                                break;
                            }
                        }
                    }
                                           
                }

                printf("\n");
                printf("MATÉRIAS QUE VOCÊ NÃO PODE CURSAR:");
                for (int i = 0; i < discet.ip; i++)
                {
                  
                    printf("\n");
                    count = PrioridadeDisc(&discet, i);
                    printf("\n");
                    
                }
    
                printf("Esse é o count %d\n", count);
                
                if(count > 2)
                {
                    printf("Disciplina pendente de Alta prioridade\n");
                }

                else if (count == 2)
                {
                    printf("Disciplina pendente de Médias prioridade\n");

                }

                else
                {
                    printf("Disciplina de baixa prioridade\n");
                }
                

                

                break;
            }
        }
    }

    

    return 0;
}

