#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct   // Estrutura para receber a letra + o peso/valor;
{
    char letra[3]; // char de tamanho 3, pois o caractere com acento ocupa 3 bytes
    int peso; 

}matriz;

typedef struct 
{
   char requi[3][8]; // codigo das disciplinas requisitadas
   int quant;        // quantidade de pre-requisitos;

}requisitos;


typedef struct
{
    char nome[50];
    char codigo[8];
    int carga_horaria;
    char horario[10];
    int classe;       // 0 materias teorica, 1 materias de calculo e 2 materias de programa
    int pre;          // 1 tem pre-requisito, 0 não tem pre-requisito
    requisitos requi;

}disciplina;


typedef struct 
{
    char cod[8];
    char horario[10];
    char nome[50];
    int carga_hora;
}cursada;

typedef struct 
{
    int periodo[8]; // Período do Aluno
    char temp_cod[50][8]; // Recebe todas as disciplinas
    char cod[50][8]; // Recebe o Codigo das Disciplinas que já foram cursadas
    char cod_p[50][8]; // Recebe Codigo das Disciplinas Perdidas
    float media[50]; // Media das disciplinas cursadas
    cursada disc[10]; // Disciplinas que o Aluno poderá adiantar / ou deverá pagar novamente!
    int dis_obg[8];    // Número de disciplinas obrigaŕorias em casda período.
    int ip;            // Armazenar o indice das diciplinas perdidas;
    int ic;            // Armazenar o indice das disciplinas cursadas;  
    int fluxo;         // fluxo do aluno;
    int id;            // armazenar o indice das disciplinas adiantadas;
}Aluno;

typedef struct 
{
    char requi[8];
}pds;


pds pre[21] = {"COMP360", "COMP361", "COMP363", "COMP359", "ECOM003", "COMP367", "COMP365", "COMP364", "COMP366", "COMP371", "COMP370", "COMP369", "COMP368", "COMP376", "COMP374", "COMP373", "COMP372", "COMP378", "COMP379", "COMP380", "COMP381"};


                            // FALTA COMPLETAR COM AS ACEs E ALGUMAS DICIPLINAS DO 6,7 E 8 PERÍODO
disciplina quadro[8][5] = {{{"LOGICA PARA COMPUTACAO", "COMP360", 72, "2M34", 0, 0}, {"COMPUTACAO SOCIEDADE E ETICA", "COMP361", 72, "2M56", 0, 0, 5}, {"CALCULO DIFERENCIAL E INTEGRAL", "COMP363", 144, "356T234", 1, 0}, {"PROGRAMAÇAO 1", "COMP359", 72,"6M3456", 2, 0}, {"MATEMÁTICA DISCRETA", "ECOM003", 72, "24M12", 1, 0}},
                           {{"GEOMETRIA ANALITICA", "COMP367", 72, "24M34", 1, 0}, {"BANCO DE DADOS", "COMP365", 72, "35T12", 2, 0}, {"ESTRUTURA DE DADOS", "COMP364", 72, "24T34", 2, 1,"COMP359","*","*",1}, {"ORG. E ARQ. DE COMPUTADORES","COMP366", 72, "24T12", 0, 0}},
                           {{"ALGEBRA LINEAR", "COMP371", 72, "24T34", 0, 1, "COMP367", "*", "*", 1}, {"PROBABILIDADE E ESTATISTICA", "COMP370", 72, "24T12", 0, 1, "COMP363", "*", "*", 1}, {"TEORIA DOS GRAFOS", "COMP369", 72,"25M34", 2, 1, "COMP364", "COMP362","*", 2}, {"REDES DE COMPUTADORES", "COMP368", 72, "34M56", 0, 1, "COMP359", "*", "*", 1}},
                           {{"TEORIA DA COMPUTACAO", "COMP376", 72, "24T12", 0, 0}, {"PROJETO E ANALISE DE ALGORITMOS", "COMP374", 72, "25M56", 2, 1, "COMP364", "COMP369", "*", 2}, {"PROGRAMACAO 3", "COMP373", 72, "34T34", 2, 1, "COMP364", "COMP365", "COMP368", 3}, {"PROGRAMACAO 2", "COMP372", 72, "35T12", 2, 1, "COMP364", "COMP365", "COMP368", 3},{"PRATICA DE EXTENSAO EM CIENCIA DA COMPUTACAO 1", "COMP377", 75, "5M12"}},
                           {{"SISTEMAS OPERACIONAIS", "COMP378", 72,"24M34", 0, 1, "COMP366", "*", "*", 1}, {"COMPILADORES", "COMP379", 72, "24M56", 2, 1, "COMP364", "COMP376", "*", 2}, {"INTELIGENCIA ARTIFICIAL", "COMP380", 72, "35M34", 2, 1, "COMP364", "COMP360", "*", 2},{"COMPUTACAO GRAFICA", "COMP381", 72, "36M56", 2, 0}},
                           {{"PROJETO E DESENVOLVIMENTO DE SISTEMAS", "COMP382", 288, "2356T1234", 2, 1,"COMP364","COMP370", "COMP374", 4}},
                           {{"MET. DA PESQ. E DO TRABALHO", "COMP386", 72, "35M34", 0, 0}, {"NOCOES DE DIREITO", "COMP387", 72, "5T1234", 0, 0}},
                           {{"Eletivas e TCC"}}};

                        // Matriz de estuturas para armazenar em cada posição a "estrutura matriz" com  
                        // sua rescptiva letra e peso/valor
matriz tabela[3][12] = {{{"q", 1}, {"w", 6}, {"e", 7}, {"r", 6}, {"t", 5}, {"y", 2}, {"u", 3}, {"i", 8}, {"o", 9}, {"p", 4}, {"á", 3}, {"ã", 4}}, 
                        {{"a", 2}, {"s", 5}, {"d", 8}, {"f", 7}, {"g", 4}, {"h", 1}, {"j", 4}, {"k", 7}, {"l", 8}, {"ç", 5}, {"é", 2}, {"í", 3}},
                        {{"z", 3}, {"x", 4}, {"c", 9}, {"v", 8}, {"b", 3}, {"n", 2}, {"m", 5}, {"ó", 6}, {"õ", 7}, {"ô", 6}, {"â", 1}, {"ê", 2}}};