#ifndef DATATYPE_H
#define DATATYPE_H

#include "TAD_stri.h"


#define STR 1
#define SET 2
#define LIST 3

typedef struct datatype* tdata;

struct datatype {
    int nodetype;
    union {
        str string;
        struct {
            struct datatype* data;
            struct datatype* next;
        };
    };
};

tdata create_str_ast(); // Crea un nodo de tipo STR vacío //

tdata create_list(); // Crea una LIST vacía //

tdata create_set();	 // Crea un SET vacío //

bool cmpstr(tdata,tdata); // Compara dos nodos STR //

tdata concatstr(tdata,tdata); // Concatena dos STR en uno nuevo //

tdata clonar(tdata ori); // Copia profunda de cualquier tdata //

void append(tdata* list, tdata elem); // Agrega un elemento al final de una LIST o SET //

int length(tdata list); // Cuenta los elementos de una LIST o SET //

tdata copy_list(tdata list); // Copia profunda de una LIST o SET //

tdata concat(tdata l1, tdata l2); // Concatena dos LIST/SET en uno nuevo //

bool twins(tdata a, tdata b); // Devuelve true si dos tdata son estructuralmente iguales //

bool search(tdata list, tdata c); // Busca un elemento en una LIST o SET //

void insert_set(tdata* s, tdata e); // Inserta en un SET solo si no existe //

bool belongs(tdata s, tdata e); // Devuelve true si el elemento está en el SET o LIST //

void destroy(tdata x); // Libera toda la memoria de un tdata recursivamente //

void remove_set(tdata* s, tdata e); // Elimina un elemento de un SET //

tdata union_set(tdata A, tdata B); // Unión de dos SET //

tdata intersection_set(tdata A, tdata B); // Intersección de dos SET //

tdata difference_set(tdata A, tdata B); // Diferencia a - b entre dos SET //

bool subset(tdata A, tdata B); // Devuelve true si b es subconjunto de a //

bool equals_set(tdata A, tdata B); // Devuelve true si los dos SET son iguales //

tdata producto_cartesiano(tdata a, tdata b); // Devuelve el conjunto de pares (x, y) con x e A, y e B //

tdata str_to_list(tdata s); // Convierte un STR en una LIST de caracteres //

tdata to_str(tdata n); // Serializa cualquier tdata a su representación como STR //

void print_data(tdata); // Imprime cualquier tdata recursivamente //

tdata make_str(const char* text); // Crea un STR desde un char* literal //



#endif
