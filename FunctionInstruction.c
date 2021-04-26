/*COMPONENTE  : MARCO BRESCIANI */
/*NOME GRUPPO : P1G67 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Function.h"



void print_v(int v[], int dim){
	int i=0;
	for (i = 0; i < dim; i++) {
		printf("[%d]", v[i]);
	}
    printf("\n\n");
}

int copy_string(char *s, char c, int punt) { 				/*funzione per la copia di un carattere in una stringa */

	int success = 0; 										/*flag */
	*(s + punt) = c; 										/*copia del carattere nella pos punt della stringa */
	success = 1;
	return (success == 1) ? 1 : 0;

}

void svuota_stringa(char s[]) { 							/*funzione per lo svuotamento di una stringa */
	int i = 0;
	for (i = 0; s[i] != '\0'; i++) { 						/*sostituisce i caratteri con '\0' */
		s[i] = '\0';										/*per ogni valore della stringa lo sostituisco con '\0'*/
	}
}

int string_is_empty(char s[]) { 							/*controlla se la stringa è vuota */
	if (s[0] == '\0') {
		return 1;
	}
	else
	{
		return 0;
	}
}




int* read_insert_file(char *filename, int *v, int *dim) { /*funzione per la lettura del file e l'inserimento delle istruzioni nel vettore , ritorna il puntatore al vettore */

	FILE *f;                                            /*puntatore al file per la lettura*/
	char s[100] = "";                                   /*stringa per salvataggio dei caratteri utili del file*/
	char crt;	                                        /*variabile che assume il valore dei caratteri del file*/
	int punt = 0;                                       /*indice posizioni stringa*/
	int lung = -1;                                       /* dimensione vettore istruzioni*/	
	int count = 0;                                      /*flag lettura del primo inter*/
	int i = 0;                                          /*contatore degli elementi inseriti nel vettore*/
	int flag = 0;
	f = fopen(filename, "r");                           /*apertura del file*/
	
	if (f == NULL) {			                        /*controllo se il puntatore punta al file*/
		return NULL;			                        /*terminazione della funzione*/
	}
	else {

		while ((crt=getc(f))!=EOF && flag==0){						/*ciclo per la lettura del file*/

			if (crt == ';') {	                        /*controllo del carattere ';'*/
				if (i == (lung)) {                      /*controllo se il commento si trova dopo l'inserimento dell'ultimo valore*/
					while ((crt = getc(f)) != EOF);     /*scorro fino alla fine del file*/
				}
				else {
					while ((crt = getc(f)) != '\n');    /*cicla fino ad un '\0' poichè tutto ciò che si trova dopo, nella la stessa riga è considerato commento */
				}
			}

			if ((crt >= '0' && crt <= '9')|| crt=='-') { /*controllo se quello che sto leggendo è un intero */
				if(crt=='-' && !string_is_empty(s)){
					
				}
				else{
				copy_string(s, crt, punt);              /*copio il carattere nella stringa */
				punt++;                                 /*incremento la posizione per salvare il prossimo carattere */
				if (count == 0) {                       /*imposto il flag per sapere che sto leggendo il primo intero*/
					count = 1;							/*aggiornameto del flag utile per l'allocazione del vettore*/
				}
				}
			}

		    if (crt == '\n' && !string_is_empty(s)) {   /*verifico se siamo su /n per inserire nel vettore delle istruzioni */
				if (count == 1) {                       /*flag di controllo primo intero */
					count=(-1);						    /*aggiorno il flag per non far più diventare la casistica dell'allocazione vera*/
					lung = atoi(s);                     /*traduco la stringa che contiene la dim del vettore in intero */
					if (lung <= 0) {
						flag = 1;
					}
					else{
						v = (int*)malloc(sizeof(int)*lung); /*alloco un array di dimensione lung */
						if(v==NULL){
							flag=1;
						}
					}
					punt = 0;                           /*azzero la posizione per poter scrivere nuovamente dall'inizio nella stringa */
					svuota_stringa(s);                  /*svuoto la stringa per poter salvarci gli atri interi */
				}
				else{
					if((strcmp(s, "-"))!=0){
					v[i] = atoi(s);                     /*inserimento nel vettore */
					punt = 0;                           /*azzero la posizione per poter scrivere nuovamente dall'inizio nella stringa */
					i++;                                /*incremento indice vettore */
					if (i >= (lung)) {                  /*caso in cui siano presenti altri valori dopo l'ultima istruzione utile inserita nel vettore*/
						svuota_stringa(s);				/*svuoto la stringa*/
						while ((crt = getc(f)) != EOF); /*scorro fino alla fine del file*/
					}
				}
				punt = 0;
				}
				svuota_stringa(s);                      /*svuoto la stringa*/
			}
		}

	}
	
    if (!string_is_empty(s)) {                          /*controllo se la stringa è piena una volta uscito dal ciclo, se lo è sulla base del codice scritto sopra sicuramente è l'ultimo valore utile da inserire nel vettore*/
		v[i] = atoi(s);                                 /*inserimento nel vettore */
		svuota_stringa(s);								/*svuoto la stringa*/
	}
	
*dim = lung;                                            /* aggiornamento della dimensione del vettore attraverso puntatore  */
/*printf("i: %d -- dim: %d \n", i, *dim);*/
return v;                                               /* ritorno l'indirizzo del vettore delle istruzioni*/
}