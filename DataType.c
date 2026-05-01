#include "DataType.h"


tdata create_str_ast() {

    tdata new = (tdata) malloc(sizeof(struct datatype));
    if (new != NULL) {
        new->nodetype = STR;
        new->string = create();
    }
    return new;
}

tdata create_list() {

    tdata new = (tdata) malloc( sizeof (struct datatype) );

    if (new != NULL) {
        new->nodetype = LIST;
        new->data = NULL;
        new->next = NULL;
    }
    return new;
}

tdata create_set() {

    tdata new = (tdata)malloc(sizeof (struct datatype) );
    if (new != NULL) {
        new->nodetype = SET;
        new->data = NULL;
        new->next = NULL;
    }
    return new;
}

bool cmpstr(tdata a, tdata b) {

    if (a == NULL || b == NULL || a->nodetype != STR || b->nodetype != STR) return false;
    return cmp(a->string, b->string);
}

tdata concatstr(tdata a, tdata b) {
    if (a == NULL || b == NULL || a->nodetype != STR || b->nodetype != STR) return NULL;
    tdata new = create_str_ast();
    
    if (new != NULL) {
        strcopy(&(new->string), a->string);
        strcopy(&(new->string), b->string);
    }

    return new;
}

tdata clonar(tdata ori) {

    if (ori == NULL) return NULL;
    tdata new;

    if (ori->nodetype == STR) {
        new = create_str_ast();
        if (new != NULL) strcopy(&(new->string), ori->string);
    } 
    else {
        if (ori->nodetype == LIST) new = create_list();
        else new = create_set();

        tdata aux = ori->data; 
        while (aux != NULL) {
            append(&new, aux->data); 
            aux = aux->next;
        }
    }
    return new;
}

void append(tdata* list, tdata elem) {

    if (elem == NULL || *list == NULL) return;

    tdata clon = clonar(elem);
    if (clon == NULL) return;

    tdata hook = create_list(); 
    if (hook == NULL) return;
    hook->data = clon;

    if ((*list)->data == NULL) {
        (*list)->data = hook; 
    } 
    else {
        tdata aux = (*list)->data; 
        while (aux->next != NULL) {
            aux = aux->next;
        }
        aux->next = hook; 
    }
}

int length(tdata list) {

    if (list == NULL || (list->nodetype != LIST && list->nodetype != SET)) return 0;

    int c = 0;
    tdata aux = list->data;

    while (aux != NULL) {
        c++;
        aux = aux->next;
    }

    return c;
}

tdata copy_list(tdata list) {

    if (list == NULL || (list->nodetype != LIST && list->nodetype != SET)) return NULL;
    return clonar(list);
}

tdata concat(tdata l1, tdata l2) {

    if (l1 == NULL || l2 == NULL) return NULL;
    if (l1->nodetype == STR || l2->nodetype == STR) return NULL;

    tdata new = clonar(l1);
    if (new == NULL) return NULL;

    tdata aux = l2->data;
    while (aux != NULL) {
        append(&new, aux->data);
        aux = aux->next;
    }

    return new;
}

bool twins(tdata a, tdata b) {

    if (a == NULL || b == NULL) return false;

    if (a->nodetype == STR && b->nodetype == STR) {
        return cmp(a->string, b->string);
    }

    if ((a->nodetype != b->nodetype)||(length(a) != length(b))) return false;

    tdata ax = a->data;

    if (a->nodetype == LIST) {
        
        tdata bx = b->data;
        while (ax != NULL && bx != NULL) {
            if (twins(ax->data, bx->data) == false) return false;
            ax = ax->next;
            bx = bx->next;
        }
        return true;
    } 
    else {
        while (ax != NULL) {
            if (search(b, ax->data) == false) return false;
            ax = ax->next;
        }
        return true;
    }
}

bool search(tdata list, tdata c) {

    if (list == NULL || c == NULL) return false;
    if (list->nodetype == STR) return false;

    bool b = false;
    tdata aux = list->data;

    while (aux != NULL &&  b == false) {
        if (twins(aux->data, c)) b = true;
        aux = aux->next;
    }

    return b;
}

void insert_set(tdata* s, tdata e) {

    if (s == NULL ||*s == NULL || (*s)->nodetype != SET ||  e == NULL) return;

    if (!belongs(*s, e)) append(s, e);
    
}

bool belongs(tdata s, tdata e) {

    if (s == NULL || e == NULL || (s->nodetype != SET && s->nodetype != LIST)) return false;

    return search(s, e);
}

void destroy(tdata x) {

    if (x == NULL) return;
    if (x->nodetype == STR) {
        destroystr( &(x->string) );
    } else {
        tdata aux = x->data;
        while (aux != NULL) {
            tdata next = aux->next;
            destroy(aux->data);
            free(aux);
            aux = next;
        }
    }
    free(x);
}

void remove_set(tdata* s, tdata e) {

    if (s == NULL || *s == NULL || e == NULL || (*s)->nodetype != SET) return;

    if (belongs(*s, e)) {
        tdata aux = (*s)->data;
        tdata pre = NULL;

        while (aux != NULL) {
            if (twins(aux->data, e)) {
                if (pre == NULL) {
                    (*s)->data = aux->next;
                } else {
                    pre->next = aux->next;
                }
                destroy(aux->data);
                free(aux);
                return;
            }
            pre = aux;
            aux = aux->next;
        }
    } else {
        printf("el elemento no está en el conjunto\n");
    }
}

tdata union_set(tdata a, tdata b) {
    if (a == NULL || b == NULL || a->nodetype != SET || b->nodetype != SET) return NULL;

    tdata new = copy_list(a);
    tdata aux = b->data;

    while (aux != NULL) {
        insert_set(&new, aux->data);
        aux = aux->next;
    }

    return new;
}

tdata intersection_set(tdata a, tdata b) {
    if (a == NULL || b == NULL || a->nodetype != SET || b->nodetype != SET) return NULL;

    tdata new = create_set();
    tdata aux = a->data;

    while (aux != NULL) {
        if (belongs(b, aux->data)) {
            insert_set(&new, aux->data);
        }
        aux = aux->next;
    }

    return new;
}

tdata difference_set(tdata a, tdata b) {
    if (a == NULL || b == NULL || a->nodetype != SET || b->nodetype != SET) return NULL;

    tdata new = create_set();
    tdata aux = a->data;

    while (aux != NULL) {
        if (!belongs(b, aux->data)) {
            insert_set(&new, aux->data);
        }
        aux = aux->next;
    }

    return new;
}

bool subset(tdata a, tdata b) {
    if (a == NULL || b == NULL || a->nodetype != SET || b->nodetype != SET) return false;

    tdata aux = b->data;
    while (aux != NULL) {
        if (!belongs(a, aux->data)) return false;
        aux = aux->next;
    }

    return true;
}

bool equals_set(tdata a, tdata b) {
    if (a == NULL || b == NULL || a->nodetype != SET || b->nodetype != SET) return false;
    return twins(a, b);
}

tdata producto_cartesiano(tdata a, tdata b) {
    if (a == NULL || b == NULL || a->nodetype != SET || b->nodetype != SET) return NULL;

    tdata new = create_set();
    if (new == NULL) return NULL;

    tdata ax = a->data;
    while (ax != NULL) {
        tdata bx = b->data;
        while (bx != NULL) {
            tdata par = create_list();
            if (par != NULL) {
                append(&par, ax->data);
                append(&par, bx->data);
                insert_set(&new, par);
                destroy(par);
            }
            bx = bx->next;
        }
        ax = ax->next;
    }
    return new;
}

tdata str_to_list(tdata s) {
    if (s == NULL || s->nodetype != STR) return NULL;

    tdata new = create_list();
    str cu = s->string;

    if (cu == NULL || get_char(cu) == '\0') return new;

    while (cu != NULL) {
        tdata ca = create_str_ast();
        addstr(&(ca->string), get_char(cu));
        append(&new, ca);
        destroy(ca);
        cu = get_next_node(cu);
    }
    return new;
}

tdata to_str(tdata n) {
    if (n == NULL) return NULL;

    tdata res = create_str_ast();

    if (n->nodetype == STR) {
        addstr(&(res->string), '"');
        strcopy(&(res->string), n->string);
        addstr(&(res->string), '"');
    } 
    else {
        if (n->nodetype == SET) {
            addstr(&(res->string), '{');
        } else {
            addstr(&(res->string), '[');
        }

        tdata ax = n->data;
        while (ax != NULL) {
            tdata tmp = to_str(ax->data);
            if (tmp != NULL) {
                strcopy(&(res->string), tmp->string);
                destroy(tmp);
            }

            if (ax->next != NULL) {
                addstr(&(res->string), ',');
                addstr(&(res->string), ' ');
            }
            ax = ax->next;
        }

        if (n->nodetype == SET) {
            addstr(&(res->string), '}');
        } else {
            addstr(&(res->string), ']');
        }
    }

    return res;
}
void print_data(tdata d) {
	if (d == NULL) {
		printf("(null)");
		return;
	}
	
	switch (d->nodetype) {
		
	case STR:
		if (d->string == NULL || get_char(d->string) == '\0')
			printf("\"\"");
		else
			print_str_inline(d->string);
		break;
		
	case LIST: {
		printf("[ ");
		tdata cur = d->data;
		while (cur != NULL) {
			print_data(cur->data);
			if (cur->next != NULL) printf(", ");
			cur = cur->next;
		}
		printf(" ]");
		break;
	}
	
	case SET: {
		printf("{ ");
		tdata cur = d->data;
		while (cur != NULL) {
			print_data(cur->data);
			if (cur->next != NULL) printf(", ");
			cur = cur->next;
		}
		printf(" }");
		break;
	}
	
	default:
		printf("<tipo desconocido: %d>", d->nodetype);
		break;
	}
}
tdata make_str(const char* text) {
	tdata s = create_str_ast();
	if (s == NULL) return NULL;
	for (int i = 0; text[i] != '\0'; i++)
		addstr(&(s->string), text[i]);
	return s;
}
