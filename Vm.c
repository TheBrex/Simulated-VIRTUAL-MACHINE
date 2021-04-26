/*COMPONENTE  : MARCO BRESCIANI */
/*NOME GRUPPO : P1G67 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Function.h"



int main(int argc , char **argv) {



	char nomefile[100] = "";                                                                                                /*inizializzazione stringa nome file*/
	int *v = NULL;         																									/*inizilizzazione puntatatore al vettore*/
	int dim = 0;           																									/*inizializzazione variabile contenente la dimensione di v*/
	char scelta=' ';
	if(argc!=3){																											/*controllo se i parametri inseriti da linea di comando sono 3*/
		printf("ERRORE NEI PARAMETRI INSERITI PER L' ESECUZIONE \n");
	
	}
	else{
	strcpy(nomefile, argv[2]); 																								/*copia di argv[2](contenente il nome del file) nella stringa nomefile*/
	printf("<-- MARCO BRESCIANI  matricola: 876743-->\n");
	printf("<-- SIMULAZIONE VIRTUAL MACHINE / PROGETTO C. 2018/2019 --> \n");
	printf("<-- SI RACCOMANDA L'UTILIZZO DI UN FILE CORRETTAMENTE FORMATTATO PER L'ESECUZIONE OTTIMALE DEL CODICE MACCHINA -->\n\n");
	printf("<-- ATTIVARE MODALITA' DEBUG ( COMPRENDE EVENTUALI MESSAGGI DI WARNING E CONTROLLO ) ? Y/N -->");
	scelta=getchar();
	printf("\n");
	
	if (strcmp(argv[1], "stampa")==0) { 																					/*controllo del comando inserito*/
		if (file_exist(nomefile)) { 																						/*verifica esistenza del file*/
			if (scelta == 'Y' || scelta == 'y') {
				printf("message : [ VERIFICA ESISTENZA DEL FILE COMPLETATA ] --> %s \n", nomefile);
			}
			v=read_insert_file(nomefile, v, &dim); 																			/*ritorna il puntatore del vettore contenente le istruzioni*/
			if (v == NULL) {																								/*controllo del puntatore del vettore contenente le istruzioni*/
				printf("error   : [ PROBABILE ERRORE NEL CONTENUTO DEL FILE ] \n");
			}
			else {
				if (dim < check_instruction(v, dim)) {
					printf("error   : [ IL NUMERO DEI PARAMETRI DELLE FUNZIONI NEL FILE NON CORRISPONDE A QUELLO NECESSARIO PER UNA CORRETTA ESECUZIONE ] \n");
					return 0;
				}
				if (dim > check_instruction(v, dim)) {
					if (scelta == 'Y' || scelta == 'y') {
						printf("warning : [ LA DIMENSIONE DEL VETTORE ALLOCATO E' MAGGIORE DI QUELLA NECESSARIA AL PROGRAMMA, POTREBBE CAUSARE MALFUNZIONAMENTO ] \n");
					}
				}
				if (scelta == 'Y' || scelta == 'y') {
					printf("message : [ CARICAMENTO DELLE ISTRUZIONI AVVENUTO ] --> ");
					print_v(v, check_instruction(v, dim));
				}
				printf("STAMPA : \n\n");
				print_machine_code(nomefile, v, dim);																		/*esegue la stampa del codice macchina*/
				free(v); 																									/*pone nuovamente disponibile la memoria allocata da v*/
			}
		}
		else{
			printf("error   : [ CARICAMENTO FILE ISTRUZIONI FALLITO, RICONTROLLARE NOME DEL FILE ] \n");
			return 0;
		}
	}
else{
	if (strcmp(argv[1], "esegui")== 0) {
		if (file_exist(nomefile)) { 																						/*verfica esistenza del file*/
			int stack[16384] = { 0 }; 																						/*inizializzazione dello stack*/
			int reg[32] = { 0 };																							/*inizializzazione dei registri*/
			int IP = 0;																										/*inizializzazione instruction pointer*/
			int SP = 0;																										/*inizializzazione stack pointer*/
			
			if (scelta == 'Y' || scelta == 'y') {
				printf("message : [ VERIFICA ESISTENZA DEL FILE COMPLETATA] --> %s \n", nomefile);
			}
			v = read_insert_file(nomefile, v, &dim);																		/*ritorna il puntatore del vettore contenente le istruzioni*/
			if (v == NULL) { 																								/*se il puntatore è null c'è stato un problema nella gestione del file*/
				printf("error   : [ PROBABILE ERRORE NEL CONTENUTO DEL FILE ] \n");
			}
			else {
				if (dim <= 0) {
					printf("error   : [ DIMENSIONE DICHIARATA NON VALIDA ] \n");
					return 0;
				}
				if (dim < check_instruction(v, dim)) {
					printf("error   : [ IL NUMERO DEI PARAMETRI DELLE FUNZIONI NEL FILE NON CORRISPONDE A QUELLO NECESSARIO PER UNA CORRETTA ESECUZIONE DEL CODICE ] \n");
					return 0;
				}
				if (dim > check_instruction(v, dim)) {
					if (scelta == 'Y' || scelta == 'y') {
						printf("warning : [ LA DIMENSIONE DEL VETTORE ALLOCATO E' MAGGIORE DI QUELLA NECESSARIA AL PROGRAMMA, POTREBBE CAUSARE MALFUNZIONAMENTO ] \n");
					}
				}
				if (scelta == 'Y' || scelta == 'y') {
					printf("message : [ CARICAMENTO DELLE ISTRUZIONI AVVENUTO ] --> ");
					print_v(v, check_instruction(v, dim));
				}
				printf("ESEGUI : \n\n");
				exexute_instruction(v, reg, stack, &IP, &SP, dim); 															/*procede con l'esecuzione del codice macchina*/
				free(v); 																									/*pone nuovamente disponibile la memoria allocata da v*/
			}
		}
		else{
			printf("error   : [ CARICAMENTO FILE ISTRUZIONI FALLITO, RICONTROLLARE NOME DEL FILE ] \n");
			return 0;
		}
	}
	else{
		printf("error   : [ ERRORE PARAMETRO DEL COMANDO ]\n          [formattazione: ./Vm stampa(oppure)esegui nomefile.estensione ] \n");
	}
}
}
return 0;
}

