#include "structs.h"

// FUNCOES DE ENTRADA
void LowerCase(char nome[50]);
void SemPrepo(char nome[50]);
int CalcularNome(matriz tabela[3][12], char nome[50], int soma_nome[4]);
float Entrada(int TAM, float soma, Aluno *discet, int ic, int ip);
int MaiorClasse(int *clas);
void substituirVirgulaPorPonto(char *str);

// FUNÇÕES DE TABELA
void MontarGrade(int i, disciplina[8][5], disciplina minha_grade[8][8]);
void Grade(Aluno *discet);

//Funções de Ordenação;
void Ordene(int TAM, Aluno *discet);
void Separe(Aluno *discet, int TAM);


//Função do aluno
void Preencha(Aluno *discet);
void Aloque(Aluno *discet, int num);
void ChoqueHorario(Aluno *discet);
void ImprimaDisc(Aluno *discet);
void ClasPriori(int maior_c, int *clas, Aluno *discet);
int PrioridadeDisc(Aluno *discet, int index);

// Substituindo a vírgula por ponto na string para converter para float
void substituirVirgulaPorPonto(char *str) {
    while (*str) {
        if (*str == ',') *str = '.';
        str++;
    }
}

// Scrit das Funcoes
float Entrada(int TAM, float soma, Aluno *discet, int i_c, int i_p)
{
    discet->ip = 0;
    discet->ic = 0;
    int div = 0;
    
    FILE *arquivo = fopen("data/dados.csv", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo.\n");
        return -1;
    }
    
    char linha[256];
    
    // lendo período e fluxo
    if (fgets(linha, sizeof(linha), arquivo)) {
        char *token = strtok(linha, ";\n");
        token = strtok(NULL, ";\n"); // Captura o número de períodos
        if (token) {
            discet->periodo[0] = atoi(token);
            token = strtok(NULL, ";\n");
            if (token) {
                discet->fluxo = atoi(token);
            }
        }
    }
    
    // Lendo disciplinas
    for (int i = 0; i < TAM && fgets(linha, sizeof(linha), arquivo); i++) {
        char *token = strtok(linha, ";\n");
        if (token) {
            strcpy(discet->temp_cod[i], token);
        }

        token = strtok(NULL, ";\n"); // Nome da disciplina (ignorado)
        
        token = strtok(NULL, ";\n"); // Nota
        if (token) {
            substituirVirgulaPorPonto(token);
            discet->media[i] = atof(token);
        }

        if (discet->media[i] >= 7) {
            discet->ic += 1;
            div += 1;
            soma += discet->media[i];
        } else if (discet->media[i] == -1) {
            discet->ip += 1;
        } else {
            discet->ip += 1;
            div += 1;
            soma += discet->media[i];
        }
    }
    
    fclose(arquivo);
    return (soma / div);
}

void Preencha(Aluno *discet)
{
    discet->dis_obg[0] = 5;
    discet->dis_obg[1] = 4;
    discet->dis_obg[2] = 4;
    discet->dis_obg[3] = 4;
    discet->dis_obg[4] = 4;
    discet->dis_obg[5] = 1;
    discet->dis_obg[6] = 2;
    discet->dis_obg[7] = 0;
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
                strcpy(temp, discet->temp_cod[i]);
                strcpy(discet->temp_cod[i], discet->temp_cod[j]);
                strcpy(discet->temp_cod[j], temp);

                // Ao ordenar a média, também ordeno o código da disciplina
                // assim a ao acessa a posição discet.media[0] e discent.cod[0]
                // nota e matéria serão correspondentes;  
                
            }
        }

    }

    return;
}

void Separe(Aluno *discet, int TAM)
{
    int ic = 0, ip = 0;
    
    for (int i = 0; i < TAM; i++)
    {
        if(discet->media[i] >= 7)
        {
            strcpy(discet->cod[ic], discet->temp_cod[i]);
            ic += 1;
        }

        else 
        {
            strcpy(discet->cod_p[ip], discet->temp_cod[i]);
            ip += 1;
        }
    }
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

void Aloque(Aluno *discet, int num)
{

    discet->id = 0;
    for(int i = (discet->periodo[0] + 1); i < 8; i++) // Percorrendo os períodos(linhas) a partir do semestre informado + 1
    {
        for (int j = 0; j < discet->dis_obg[i]; j++) // Percorrendo as disciplinas(colunas)
        {
            if(quadro[i][j].pre == 0) // Verificando se existe pre-requisito, nesse caso não tem;
            {
                int cont = 0;
                for(int k = 0; k < discet->dis_obg[discet->periodo[0]]; k++) // Irei comparar o horário da disciplina [i][j], com todos os horários das diciplinas [discet.periodo[0]][k] 
                {                                                           // para achar algum choque de horário
                    
                    if(strcmp(quadro[i][j].horario, quadro[discet->periodo[0]][k].horario) == 0) // Verificando se ha choque de horários; 
                    {                                                                           // quando ambos horários(string) são iguais;
                        cont = 1;                                                              
                    }
                    
                    else if (strlen(quadro[i][j].horario) == strlen(quadro[discet->periodo[0]][k].horario)) // Verificando se ha choque de horários;
                    {                                                                                      // Quando o tamnho das stings são iguais, porém as strings são diferentes
                        
                        int dia = 0, turno = 0, aula = 0; // Só existe colisão de horário quando as 3 variáveis são maiores que 0;                                                 
                        int e = 0; // contador da posição

                        while(quadro[i][j].horario[e] != 'M' && quadro[i][j].horario[e] != 'T')  // Lendo minha string até chegar no Turno, ou seja, estamos verificando os dias
                        {
                            if(quadro[i][j].horario[e] == quadro[discet->periodo[0]][k].horario[e]) // checando os dias
                            {
                                dia = 1;
                                e++; 
                            }

                            e++;
                        }

                        if(quadro[i][j].horario[e] == quadro[discet->periodo[0]][k].horario[e]) // Verificando o Turno, o indice de "e" já está na posição do Turno;
                        {
                            turno = 1;
                        }

                        e++; // indo para pŕoxima posição
                        
                        while(quadro[i][j].horario[e] != '\0') // caminhando até o final da string, e verificos os horários de aula
                        {
                            if(quadro[i][j].horario[e] == quadro[discet->periodo[0]][k].horario[e])
                            {
                                aula = 1;
                                break;
                            }
                            e++;
                        }
                        
                        if(dia > 0 && turno > 0 && aula > 0) cont = 1; // Caso as três variáveis sejam maiores que 0, existe o choque de horário;
                    }

                    else // Strings de tamnhos diferentes;
                    {
                        // QUEBRANDO AS STRINGS A APRITIR DO T OU M

                        int l1 = strlen(quadro[i][j].horario);  // Salvando o tamnho das minha strins
                        int l2 = strlen(quadro[discet->periodo[0]][k].horario);

                        int ti; // turno de tempi1
                        int tj; // turno de tempj1
                        int ei = 0; // indice de tempi1
                        int ej = 0; // indice de tempi2
                        int dia = 0, turno = 0, aula = 0;
                        char tempi1[10], tempi2[10], tempj1[10], tempj2[10];
                        strcpy(tempi1, quadro[i][j].horario);
                        strcpy(tempj1, quadro[discet->periodo[0]][k].horario);

                        while(tempi1[ei] != '\0')
                        {
                            if(tempi1[ei] == 'T')
                            {
                                ti = 0;
                                break;
                            }
            
                            else if(tempi1[ei] == 'M')
                            {
                                ti = 1;
                                break;
                            }
            
                            ei++;
                        }   
                        
                        switch(ti)
                        {
                            case 0:
                            {
                                tempi1[strcspn(tempi1, "T")] = '\0';
                                break;    
                            }
            
                            case 1:
                            {
                                tempi1[strcspn(tempi1, "M")] = '\0';
                                break;
                            }
                        }

                        ei = ei + 1;
                        int ind = 0;
                        while(quadro[i][j].horario[ei] != '\0')
                        {
                            tempi2[ind] = quadro[i][j].horario[ei];
                            ei++;
                            ind++;
                        }
                        tempi2[ei] = '\0';
                        

                        while(tempj1[ej] != '\0')
                        {
                            if(tempj1[ej] == 'T')
                            {
                                tj = 0;
                                break;
                            }
            
                            else if(tempj1[ej] == 'M')
                            {
                                tj = 1;
                                break;
                            }
            
                            ej++;
                        }

                        switch(tj)
                        {
                            case 0:
                            {
                                tempj1[strcspn(tempj1, "T")] = '\0';
                                break;
                            }
            
                            case 1:
                            {
                                tempj1[strcspn(tempj1, "M")] = '\0';
                                break;
                            }
                        }

                        ej = ej + 1;
                        int jnd = 0;
                        while(quadro[discet->periodo[0]][k].horario[ej] != '\0') //
                        {
                            tempj2[jnd] = quadro[discet->periodo[0]][k].horario[ej];
                            ej++;
                            jnd++;
                        }
                        tempj2[jnd] = '\0';
                  

                        if(strlen(tempi1) == strlen(tempj1))  
                        {
                            int l = 0;
                            while(l < strlen(tempi1))
                            {
                                if(tempi1[l] == tempj1[l])
                                {
                                    dia = 1;
                                    break;
                                }
            
                                l++;
                            }
                        }

                        else if (strlen(tempi1) > strlen(tempj1)) //
                        {
                            for(int l = 0; l < strlen(tempj1); l++)
                            {
                                for(int m = 0; l < strlen(tempi1); l++)
                                {
                                    if(tempj1[l] == tempi1[m])
                                    {
                                        dia = 1;
                                        break;
                                    }
                                }
            
                                if (dia == 1) 
                                {
                                    break;
                                }
                            }
                            
                        }

                        else 
                        {
                            for(int l = 0; l < strlen(tempi1); l++)
                            {
                                for(int m = 0; m < strlen(tempj1); m++)
                                {
                                    if(tempi1[l] == tempj1[m])
                                    {
                                        dia = 1;
                                        break;
                                    }
                                }
            
                                if (dia == 1)
                                {
                                    break;
                                }
                            }
                        }

                        if(quadro[i][j].horario[strlen(tempi1)] == quadro[discet->periodo[0]][k].horario[strlen(tempj1)])
                        {
                            turno = 1;
                        }

                        if(strlen(tempi2) == strlen(tempj2)) 
                        {
                            for(int l = 0; l < strlen(tempi2); l++)
                            {
                                if(tempi2[l] == tempj2[j])
                                {
                                    aula = 1;
                                    break;
                                }
                            }
                        }
            
                        else if(strlen(tempi2) > strlen(tempj2))
                        {
                            for(int l = 0; l < strlen(tempj2); l++)
                            {
                                for(int m = 0; m < strlen(tempi2); m++)
                                {
                                    if(tempj2[l] == tempi2[m])
                                    {
                                        aula = 1;
                                        break;
                                    }
                                }
            
                                if (aula == 1)
                                {
                                    break;
                                }
                            }
                        }
            
                        else
                        {
                            for(int l = 0; l < strlen(tempi2); l++)
                            {
                                for(int m = 0; m < strlen(tempj2); m++)
                                {
                                    if(tempi2[l] == tempj2[m])
                                    {
                                        aula = 1;
                                        break;
                                    }
                                }
            
                                if (aula == 1)
                                {
                                    break;
                                }
                            }
                        }


                        if ( dia > 0 && turno > 0 && aula > 0)
                        { 
                          cont = 1;
                        }
                        
                    }

                    if (cont == 1) break;
                }

                if (cont == 0)
                {
                    strcpy(discet->disc[discet->id].cod, quadro[i][j].codigo); // copiando o código da materia para as diciplinas que podem se adiantadas 
                    strcpy(discet->disc[discet->id].horario, quadro[i][j].horario);
                    strcpy(discet->disc[discet->id].nome, quadro[i][j].nome);
                    discet->disc[discet->id].carga_hora = quadro[i][j].carga_horaria;
                    discet->id += 1; // salvando a quantida de de disciplinas;
                }
            }

            else if (quadro[i][j].pre == 1) // existe o pre-requisito
            {
               int sum = 0;
               int valido = 0;
               switch(quadro[i][j].requi.quant) // Escolhendo quantas matérias de pre-requisitos são necessárias;
               {
                    case 1: // Somente 1 pre-requisito
                    {
                        for(int l = 0; l < discet->ic; l++) // Percorrendo as materias cursadas pelo Aluno, em discet.cod;
                        {
                            for(int m = 0; m < 3; m++) // Percorrendo as pre-requisitos das materias que o aluno pretende cursar;
                            {
                                if(strcmp(discet->cod[l], quadro[i][j].requi.requi[m]) == 0) // Verificando se o aluno tem a matérias necessária
                                {
                                    valido = 1;
                                    break;
                                }
                            }

                            if (valido == 1) break;
                        }

                        break;
                    }

                    case 2: // 2 pre-requisitos
                    {
                        for(int l = 0; l < discet->ic; l++) // Percorrendo as materias cursadas pelo Aluno;
                        {
                            for( int m = 0; m < 3; m++) // Percorrendo as pre-requisitos das materias que o aluno pretende cursar;
                            {
                                if(strcmp(discet->cod[l], quadro[i][j].requi.requi[m]) == 0) sum++;
                                
                                if( sum == 2)
                                {
                                    valido = 1;
                                    break;
                                }
                            }

                            if (valido == 1) break;

                        }
                        break;
                    }

                    case 3: // 3 matérias são postas como pre-requisito, porém somente duas são necessárias
                    {
                        int check = 0;
                        for(int l = 0; l < discet->ic; l++) // Percorrendo as materias cursadas pelo Aluno;
                        {
                            for(int m = 0; m < 3; m++) // Percorrendo as pre-requisitos das materias que o aluno pretende cursar;
                            { 
                                if (m != 2) // as duas primeiras materias são um (OU), o aluno só precisar ter uma das duas 
                                {
                                    if(strcmp(discet->cod[l], quadro[i][j].requi.requi[m]) == 0) sum++;
                                }

                                else // Essa matéria é obrigarótóri
                                {
                                    if(strcmp(discet->cod[l], quadro[i][j].requi.requi[m]) == 0) check = 1;
                                }

                                if (sum > 0 && check > 0)
                                {
                                    valido = 1;
                                    break;
                                }
                            }

                            if(valido == 1) // Verificando se o aluno já cursou pelo menos uma das duas primeiras && se cursou a terceira
                            break;
                        }

                        break;
                    }

                    case 4:
                    {
                        if(discet->periodo[0] > 5 && discet->fluxo != 1)
                        {   
                            int verifique;
                            for(int l = 0; l < discet->ic; l++)
                            {   
                                verifique = 0;
                                for(int m = 0; m < 21; m++)
                                {
                                    if(strcmp(discet->cod[l], pre[m].requi) == 0)
                                    {
                                        verifique = 1;
                                        break;
                                    }
                                }

                                if(verifique == 0)
                                {
                                    break;
                                }
                            }

                            if(verifique == 1)
                            {
                                valido = 1;
                                break;
                            }
                        }

                        break;
                    }
                }

                if (valido == 1)
                {                       // HORÁRIOS DE AULA;
                    int cont = 0;
                    for(int k = 0; k < discet->dis_obg[discet->periodo[0]]; k++) // Irei comparar o horário da disciplina [i][j], com todos os horários das diciplinas [discet.periodo[0]][k] 
                    {                                                           // para achar algum choque de horário
                        if(strcmp(quadro[i][j].horario, quadro[discet->periodo[0]][k].horario) == 0) // Verificando se ha choque de horários; 
                        {                                                                           // quando ambos horários(string) são iguais;
                            cont = 1;                                                              
                        }
                        
                        else if (strlen(quadro[i][j].horario) == strlen(quadro[discet->periodo[0]][k].horario)) // Verificando se ha choque de horários;
                        {                                                                                      // Quando o tamnho das stings são iguais, porém as strings são diferentes
                            
                            int dia = 0, turno = 0, aula = 0; // Só existe colisão de horário quando as 3 variáveis são maiores que 0;                                                 
                            int e = 0; // contador da posição

                            while(quadro[i][j].horario[e] != 'M' && quadro[i][j].horario[e] != 'T')  // Lendo minha string até chegar no Turno, ou seja, estamos verificando os dias
                            {
                                if(quadro[i][j].horario[e] == quadro[discet->periodo[0]][k].horario[e]) // checando os dias
                                {
                                    dia = 1;
                                    e++; 
                                }

                                e++;
                            }

                            if(quadro[i][j].horario[e] == quadro[discet->periodo[0]][k].horario[e]) // Verificando o Turno, o indice de "e" já está na posição do Turno;
                            {
                                turno = 1;
                            }

                            e++; // indo para pŕoxima posição
                            
                            while(quadro[i][j].horario[e] != '\0') // caminhando até o final da string, e verificos os horários de aula
                            {
                                if(quadro[i][j].horario[e] == quadro[discet->periodo[0]][k].horario[e])
                                {
                                    aula = 1;
                                    break;
                                }
                                e++;
                            }
                            
                            if(dia > 0 && turno > 0 && aula > 0) cont = 1; // Caso as três variáveis sejam maiores que 0, existe o choque de horário;
                        }

                        else // Strings de tamnhos diferentes;
                        {
                            // QUEBRANDO AS STRINGS A APRITIR DO T OU M
    
                            int l1 = strlen(quadro[i][j].horario);  // Salvando o tamnho das minha strins
                            int l2 = strlen(quadro[discet->periodo[0]][k].horario);
    
                            int ti; // turno de tempi1
                            int tj; // turno de tempj1
                            int ei = 0; // indice de tempi1
                            int ej = 0; // indice de tempi2
                            int dia = 0, turno = 0, aula = 0;
                            char tempi1[10], tempi2[10], tempj1[10], tempj2[10];
                            strcpy(tempi1, quadro[i][j].horario);
                            strcpy(tempj1, quadro[discet->periodo[0]][k].horario);
    
                            while(tempi1[ei] != '\0')
                            {
                                if(tempi1[ei] == 'T')
                                {
                                    ti = 0;
                                    break;
                                }
                
                                else if(tempi1[ei] == 'M')
                                {
                                    ti = 1;
                                    break;
                                }
                
                                ei++;
                            }   
                            
                            switch(ti)
                            {
                                case 0:
                                {
                                    tempi1[strcspn(tempi1, "T")] = '\0';
                                    break;    
                                }
                
                                case 1:
                                {
                                    tempi1[strcspn(tempi1, "M")] = '\0';
                                    break;
                                }
                            }
    
                            ei = ei + 1;
                            int ind = 0;
                            while(quadro[i][j].horario[ei] != '\0')
                            {
                                tempi2[ind] = quadro[i][j].horario[ei];
                                ei++;
                                ind++;
                            }
                            tempi2[ei] = '\0';
                           
    
                            while(tempj1[ej] != '\0')
                            {
                                if(tempj1[ej] == 'T')
                                {
                                    tj = 0;
                                    break;
                                }
                
                                else if(tempj1[ej] == 'M')
                                {
                                    tj = 1;
                                    break;
                                }
                
                                ej++;
                            }
    
                            switch(tj)
                            {
                                case 0:
                                {
                                    tempj1[strcspn(tempj1, "T")] = '\0';
                                    break;
                                }
                
                                case 1:
                                {
                                    tempj1[strcspn(tempj1, "M")] = '\0';
                                    break;
                                }
                            }
    
                            ej = ej + 1;
                            int jnd = 0;
                            while(quadro[discet->periodo[0]][k].horario[ej] != '\0') //
                            {
                                tempj2[jnd] = quadro[discet->periodo[0]][k].horario[ej];
                                ej++;
                                jnd++;
                            }
                            tempj2[jnd] = '\0';
    
    
                            if(strlen(tempi1) == strlen(tempj1))  
                            {
                                int l = 0;
                                while(l < strlen(tempi1))
                                {
                                    if(tempi1[l] == tempj1[l])
                                    {
                                        dia = 1;
                                        break;
                                    }
                
                                    l++;
                                }
                            }
    
                            else if (strlen(tempi1) > strlen(tempj1)) //
                            {
                                for(int l = 0; l < strlen(tempj1); l++)
                                {
                                    for(int m = 0; l < strlen(tempi1); l++)
                                    {
                                        if(tempj1[l] == tempi1[m])
                                        {
                                            dia = 1;
                                            break;
                                        }
                                    }
                
                                    if (dia == 1) 
                                    {
                                        break;
                                    }
                                }
                                
                            }
    
                            else 
                            {
                                for(int l = 0; l < strlen(tempi1); l++)
                                {
                                    for(int m = 0; m < strlen(tempj1); m++)
                                    {
                                        if(tempi1[l] == tempj1[m])
                                        {
                                            dia = 1;
                                            break;
                                        }
                                    }
                
                                    if (dia == 1)
                                    {
                                        break;
                                    }
                                }
                            }
    
                            if(quadro[i][j].horario[strlen(tempi1)] == quadro[discet->periodo[0]][k].horario[strlen(tempj1)])
                            {
                                turno = 1;
                            }
    
                            if(strlen(tempi2) == strlen(tempj2)) 
                            {
                                for(int l = 0; l < strlen(tempi2); l++)
                                {
                                    if(tempi2[l] == tempj2[j])
                                    {
                                        aula = 1;
                                        break;
                                    }
                                }
                            }
                
                            else if(strlen(tempi2) > strlen(tempj2))
                            {
                                for(int l = 0; l < strlen(tempj2); l++)
                                {
                                    for(int m = 0; m < strlen(tempi2); m++)
                                    {
                                        if(tempj2[l] == tempi2[m])
                                        {
                                            aula = 1;
                                            break;
                                        }
                                    }
                
                                    if (aula == 1)
                                    {
                                        break;
                                    }
                                }
                            }
                
                            else
                            {
                                for(int l = 0; l < strlen(tempi2); l++)
                                {
                                    for(int m = 0; m < strlen(tempj2); m++)
                                    {
                                        if(tempi2[l] == tempj2[m])
                                        {
                                            aula = 1;
                                            break;
                                        }
                                    }
                
                                    if (aula == 1)
                                    {
                                        break;
                                    }
                                }
                            }
    
    
                            if ( dia > 0 && turno > 0 && aula > 0)
                            { 
                              cont = 1;
                              
                            }
                            
                        }

                        if (cont == 1) break;
                    }

                    if (cont == 0)
                    {
                        strcpy(discet->disc[discet->id].cod, quadro[i][j].codigo); // copiando o código da materia para as diciplinas que podem se adiantadas 
                        strcpy(discet->disc[discet->id].horario, quadro[i][j].horario);
                        strcpy(discet->disc[discet->id].nome, quadro[i][j].nome);
                        discet->disc[discet->id].carga_hora = quadro[i][j].carga_horaria;
                        discet->id += 1; // salvando a quantida de de disciplinas;
                    }
                }

            }
        }
    }


}

void ChoqueHorario(Aluno *discet)
{
    for (int i = 0; i < (discet->id - 1); i++)
    {
        for(int j = i + 1; j < discet->id; j++)
        {
            // QUEBRANDO AS STRINGS A APRITIR DO T OU M

            int ti; // turno de tempi1
            int tj; // turno de tempj1
            int ei = 0; // indice de tempi1
            int ej = 0; // indice de tempi2
            int dia = 0, turno = 0, aula = 0;

            char tempi1[10], tempi2[10], tempj1[10], tempj2[10];
            strcpy(tempi1, discet->disc[i].horario);
            strcpy(tempj1, discet->disc[j].horario);

            while(tempi1[ei] != '\0')
            {
                if(tempi1[ei] == 'T')
                {
                    ti = 0;
                    break;
                }

                else if(tempi1[ei] == 'M')
                {
                    ti = 1;
                    break;
                }

                ei++;
            }
            
            
            switch(ti)
            {
                case 0:
                {
                    tempi1[strcspn(tempi1, "T")] = '\0';
                    break;    
                }

                case 1:
                {
                    tempi1[strcspn(tempi1, "M")] = '\0';
                    break;
                }
            }

            
            ei = ei + 1;
            int ind = 0;
            while(discet->disc[i].horario[ei] != '\0')
            {
                tempi2[ind] = discet->disc[i].horario[ei];
                ei++;
                ind++;
            }
            tempi2[ei] = '\0';

            
            while(tempj1[ej] != '\0')
            {
                if(tempj1[ej] == 'T')
                {
                    tj = 0;
                    break;
                }

                else if(tempj1[ej] == 'M')
                {
                    tj = 1;
                    break;
                }

                ej++;
            }


            switch(tj)  
            {
                case 0:
                {
                    tempj1[strcspn(tempj1, "T")] = '\0';
                    break;
                }

                case 1:
                {
                    tempj1[strcspn(tempj1, "M")] = '\0';
                    break;
                }
            }

            ej = ej + 1;  
            int jnd = 0;
            while(discet->disc[j].horario[ej] != '\0')
            {
                tempj2[jnd] = discet->disc[j].horario[ej];
                ej++;
                jnd++;
            }
            tempj2[jnd] = '\0';
            
            if(strlen(tempi1) == strlen(tempj1))  
            {
                int l = 0;
                while(l < strlen(tempi1))
                {
                    if(tempi1[l] == tempj1[l])
                    {
                        dia = 1;
                        break;
                    }

                    l++;
                }
            }

            
            else if (strlen(tempi1) > strlen(tempj1)) 
            {
                for(int l = 0; l < strlen(tempj1); l++)
                {
                    for(int m = 0; l < strlen(tempi1); l++)
                    {
                        if(tempj1[l] == tempi1[m])
                        {
                            dia = 1;
                            break;
                        }
                    }

                    if (dia == 1) 
                    {
                        break;
                    }
                }
            }
            
            else 
            {
                for(int l = 0; l < strlen(tempi1); l++)
                {
                    for(int m = 0; m < strlen(tempj1); m++)
                    {
                        if(tempi1[l] == tempj1[m])
                        {
                            dia = 1;
                            break;
                        }
                    }

                    if (dia == 1)
                    {
                        break;
                    }
                }
            }
            
            if(discet->disc[i].horario[strlen(tempi1)] == discet->disc[j].horario[strlen(tempj1)])
            {
                turno = 1;
            }


            if(strlen(tempi2) == strlen(tempj2)) 
            {
                for(int l = 0; l < strlen(tempi2); l++)
                {
                    if(tempi2[l] == tempj2[j])
                    {
                        aula = 1;
                        break;
                    }
                }
            }

            else if(strlen(tempi2) > strlen(tempj2))
            {
                for(int l = 0; l < strlen(tempj2); l++)
                {
                    for(int m = 0; m < strlen(tempi2); m++)
                    {
                        if(tempj2[l] == tempi2[m])
                        {
                            aula = 1;
                            break;
                        }
                    }

                    if (aula == 1)
                    {
                        break;
                    }
                }
            }

            else
            {
                for(int l = 0; l < strlen(tempi2); l++)
                {
                    for(int m = 0; m < strlen(tempj2); m++)
                    {
                        if(tempi2[l] == tempj2[m])
                        {
                            aula = 1;
                            break;
                        }
                    }

                    if (aula == 1)
                    {
                        break;
                    }
                }
            }


          if ( dia == 1 && turno == 1 && aula == 1)
          {
            printf("\nDISCIPLINAAS COM CHOQUE DE HORÁRIOS:\n%s\n%s", discet->disc[i].nome, discet->disc[j].nome);
          } 
             
        }
        
    }

    return;
}

void ImprimaDisc(Aluno *discet)
{
    for(int i = 0; i < discet->id; i ++)
    {
        printf("%s %s %s\n", discet->disc[i].cod, discet->disc[i].nome, discet->disc[i].horario);
    }
}

void ClasPriori(int maior_c, int *clas, Aluno *discet)
{
    switch(maior_c)
    {
        
        case 0:
        {
            
            if(clas[1] > clas[2])
            {
                printf("1º) Materias Teóricas\n");
                printf("2º) Matérias de Cálculo\n");
                printf("3º) Matérias de Programção/Computação\n");
            }

            else if (clas[1] < clas[2])
            {
                printf("1º) Materias Teóricas\n");
                printf("2º) Matérias de Programção/Computação\n");
                printf("3º) Matérias de Cálculo\n");
            }

            else
            {
                printf("1º) Materias Teóricas\n");
                printf("2º) Matérias de Cálculo ou Matérias de Prgramação/Computação\n");
                
            }
            break;
        }

        case 1:
        {
            if(clas[0] > clas[2])
            {
                printf("1º) Matérias de Cálculo\n");
                printf("2º) Materias Teóricas\n");
                printf("3º) Matérias de Programção/Computação\n");
            }

            else if (clas[0] < clas[2])
            {
                printf("1º) Matérias de Cálculo\n");
                printf("2º) Matérias de Programção/Computação\n");
                printf("3º) Materias Teóricas\n");
            }

            else
            {
                printf("1º) Materias de Cálculo\n");
                printf("2º) Matérias Teóricas ou Matérias de Prgramação/Computação\n");
                
            }
            
            break;
        }

        case 2:
        {
            if(clas[0] > clas[1])
            {
                printf("1º) Matérias de Programção/Computação\n");
                printf("2º) Materias Teóricas\n");
                printf("3º) Matérias de Cálculo\n");
            }

            else if (clas[0] < clas[1])
            {
                printf("1º) Matérias de Programção/Computação\n");
                printf("2º) Matérias de Cálculo\n");
                printf("3º) Materias Teóricas\n");
            }

            else
            {
                printf("1º) Materias de Prgramação/Computação\n");
                printf("2º) Matérias de Teóricas ou Matérias de Cálculo \n");
                
            }

            break;
        }

        case 3:
        {
            
        }

    }
}

int PrioridadeDisc(Aluno *discet, int index)
{
    int count = 0;

    for(int j = discet->periodo[0]; j < 6; j++) // Navegando pelas linhas do meu qudro de discipinas
    {
        for(int k = 0; k < discet->dis_obg[j]; k++) // Percorrendo pelas colunas de cada linha
        {
          if(quadro[j][k].pre == 1)
          {
            for(int l = 0; l < quadro[j][k].requi.quant; l++)
            {
                if(quadro[j][k].requi.quant == 4 && l == 0)
                {
                    for(int m = 0; m < 21; m++)
                    {
                        if(strcmp(discet->cod_p[index], pre[m].requi) == 0)
                        {
                            printf("%s %s\n", quadro[j][k].nome ,pre[m].requi);
                            count += 1;
                        }
                    }
                }

                else if (strcmp(discet->cod_p[index], quadro[j][k].requi.requi[l]) == 0)
                {
                    printf("%s %s\n", quadro[j][k].nome ,quadro[j][k].requi.requi[l]);
                    count += 1;
                }
            }


          }
          
        }
    }

    return count;
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

void Grade(Aluno *discet)
{
    
    printf("____________________________________________________________________\n");
    printf("|        |       |                                                 |\n");
    printf("|SEMESTRE| CODIGO|                  DISCIPLINAS                    |\n");
    printf("|________|_______|_________________________________________________|\n");
    printf("|        |       |                                                 |\n");
    for(int i = 0; i < discet->dis_obg[discet->periodo[0]]; i++)
    {
    printf("|   %d    |%s|           %s                                        |\n", discet->periodo[0] + 1, quadro[discet->periodo[0]][i].codigo, quadro[discet->periodo[0]][i].nome);
    printf("|________|_______|_________________________________________________|\n");
    }
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