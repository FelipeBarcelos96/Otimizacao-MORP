// Minimização do Espalhamento de Ordens.cpp : define o ponto de entrada para o aplicativo do console.//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cstring>
#include "stdafx.h"
#include "MORP.h"
#include <cstdio>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
//#define DBG
//#define TEMPMELHOR
//#define DBG2

int main()
{
	clock_t h;
	double tempo;
	srand(time(NULL));
	char aux[50] = "wli.txt";
	lerDados(aux);
	//char aux1[50] = "w1T.txt"; //descomentar no uso de .bat
	//testarDados(aux1); 
	calcFunObj(sol);
	mostraSol(sol);
	
	h = clock();

	//permutaMatrixAle(sol);
	//permutaMatrixGul(sol);
	//calcFunObj(sol);
	//heuConstAleGul(sol, 3);
	//heuBLRand(sol);
	//heuBLPM(sol);
	//heuBLMM(sol);
    //SA(0.975, 2 * (numPrd*(numPed + 1)), 100, 0.01, sol);
	GRASP(10.0, 5, sol);
	mostraSol(sol);
	h = clock() - h;
	tempo = ((double)h) / CLOCKS_PER_SEC;
	//EscreveDados(aux1, sol); //descomentar no uso de .bat
	printf("\nEncontrou melhor em %.2f segundos", tempM);
	printf("\n");
	printf("Tempo de Execucao: %.2f\n", tempo);
	system("Pause");
    return 0;
}

void lerDados(char* arq) {
	FILE *f = fopen(arq, "r");
	fscanf(f, "Not an original instance. This line added and matrix changed to binary.%d %d", &numPed, &numPrd);
	for (int i = 0; i < numPed; i++) {
		for (int j = 0; j < numPrd; j++) {
			fscanf(f, "%d", &sol.matSol[j][i]);
		}
	}

	fclose(f);
}

void mostraDados(char* arq) {
	FILE *f = fopen(arq, "r");
	printf("%d %d \n", numPed, numPrd);
	for (int i = 0; i < numPed; i++) {
		for (int j = 0; j < numPrd; j++) {
			printf("%d ", sol.matSol[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
	fclose(f);
}

void testarDados(char  *arq, Solucao &s) {
	FILE *f;
	if (arq == "")
		f = stdout;
	else
		f = fopen(arq, "w");
	fprintf(f, "%d %d\n", numPed, numPrd);
	for (int i = 0; i < numPed; i++) {
		for (int j = 0; j < numPrd; j++) {
			fprintf(f, "%d ", s.matSol[j][i]);
		}
		fprintf(f, "\n");
	}
	fprintf(f, "\n");
	fprintf(f, "\nVetor de espacamento local: ");
	for (int i = 0; i < numPed; i++)
		fprintf(f, "%d ", s.vetEspLoc[i]);
	fprintf(f, "\n\n");
	fprintf(f, "Media de espalhamento dos pedidos: %.2f \n", s.funObj);
	fprintf(f, "\n");
	if (arq != "")
		fclose(f);
}

void EscreveDados(char  *arq, Solucao &s) {
	FILE *f;
	if (arq == "")
		f = stdout;
	else
		f = fopen(arq, "a");

	fprintf(f, "Espacamento Total: %d    Tempo: %.2f \n", s.EspTot, tempM);
	if (arq != "")
		fclose(f);
}

void calcFunObj(Solucao &s) {
	int priUm;
	int ultUm;
	int vetEspLoc[MAX_PED];

	for (int i = 0; i < numPed; i++) {
		priUm = -1;
		for (int j = 0; j < numPrd; j++) {
			if (s.matSol[j][i] == 1) {
				if (priUm == -1) {
					priUm = j + 1;
				}
				ultUm = j + 1;
			}

		}
		if (priUm != -1) {
			vetEspLoc[i] = (ultUm - priUm);
		}
		else
		{
			vetEspLoc[i] = 0;
		}
	}
	memcpy(&s.vetEspLoc, &vetEspLoc, sizeof(vetEspLoc));

	double espTot;
	espTot = 0;

	for (int i = 0; i < numPed; i++)
		espTot = espTot + vetEspLoc[i];

	s.funObj = (espTot / numPed);
	s.EspTot = espTot;

}

void mostraSol(Solucao &s) {
	printf("\n\n");
	printf("%d %d \n", numPed, numPrd);
	for (int i = 0; i < numPed; i++) {
		for (int j = 0; j < numPrd; j++) {
			printf("%d ", s.matSol[j][i]);
		}
		printf("\n");
	}
	printf("\n");
	printf("\nVetor de espacamento local: ");
	for (int i = 0; i < numPed; i++)
		printf("%d ", s.vetEspLoc[i]);
	printf("\n\n");
	printf("Espacamento Total: %d", s.EspTot);
	printf("\n\n");
	printf("Media de espalhamento dos pedidos: %.2f \n", s.funObj);
	printf("\n");
}

void clonaSol(Solucao &s, Solucao &s2) {
	memcpy(&s2, &s, sizeof(s));
}

void permutaMatrix(Solucao &s, int col1, int col2) {
	int auxi[MAX_PED];
	if (col1 != col2) {
		memcpy(&auxi, &s.matSol[col1], sizeof(s.matSol[col1]));
		memcpy(&s.matSol[col1], &s.matSol[col2], sizeof(s.matSol[col2]));
		memcpy(&s.matSol[col2], &auxi, sizeof(auxi));
	}
}

void permutaMatrixAle(Solucao &s) {
	int col1;
	int col2;
	col1 = rand() % (numPrd-1);
	col2 = rand() % (numPrd-1);

	if (col1 == col2) {
		while (col1 == col2)
		{
			col2 = rand() % (numPrd-1);
		}
	}

	permutaMatrix(s, col1, col2);
	
}

void permutaMatrixGul(Solucao &s) {
	int aux = 0;
	int col1, col2, flag, flag2, flag3;
	flag = 0;
	flag2 = 0;
	flag3 = 0;
	for (int i = 1; i < numPed; i++)
		if (s.vetEspLoc[i] > s.vetEspLoc[aux])
			aux = i; // Guarda o Pedido com maior espalhamento Local

	for (int i = 0; i < numPrd; i++) {
		if (s.matSol[i][aux] == 0 and flag == 1 and flag2 == 0) {
			col1 = i; //Guarda posiçao do Primeiro zero depois de ter visto o primeiro 1
			flag2 = 1;
		}
		if (s.matSol[i][aux] == 1 and flag == 1) {
			col2 = i; // Guarda a posição do ultimo um do Pedido
			flag3 = 1; //Identifica que houve um ultimo um visto e que este é diferente do primeiro em posição
		}
		if (s.matSol[i][aux] == 1 and flag == 0)
			flag = 1; //Identifica o primeiro um Visto
	}
	if (flag3 != 1)
		col2 = col1;

	if (flag == 1)
	permutaMatrix(s, col1, col2);
			
}

void heuConstAleGul(Solucao &s, int ale) {
	Solucao solAux;
	int col,flag, Mcol, MFO;
	int vetAux[MAX_PRD];
	memset(&vetAux, 0, sizeof(vetAux));

	for (int i = 0; i < ale; i++) {
		do{
			flag = 0;
			col = rand() % numPrd;
			if (vetAux[col] == 1)
				flag = 1;
			if (vetAux[col] == 0) {
				vetAux[col] = 1;
				memcpy(&solAux.matSol[i], &s.matSol[col], sizeof(s.matSol[col]));
			}
		} while (flag != 0);
	}
	calcFunObjAdapt(solAux, ale);
#ifdef DBG
	printf("Media de espalhamento dos pedidos: %.2f \n", solAux.funObj);
	printf("\n");
#endif
	for (int i = 0; i < (numPrd-ale); i++) {
		MFO = INT_MAX;
		for (int j = 0; j < numPrd; j++) {
			if (vetAux[j] == 0) {
				memcpy(&solAux.matSol[ale + i], &s.matSol[j], sizeof(s.matSol[j]));
				calcFunObjAdapt(solAux, (ale + i + 1));
				if (solAux.funObj < MFO) {
					MFO = solAux.funObj;
					Mcol = j;
				}
			}
		}
		vetAux[Mcol] = 1;
		memcpy(&solAux.matSol[ale + i], &s.matSol[Mcol], sizeof(s.matSol[Mcol]));
		calcFunObjAdapt(solAux, (ale + i + 1));
#ifdef DBG
		printf("Media de espalhamento dos pedidos: %.2f \n", solAux.funObj);
		printf("\n");
#endif
	}
	memcpy(&s, &solAux, sizeof(solAux));
}

void calcFunObjAdapt(Solucao &s, int Prd) {
	int priUm;
	int ultUm;
	int vetEspLoc[MAX_PED];

	for (int i = 0; i < numPed; i++) {
		priUm = -1;
		for (int j = 0; j < Prd; j++) {
			if (s.matSol[j][i] == 1) {
				if (priUm == -1) {
					priUm = j + 1;
				}
				ultUm = j + 1;
			}

		}
		if (priUm != -1) {
			vetEspLoc[i] = (ultUm - priUm);
		}
		else
		{
			vetEspLoc[i] = 0;
		}
	}
	memcpy(&s.vetEspLoc, &vetEspLoc, sizeof(vetEspLoc));

	double espTot;
	espTot = 0;

	for (int i = 0; i < numPed; i++)
		espTot = espTot + vetEspLoc[i];

	s.funObj = (espTot / numPed);

}

 void heuBLRand(Solucao &s) {
	Solucao solAux;
	memcpy(&solAux.matSol, &s.matSol, sizeof(s.matSol));
	int flag;
	while (true) {
		flag = 0;
		for (int i = 0; i < 2 * (numPrd*(numPed + 1)); i++) {
			permutaMatrixAle(solAux);
			calcFunObj(solAux);
			if (solAux.funObj < s.funObj) {
				memcpy(&s, &solAux, sizeof(solAux));
				flag = 1;
				break;
			}
			else
				memcpy(&solAux, &s, sizeof(s));
		}
		if (!flag)
			break;
	}
} 

 void heuBLPM(Solucao &s) {
	 Solucao solAux;
	 memcpy(&solAux.matSol, &s.matSol, sizeof(s.matSol));
	 int flag, col1, col2;
	
		 flag = 0;
		
			 for (int i = 0; i < numPrd; i++) {
				 for (int j = 0; j < numPrd; j++) {
					 col1 = i;
					 col2 = j;
					 if (solAux.matSol[col1] != solAux.matSol[col2]) {
						 permutaMatrix(solAux, col1, col2);
						 calcFunObj(solAux);
						 if (solAux.funObj < s.funObj) {
							 memcpy(&s, &solAux, sizeof(solAux));
							 flag = 1;
							 break;
						 }
						 else
							 memcpy(&solAux, &s, sizeof(s));
					 }
				 }
				 if (flag = 1)
					 break;
			 }
 }

 void heuBLMM(Solucao &s) {
	 Solucao solAux;
	 memcpy(&solAux.matSol, &s.matSol, sizeof(s.matSol));
	 int flag, col1, col2, Mcol1, Mcol2;
	 double MFO = s.funObj;
	 Mcol1 = -1;
	 Mcol2 = -1;
	 while (true) {
		 flag = 0;
		 for (int i = 0; i < numPrd; i++) {
			 col1 = i;
			 for (int j = 0; j < numPrd; j++) {
				 col2 = j;
				 if (solAux.matSol[col1] != solAux.matSol[col2]) {
					 permutaMatrix(solAux, col1, col2);
					 calcFunObj(solAux);
					 if (solAux.funObj < MFO) {
						 Mcol1 = i;
						 Mcol2 = j;
						 MFO = solAux.funObj;
						 flag = 1;
					 }
					 memcpy(&solAux, &s, sizeof(s));
				 }
			 }
		 }

		 if (MFO < s.funObj) {
			 permutaMatrix(s, Mcol1, Mcol2);
			 calcFunObj(s);
		 }
		 if (!flag)
			 break;
	 }
 }

 void SA(double a, int SAmax, double T0, double Tc, Solucao &s) {
	 Solucao MSol;
	 memcpy(&MSol, &s, sizeof(s));
	 double T = T0, delta, X;
	 Solucao solAux;
	 clock_t t, x;
	 x = clock();

	 int col1, col2;
	 while (T > Tc)
	 {
		 for (int IterT = 0; IterT < SAmax; IterT++) {
			 col1 = rand() % numPrd;
			 do
				 col2 = rand() % numPrd;
			 while (col2 == col1);

			 memcpy(&solAux, &s, sizeof(s));
			 permutaMatrix(solAux, col1, col2);
			 calcFunObj(solAux);
			 delta = s.funObj - solAux.funObj;
			 if (delta > 0) {
				 memcpy(&s, &solAux, sizeof(solAux));
				 if (solAux.funObj < MSol.funObj) {
					 memcpy(&MSol, &solAux, sizeof(solAux));
					 printf("melhora: %d\n", MSol.EspTot);
					 t = clock() - x;
					 tempM = ((double)t) / CLOCKS_PER_SEC;
				 }

			 }
			 else {
				 X = rand() % 101;
				 X = X / 100.0;
				 if (X < exp((delta) / T))
					 memcpy(&s, &solAux, sizeof(solAux));
			 }
		 }
		 T = T * a;
	 }
	 memcpy(&s, &MSol, sizeof(MSol));
 }

 void GRASP(double tempo_limite, int LRC, Solucao &s) {
	 Solucao MSol;
	 MSol.funObj = INT_MAX;
	 clock_t x, t;
	 double temp;
	 x = clock();
	 t = clock() - x;
	 temp = ((double)t) / CLOCKS_PER_SEC;
	 while (temp <= tempo_limite) {
		 heuConstAleGul(s, LRC);
		 heuBLMM(s);
		 if (s.funObj < MSol.funObj) {
			 memcpy(&MSol, &s, sizeof(s)); 
		     printf("melhora: %d \n", MSol.EspTot);
			 t = clock() - x;
			 tempM = ((double)t) / CLOCKS_PER_SEC;
		 }

		 t = clock() - x;
		 temp = ((double)t) / CLOCKS_PER_SEC;
	 }
	 if (MSol.funObj < s.funObj)
		 memcpy(&s, &MSol, sizeof(MSol));
 }

