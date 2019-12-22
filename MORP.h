#pragma once
#ifndef MORP_H_INCLUDED
#define MORP_H_INCLUDED

#define MAX_PRD 300
#define MAX_PED 250

typedef struct tSolucao {
	int matSol[MAX_PRD][MAX_PED];
	int vetEspLoc[MAX_PED];
	int EspTot;
	double funObj;
}Solucao;

Solucao sol,nsol;
static int numPrd;
static int numPed;
static double tempM;


void lerDados(char* arq);
void mostraDados(char* arq);
void testarDados(char  *arq, Solucao &s);
void EscreveDados(char  *arq, Solucao &s);
void calcFunObj(Solucao &s);
void calcFunObjAdapt(Solucao &s, int Prd);
void mostraSol(Solucao &s);
void clonaSol(Solucao &s, Solucao &s2);
void permutaMatrix(Solucao &s, int col1, int col2);
void permutaMatrixAle(Solucao &s);
void permutaMatrixGul(Solucao &s);
void heuConstAleGul(Solucao &s, int ale);
void heuBLRand(Solucao &s);
void heuBLPM(Solucao &s);
void heuBLMM(Solucao &s);
void SA(double a, int SAmax, double T0, double Tc, Solucao &s);
void GRASP(double tempo_limite, int LRC, Solucao &s);

#endif // !MORP_H_INCLUDED
