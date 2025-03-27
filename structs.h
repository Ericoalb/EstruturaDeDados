#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct 
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
    int classe;       // 0 materias teorica, 1 materias de calculo e 2 materias de programa
    int pre;          // 1 tem pre-requisito, 0 não tem pre-requisito
    requisitos requi;

}disciplina;

typedef struct 
{
    int periodo[8];
    char cod[10][20];
    float media[20];
    char disc[10][10];

}Aluno;


disciplina quadro[8][5] = {{{"LOGICA PARA COMPUTACAO", "COMP360", 72, "02M34", 0, 0}, {"COMPUTACAO SOCIEDADE E ETICA", "COMP361", 72, "02M56", 0, 0}, {"CALCULO DIFERENCIAL E INTEGRAL", "COMP363", 144, "356T234", 1, 0}, {"PROGRAMAÇAO 1", "COMP359", 72,"06M3456", 2, 0}, {"MATEMÁTICA DISCRETA", "ECOM003", 72, "24M12", 1, 0}},
                               {{"GEOMETRIA ANALITICA", "COMP367", 72, "24M34", 1, 0}, {"BANCO DE DADOS", "COMP365", 72, "35T12", 2, 0}, {"ESTRUTURA DE DADOS", "COMP364", 72, "24T34", 2, 1,"COMP359","*","*",1}, {"ORG. E ARQ. DE COMPUTADORES","COMP366", 72, "24T12", 0, 0}},
                               {{"ALGEBRA LINEAR", "COMP371", 72, "24T34", 0, 1, "COMP367", "*", "*", 1}, {"PROBABILIDADE E ESTATISTICA", "COMP370", 72, "24T12", 0, 1, "COMP363", "*", "*", 1}, {"TEORIA DOS GRAFOS", "COMP369", 72,"25M34", 2, 1, "COMP364", "COMP362","*", 2}, {"REDES DE COMPUTADORES", "COMP368", 72, "34M56", 0, 1, "COMP359", "*", "*", 1}},
                               {{"TEORIA DA COMPUTACAO", "COMP376", 72, "24T12", 0, 0}, {"PROJETO E ANALISE DE ALGORITMOS", "COMP374", 72, "25M56", 2, 1, "COMP364", "COMP369", "*", 2}, {"PROGRAMACAO 3", "COMP373", 72, "34T34", 2, 1, "COMP364", "COMP365", "COMP368", 3}, {"PROGRAMACAO 2", "COMP372", 72, "35T12", 2, 1, "COMP364", "COMP365", "COMP368", 3}},
                               {{"SISTEMAS OPERACIONAIS", "COMP378", 72,"24M34", 0, 1, "COMP366", "*", "*", 1}, {"COMPILADORES", "COMP379", 72, "24M56", 2, 1, "COMP364", "COMP376", "*", 2}, {"INTELIGENCIA ARTIFICIAL", "COMP380", 72, "35M34", 2, 1, "COMP364", "COMP360", "*", 2},{"COMPUTACAO GRAFICA", "COMP381", 72, "36M56", 2, 0}},
                               {{"PROJETO E DESENVOLVIMENTO DE SISTEMAS", "COMP382", 288, "2356T1234", 2, 1,"COMP364","COMP370", "COMP374", 3}},
                               {{"MET. DA PESQ. E DO TRABALHO", "COMP386", 72, "35M34", 0, 0}, {"NOCOES DE DIREITO", "COMP387", 72, "05T1234", 0, 0}}};