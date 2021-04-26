/*COMPONENTE  : MARCO BRESCIANI */
/*NOME GRUPPO : P1G67 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>



/*RIEMPIMENTO VETTORE ISTRUZIONI*/
/*--------------------------------------*/
void print_v(int v[], int dim);
int copy_string(char *s, char c, int punt);
void svuota_stringa(char s[]);
int string_is_empty(char s[]);
int* read_insert_file(char *filename, int *v, int *dim);
/*--------------------------------------*/

/*FUNZIONE DI STAMPA*/
/*--------------------------------------*/
void print_machine_code(char *filename, int *v, int dim);
int file_exist(char *filename);
/*--------------------------------------*/

/*FUNZIONI DI ESECUZIONE*/
/*--------------------------------------*/
int HALT();
void DISPLAY(int *v, int reg[], int *IP);
void PRINTSTACK(int *v, int stack[], int *SP, int *IP);
int PUSH(int *v, int reg[] ,int stack[], int *IP, int *SP);
int POP(int *v, int stack[], int reg[], int *IP, int *SP);
void MOV(int *v, int reg[], int *IP);
void CALL(int *v, int stack[], int *IP, int *SP);
int RET( int stack[], int *IP, int *SP);
void JMP(int *v, int* IP);
void JZ(int *v, int stack[], int *IP, int *SP);
void JPOS(int *v, int stack[], int *IP, int *SP);
void JNEG(int *v, int stack[], int *IP, int *SP);
int ADD(int *v, int stack[], int reg[], int *IP, int *SP);
int SUB(int *v, int stack[], int reg[], int *IP, int *SP);
int MUL(int *v, int stack[], int reg[], int *IP, int *SP);
int DIV(int *v, int stack[], int reg[], int *IP, int *SP);
int check_instruction(int *v, int dim);
void exexute_instruction(int* v, int reg[], int stack[], int *IP, int *SP, int dim);
/*--------------------------------------*/