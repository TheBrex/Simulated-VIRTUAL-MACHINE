/*COMPONENTE  : MARCO BRESCIANI */
/*NOME GRUPPO : P1G67 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Function.h"



int check_instruction(int *v, int dim) {
	int i = 0;
	int count = 0;
	for (i = 0; i < dim; i++) {
		switch (*(v+i))
		{
		case 0:
			count = count + 1;
			break;
		case 1:
			count = count + 2;
			i++;
			break;
		case 2:
			count = count + 2;
			i++;
			break;
		case 10:
			count = count + 2;
			i++;
			break;
		case 11:
			count = count + 2;
			i++;
			break;
		case 12:
			count = count + 3;
			i=i+2;
			break;
		case 20:
			count = count + 2;
			i++;
			break;
		case 21:
			count = count + 1;
			break;
		case 22:
			count = count + 2;
			i++;
			break;
		case 23:
			count = count + 2;
			i++;
			break;
		case 24:
			count = count + 2;
			i++;
			break;
		case 25:
			count = count + 2;
			i++;
			break;
		case 30:
			count = count + 3;
			i = i + 2;
			break;
		case 31:
			count = count + 3;
			i = i + 2;
			break;
		case 32:
			count = count + 3;
			i = i + 2;
			break;
		case 33:
			count = count + 3;
			i = i + 2;
			break;
		}

	}
	return count;
}


void exexute_instruction(int *v, int reg[], int stack[], int *IP, int *SP, int dim) { /*FUNZIONE DI ESECIZIONE DEL CODICE MACCHINA */
	
	int flag_uscita = 0;                                                             /* inizializzazione del flag utile per uscire dal ciclo */
	for ((*IP) = 0; (*IP) <dim && flag_uscita==0; (*IP)++) {                         /*scorre il vettore v(contenente le istruzioni fino allo 0 che corrisponde ad HALT) */
		
		switch (*(v + *IP)) {
		case 0: 
			flag_uscita = HALT();                                                  /*chiama la funzione HALT aggiornando il flag d uscita*/
			printf("[ PROGRAMMA TERMINATO ] \n");
			printf("\n");
			break;
		case 1:
			if (*(v + ((*IP) + 1)) > 31) {
				printf("error-DISPLAY: [ REGISTRO FUORI INTERVALLO 0-31 ] \n");
				flag_uscita = 1;
			}
			else {
				DISPLAY(v, reg, IP);                                                     /* chiama la funzione DISPLAY */
			}
				break;
		case 2:
			PRINTSTACK(v, stack, SP, IP);                                            /* chiama la funzione PRINTSTACK */
				break;
		case 10:
			if (*(v + ((*IP) + 1)) > 31) {
				printf("error-PUSH: [ REGISTRO FUORI INTERVALLO 0-31 ] \n");
				flag_uscita = 1;
			}
			else {
				if (!PUSH(v, reg, stack, IP, SP)) {                                       /* chiama la funzione PUSH */
					printf("error-PUSH: [ STACK OVERFLOW ] \n");
					flag_uscita = 1;                                                     /* aggiornamento flag di uscita dal ciclo */
				}
			}
			break;
		case 11:
			if (*(v + ((*IP) + 1)) > 31) {
				printf("error-POP: [ REGISTRO FUORI INTERVALLO 0-31 ] \n");
				flag_uscita = 1;
			}
			else {
				if (!POP(v, stack, reg, IP, SP)) {                                        /* chiama la funzione POP */
					printf("error-POP: [ STACK UNDERFLOW ] \n");
					flag_uscita = 1;													 /* aggiornamento flag di uscita dal ciclo */
				}
			}
			break;
		case 12:
			if (*(v + ((*IP) + 1)) > 31) {
				printf("error-MOV: [ REGISTRO FUORI INTERVALLO 0-31 ] \n");
				flag_uscita = 1;
			}
			else {
				MOV(v, reg, IP);                                                         /* chiama la funzione MOV */
			}
			break;
		case 20:
			CALL(v, stack, IP, SP);                                                     /* chiama la funzione CALL */
				(*IP)--;
				break;
		case 21:
			if (!RET(stack, IP, SP)) {                                                   /* chiama la funzione RET */
				flag_uscita = 1;                                                       /* aggiornamento flag di uscita dal ciclo */
				printf("error-RET: [ UNDERFLOW DELLO STACK ] \n");
			}
			(*IP)--;
			break;
		case 22:
			JMP(v, IP);                                                              /* chiama la funzione JMP */
			(*IP)--;
			break;
		case 23:
			JZ(v, stack, IP, SP);                                                    /* chiama la funzione JZ */
			break;
		case 24:
			JPOS(v, stack, IP, SP);                                                  /* chiama la funzione JPOS */
			break;
		case 25:
			JNEG(v, stack, IP, SP);                                                  /* chiama la funzione JNEG */
			break;
		case 30:
			if (*(v + ((*IP) + 1)) > 31 || *(v + ((*IP) + 1)) < 0 || *(v + ((*IP) + 2)) > 31 || *(v + ((*IP) + 2)) < 0) {
				printf("error-ADD: [ REGISTRO/I FUORI INTERVALLO 0-31 ] \n");
				flag_uscita = 1;
			}
			else {
				if (ADD(v, stack, reg, IP, SP)) {                                        /* chiama la funzione ADD e controlla se genera overflow nello stack */
					/*printf("SOMMA INSERITA NELLO STACK \n");<--printf di prova */
				}
				else {
					printf("error-ADD: [ OVERFLOW STACK INSERIMENTO SOMMA ] \n");
					flag_uscita = 1;                                                       /* aggiornamento flag di uscita dal ciclo */
				}
			}
			break;
		case 31:
			if (*(v + (*IP + 1)) > 31 || *(v + (*IP + 1)) < 0 || *(v + (*IP + 2)) > 31 || *(v + (*IP + 2)) < 0) {
				printf("error-SUB: [ REGISTRO/I FUORI INTERVALLO 0-31 ] \n");
				flag_uscita = 1;
			}
			else {
				if (SUB(v, stack, reg, IP, SP)) {                                        /* chiama la funzione SUB e controlla se genera overflow nello stack */
					/*printf("SUB INSERITA NELLO STACK \n");<--printf di prova */
				}
				else {
					printf("error-SUB: [ OVERFLOW STACK INSERIMENTO SUB ] \n");
					flag_uscita = 1;                                                     /* aggiornamento flag di uscita dal ciclo */
				}
			}
			break;
		case 32:
			if (*(v + (*IP + 1)) > 31 || *(v + (*IP + 1)) < 0 || *(v + (*IP + 2)) > 31 || *(v + (*IP + 2)) < 0) {
				printf("error-MUL: [ REGISTRO/I FUORI INTERVALLO 0-31 ] \n");
				flag_uscita = 1;
			}
			else {
				if (MUL(v, stack, reg, IP, SP)) {                                          /* chiama la funzione MUL e controlla se genera overflow nello stack */
					/*printf("MUL INSERITA NELLO STACK \n");<--printf di prova */
				}
				else {
					printf("error-MUL: [ OVERFLOW STACK INSERIMENTO MUL ] \n");
					flag_uscita = 1;                                                    /* aggiornamento flag di uscita dal ciclo */
				};
			}
			break;
		case 33:
			if (*(v + (*IP + 1)) > 31 || *(v + (*IP + 1)) < 0 || *(v + (*IP + 2)) > 31 || *(v + (*IP + 2)) < 0) {
				printf("error-DIV: [ REGISTRO/I FUORI INTERVALLO 0-31 ] \n");
				flag_uscita = 1;
			}
			else {
				if (DIV(v, stack, reg, IP, SP)) {                                         /* chiama la funzione DIV e controlla se genera overflow nello stack */
					/*printf("DIV INSERITA NELLO STACK \n");<--printf di prova */

				}
				else {
					printf("error-DIV: [ OVERFLOW STACK INSERIMENTO DIV ] \n");
					flag_uscita = 1;                                                    /* aggiornamento flag di uscita dal ciclo */
				};
				break;
			}
		}
	}
}
