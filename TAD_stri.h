#ifndef str_h
#define str_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct nodoc {
    char c;
    struct nodoc* next;
} tstr;

typedef tstr* str;

str create(); 	// Crea un nodo str vacío ('\0') //

void addstr(str* s, char c); // Agrega un char al final del string //

void tostr(str* s, char* text); //Carga un char* literal en un str //

void elimvocal(str* s); // Elimina todas las vocales del string //

void destroystr(str* s); // Libera toda la memoria del string //

void strcopy(str* d, str s); // Copia el contenido de s al final de d //

bool cmp(str s1, str s2); // Devuelve true si los dos strings son iguales //

char get_char(str s); // Devuelve el char del nodo actual //

void printstr(str s); // Imprime el string con \n al final

void printstr_inline(str s); // Imprime el string sin \n //

str get_next_node(str s); // Devuelve el siguiente nodo //

void printstr_inline(str s); // Imprime el string sin \n //

#endif
