#include "TAD_stri.h"

str create() {
    str new = (str)malloc(sizeof(tstr));
    if (new != NULL) {
        new->c = '\0';
        new->next = NULL;
    }
    return new;
}

void addstr(str* s, char c) {
    if (*s == NULL) {
        *s = create();
        (*s)->c = c;
        return;
    }

    if ((*s)->c == '\0') {
        (*s)->c = c;
    } 
    else {
        str new = create();
        if (new != NULL) {
            new->c = c;
            str aux = *s;
            while (aux->next != NULL) {
                aux = aux->next;
            }
            aux->next = new;
        }
    }
}

void tostr(str* s, char* text) {
    if (text == NULL) return;
    int i = 0;
    while (text[i] != '\0') {
        addstr(s, text[i]);
        i++;
    }
}

void elimvocal(str* s) {
    if (*s == NULL) return;
    str actual = *s;
    str anterior = NULL;
    while (actual != NULL) {
        char l = tolower(actual->c);
        if (l == 'a' || l == 'e' || l == 'i' || l == 'o' || l == 'u') {
            str borrar = actual;
            if (anterior == NULL) {
                *s = actual->next;
                actual = *s;
            } else {
                anterior->next = actual->next;
                actual = anterior->next;
            }
            free(borrar);
        } else {
            anterior = actual;
            actual = actual->next;
        }
    }
}

void printstr(str s) {
    if (s == NULL || (s->c == '\0')) {
        printf("string vacio\n");
        return;
    }
    while (s != NULL) {  
      printf("%c", s->c);
      s = s->next;
    }
    printf("\n");
}

void destroystr(str* s) {
    str aux;
    while (*s != NULL) {
        aux = *s;
        *s = (*s)->next;
        free(aux);
    }
}

bool cmp(str s1, str s2) {
    while (s1 != NULL && s2 != NULL) {
        if (s1->c != s2->c) return false;
        s1 = s1->next;
        s2 = s2->next;
    }
    return (s1 == NULL && s2 == NULL);
}

void strcopy(str* d, str s) {
    if (s == NULL||s->c == '\0') return;
    str aux = s;
    while (aux != NULL) {
        addstr(d, aux->c);
        aux = aux->next;
    }
}

char get_char(str s) {
    if (s == NULL) return '\0';
    return s->c;
}

str get_next(str s) {
    if (s == NULL) return NULL;
    return s->next;
}
void print_str_inline(str s) {
	while (s != NULL && get_char(s) != '\0') {
		printf("%c", get_char(s));
		s = get_next(s);
	}
}
str get_next_node(str s) {
	return get_next(s); 
}

void printstr_inline(str s) {
	while (s != NULL && s->c != '\0') {
		printf("%c", s->c);
		s = s->next;
	}
}

