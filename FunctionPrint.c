/*COMPONENTE  : MARCO BRESCIANI */
/*NOME GRUPPO : P1G67 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Function.h"



int file_exist(char *filename) { /*funzione verifica esistenza del file */

	FILE *fp;                    /*puntatore al file*/
	fp = fopen(filename, "r");   /*apertura del file*/
	if (fp == NULL) {            /*controllo valore del puntatore al file*/
		return 0;
	}
	else {
		fclose(fp);              /*chiusura del file*/
		return 1;
	}
}


void print_machine_code(char *filename, int *v, int dim) {                                             /*funzione di stampa del codice macchina*/

	FILE *f;                                                                                           /*puntatore al file*/
	int k = 0;                                                                                         /*inizializzazione indice ciclo*/
	f = fopen(filename, "r");                                                                          /*apertura del file*/
	

	if (f == NULL) {                                                                                   /*controllo apertura/esistenza del file */
		printf("ERROR \n");
		fclose(f);                                                                                     /*chiusura del file */
		return;
	}
	else {
		for (k = 0; k < dim; k++) {                                                                    /*ciclo per l'interpretazione dal codice macchina al formato [ k] GENERIC_FUNCTION P1 P2 */
			switch (*(v+k)){                                                                           /*switch per interpretare il codice e stampare le funzioni corrispondenti */

				case 0: 
						printf("[ %d]  HALT \n", k);                                           /*0-->HALT */
					break;
				case 1: 
						printf("[ %d]  DISPLAY R%d \n", k, *(v + k + 1));                          /*1-->DISPLAY */
						k++;
					break;
				case 2: 
						printf("[ %d]  PRINT_STACK %d \n", k, *(v + k + 1));                       /*2-->PRINT_STACK */
						k++;
					break;
				case 10: 
						printf("[ %d]  PUSH R%d \n", k, *(v + k + 1));                            /*10-->PUSH */
						k++;
					break;
				case 11: 
						printf("[ %d]  POP R%d \n", k, *(v + k + 1));                             /*11-->POP */
						k++;
					break;
				case 12: 
						printf("[ %d]  MOVE R%d %d \n", k, *(v + k + 1), *(v + k + 2));           /*12-->MOVE */
						k = k + 2;
					break;
				case 20: 
						printf("[ %d]  CALL R%d \n", k, *(v + k + 1));                            /*20-->CALL */
						k++;
					break;
				case 21: 
						printf("[ %d]  RET \n", k);                                               /*21-->RET */
					break;
				case 22: 
						printf("[ %d]  JMP %d \n", k, *(v + k + 1));                              /*22-->JMP */
						k++;
					break;
				case 23: 
						printf("[ %d]  JZ %d \n", k, *(v + k + 1));                               /*23-->JZ */
						k++;
					break;
				case 24: 
						printf("[ %d]  JPOS %d \n", k, *(v + k + 1));                             /*24-->JPOS */
						k++;
					break;
				case 25: 
						printf("[ %d]  JNEG %d \n", k, *(v + k + 1));                             /*25-->JNEG */
						k++;
					break;
				case 30: 
						printf("[ %d]  ADD R%d R%d \n", k, *(v + k + 1), *(v + k + 2));           /*30-->ADD */
						k = k + 2;
					break;
				case 31: 
						printf("[ %d]  SUB R%d R%d \n", k, *(v + k + 1), *(v + k + 2));           /*31-->SUB */
						k = k + 2;
					break;
				case 32: 
						printf("[ %d]  MUL R%d R%d \n", k, *(v + k + 1), *(v + k + 2));           /*32-->MUL */
						k = k + 2;
					break;
				case 33: 
						printf("[ %d]  DIV R%d R%d \n", k, *(v + k + 1), *(v + k + 2));           /*33-->DIV */
						k = k + 2;
					break;

			}
		}
	}
	fclose(f);                                                                                         /*chiusura del file*/
	return;
}