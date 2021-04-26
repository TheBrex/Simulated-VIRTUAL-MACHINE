/*COMPONENTE  : MARCO BRESCIANI */
/*NOME GRUPPO : P1G67 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Function.h"



int HALT() {
	return 1;
}

void DISPLAY(int *v, int reg[], int *IP) {											    /*funzione DISPLAY*/
	
	printf("R%d : %d \n",*(v+(*IP) + 1) ,reg[*(v + (*IP) + 1)]);                                             /*stampa il parametro della funzione display, contenuto nella posizione successiva del vettore */
	(*IP)++;																		    /*aggiornamento instruction pointer */
	return;
}

void PRINTSTACK(int *v, int stack[], int *SP, int *IP) {							   /*funzione PRINTSTACK*/
	
	int i = 0;
	int Npos=*(v+(*IP+1)); 															   /*aquisizione parametro 1 funzione */
	(*IP)++;																		   /*aggiornamento instruction pointer */
	printf("PRINTSTACK: \n");
	if(((*SP)-Npos)<0){																   /*controlla che i valori scelti da visualizzare nel programma siamo possibili*/
		printf("error: [ ELEMENTI DELLO STACK NON SUFFICENTI ] \n");
		printf("\n");
	}
	else{
		for (i = 0; i < Npos; i++) { 												   /*ciclo che scorre lo stack dall' ultima pos dello stack - parametro della funzione*/ 
			printf("%d)stack[%d] = %d  ", i+1 ,*SP - i-1 , stack[*SP -1 - i]); 		   /*stampa elementi stack*/
		}
		printf("\n");
	}
	return;
}

int PUSH(int *v, int reg[] ,int stack[] ,int *IP, int *SP ) {							/*funzione PUSH*/

	if ((*SP) < 16384){ 																/*verifica se è disponibile spazio nello stack */
	int elem = *(v + (*IP + 1)); 														/*aquisizione parametro 1 funzione */
	(*IP)++;																			/*aggiornamento instruction pointer */
	stack[*SP] = reg[elem];																/*(stack + (*SP)) = Elem; */
	(*SP)++; 																			/*aggiornamento stack pointer */
	return 1; 																			/* elemento inserito */
	}
	else{
		return 0; 																		/* stack pieno */
	} 
}

int POP( int *v ,int stack[],int reg[], int *IP ,int *SP) {								/*funzione POP*/

	if((*SP)<1){																		/*verifica se lo stack è vuoto */
		return 0; 																		/*pop da stack vuoto */
	}
	else {
		int Nreg = *(v + (*IP + 1)); 													/*aquisizione parametro 1 funzione */
		(*SP)--;																		/*aggiornamento stack pointer */
		(*IP)++;
		reg[Nreg] = stack[*SP];															/*<--Il valore di v o di stack?? */
		return 1;																		/*pop da stack con almeno un elemento */
	}
}

void MOV(int *v, int reg[], int *IP) {													/*funzione MOV*/
	
	int elem = *(v + (*IP) + 2);														/*aquisizione parametro 1 funzione */
	reg[*(v + (*IP) + 1)] = elem; 														/* parametro 1--> registro in cui copiare */
	(*IP) = *IP + 2;																	/*aggiornamento instruction pointer di 2 poichè i parametri per MOV sono 2 */
	/*return 1; */
	return;
}

void CALL(int *v, int stack[], int *IP, int *SP ) { 									/*funzione CALL*/
	stack[*SP] = *IP + 2;																/*salva l'IP da dove deve riprendere terminata la subroutine nello stack */
	(*SP)++; 																				/*aggiornamento stack pointer */
	*IP = *(v + *IP+1);																	/*jump alla posizione indicata*/
	return;
}


int RET( int stack[], int *IP, int *SP) {         										/*funzione RET*/ 
	if((*SP)>0){																		/*controlla se ci sia almeno un elemento nello stack*/
	*IP = stack[*SP - 1];																/*aggiorna l'IP counter al valore che tecnicamente dovrebbe raprresentare l'indice da cui riprendere dopo la chiamata alla subroutine*/
	(*SP)--;																			/*aggiornamento stack pointer */
	return 1;
	}
	else{
		return 0;
	}
}


void JMP(int *v, int *IP) {																/*funzione JMP*/

	int elem = *(v + (*IP) + 1); 														/*aquisizione parametro 1 funzione */
	*IP = elem;																			/*aggiornamento instruction pointer */
	/*return 1; */
	return;
}

void JZ(int *v,int stack[] ,int *IP, int *SP) {											/*funzione JZ*/
	
	int elem = *(v + (*IP) + 1); 														/*aquisizione parametro 1 funzione */

	if (stack[(*SP) - 1] == 0) {														/*controllo se ultimo valore dello stack è uguale a 0*/
		*IP = elem-1;																	/*aggiornamento instruction pointer ad una posizione in meno, che diventerà quella corretta non appena il ciclo incrementerà IP*/
		/*return 1; */
	}
	else{
		(*IP)++;																		/*aggiornamento instruction pointer */
	}
	(*SP)--;																			/*aggiornamento stack pointer */
	/*else return 0; */
	return;
}

void JPOS(int *v, int stack[], int *IP, int *SP) {										/*funzione JPOS*/

	int elem = *(v + (*IP) + 1);														/*aquisizione parametro 1 funzione */

	if (stack[(*SP) - 1] > 0) {
		
		*IP = elem-1;																	/*aggiornamento instruction pointer ad una posizione in meno, che diventerà quella corretta non appena il ciclo incrementerà IP*/
		/*return 1;*/
	}
	else{
		(*IP)++;																		/*aggiornamento instruction pointer */
	}
	(*SP)--;																			/*aggiornamento stack pointer */
	/*else return 0;*/
	return;
}

void JNEG(int *v, int stack[], int *IP, int *SP) {										/*funzione JNEG*/

	int elem = *(v + (*IP) + 1); 														/*aquisizione parametro 1 funzione */

	if (stack[(*SP) - 1] < 0) {
		
		*IP = elem-1;																	/*aggiornamento instruction pointer ad una posizione in meno, che diventerà quella corretta non appena il ciclo incrementerà IP*/
		/*return 1;*/
	}
	else{
		(*IP)++;																		/*aggiornamento instruction pointer */
	}
	(*SP)--;																			/*aggiornamento stack pointer */
	
	/*else return 0;*/
	return;
}

int ADD(int *v, int stack[], int reg[], int *IP, int *SP) {								/*funzione ADD*/

	int elem1 = reg[*(v + (*IP) + 1)]; 													/*aquisizione parametro 1 funzione */
	/*printf("ADD elem1 %d ", elem1);*/
	int elem2 = reg[*(v + (*IP) + 2)];													/*aquisizione parametro 2 funzione */
	/*printf("elem2 %d ", elem2);*/
	long int somma =  elem1 + elem2;															/*somma dei due parametri */
	*(IP) = (*IP) + 2;																	/*aggiornamento instruction pointer */
	if (somma>= (-2147483647) && somma <= 2147483647) {									/*controllo overflow della somma*/
		if (*SP < 16384) {																/*controllo disponibilità dello stack */
			stack[*SP] = somma;															/*inserimento nello stack */
			(*SP)++;																	/*aggiornamento stack pointer */
			return 1;
		}
		else {
			return 0;
		}
	}
	else{
		return -1;
	}
}

int SUB(int *v, int stack[], int reg[], int *IP, int *SP) {								/*funzione SUB*/

	int elem1 = reg[*(v + (*IP) + 1)]; 													/*aquisizione parametro 1 funzione */
	int elem2 = reg[*(v + (*IP) + 2)];													/*aquisizione parametro 2 funzione */
	long int sottr = elem1 - elem2;								/*sottrazione dei due parametri */
	*(IP)=(*IP)+2;																		/*aggiornamento instruction pointer */
	if (sottr >= (-2147483647) && sottr <= 2147483647) {								/*controllo overflow della sottrazione*/
		if (*SP < 16384) {																/*controllo disponibilità dello stack */
			stack[*SP] = sottr;															/*inserimento nello stack */
			(*SP)++;																	/*aggiornamento stack pointer */
			return 1;
		}
		else {
			return 0;
		}
	}
	else {
		return -1;
	}
}

int MUL(int *v, int stack[], int reg[], int *IP, int *SP) {								/*funzione MUL*/

	int elem1 = reg[*(v + (*IP) + 1)]; 													/*aquisizione parametro 1 funzione */
	int elem2 = reg[*(v + (*IP) + 2)];													/*aquisizione parametro 2 funzione */
	long int molt = elem1 * elem2;															/*moltiplicazione dei due parametri */
	*(IP) = (*IP) + 2;																	/*aggiornamento instruction pointer */
	if (molt >= (-2147483647) && molt <= 2147483647) {									/*controllo overflow della moltiplicazione*/
		if (*SP < 16384) {																/*controllo disponibilità dello stack */
			stack[*SP] = molt;															/*inserimento nello stack */
			(*SP)++;																	/*aggiornamento stack pointer */
			return 1;
		}
		else {
			return 0;
		}
	}
	else {
		return -1;
	}
}

int DIV(int *v, int stack[], int reg[], int *IP, int *SP) {								/*funzione DIV*/

	int elem1 = reg[*(v + (*IP) + 1)];													/*aquisizione parametro 1 funzione */
	int elem2 = reg[*(v + (*IP) + 2)];													/*aquisizione parametro 2 funzione */
	int div=0;
	if (elem2 == 0) {																	/*controllo se il parametro che divide il primo è uguale a zero*/
		return 0; 
	}
	else {
		div = elem1 / elem2;															/*rapporto dei due parametri */
	}
	*(IP) = (*IP) + 2;																	/*aggiornamento instruction pointer */
	if (div >= (-2147483647) && div <= 2147483647) {									/*controllo overflow della divisione*/
		if (*SP < 16384) { 																/*controllo disponibilità dello stack */
			stack[*SP] = div; 															/*inserimento nello stack */
			(*SP)++;																	/*aggiornamento stack pointer */
			return 1;
		}
		else {
			return 0;
		}
	}
	else {
		return -1;
	}
}

