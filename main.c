#include "TAD_stri.h"
#include "DataType.h"


// GUAYMAS FABRIZIO AGUSTIN, LAMAS TORRES DIEGO ERICK, YULETHSY KATERINE RIVERA GIRALDO

int main(void){
	
	/* 1. STR simple */
	printf("=== 1. STR simple ===\n");
	tdata s1 = make_str("holita");
	tdata s2 = make_str("mundoooo");
	print_data(s1); printf("\n");
	print_data(s2); printf("\n");
	
	/* 2. LIST de STRs */
	printf("\n=== 2. LIST de STRs ===\n");
	tdata lista = create_list();
	append(&lista, s1);
	append(&lista, s2);
	print_data(lista); printf("\n");
	
	/* 3. SET de STRs (sin duplicados) */
	printf("\n=== 3. SET de STRs ===\n");
	tdata set = create_set();
	tdata s3 = make_str("Q");
	tdata s4 = make_str("Sigma");
	tdata s5 = make_str("delta");
	insert_set(&set, s3);
	insert_set(&set, s4);
	insert_set(&set, s5);
	insert_set(&set, s3);   /* duplicado: no debe aparecer dos veces */
	print_data(set); printf("\n");
	
	/* 4. LIST de LISTs */
	printf("\n=== 4. LIST de LISTs ===\n");
	tdata sub1 = create_list();
	tdata sub2 = create_list();
	tdata s6 = make_str("X");
	tdata s7 = make_str("Y");
	tdata s8 = make_str("Z");
	append(&sub1, s6);
	append(&sub1, s7);
	append(&sub2, s8);
	tdata lista2 = create_list();
	append(&lista2, sub1);
	append(&lista2, sub2);
	print_data(lista2); printf("\n");
	
	/* 5. Producto cartesiano */
	printf("\n=== 5. Producto cartesiano ===\n");
	tdata setA = create_set();
	tdata sa1 = make_str("c");
	tdata sa2 = make_str("d");
	insert_set(&setA, sa1);
	insert_set(&setA, sa2);
	tdata setB = create_set();
	tdata sb1 = make_str("a");
	tdata sb2 = make_str("b");
	insert_set(&setB, sb1);
	insert_set(&setB, sb2);
	tdata cart = producto_cartesiano(setA, setB);
	printf("A x B = ");
	print_data(cart); printf("\n");
	
	/* 6. STR vacio */
	printf("\n=== 6. STR vacio ===\n");
	tdata svacio = create_str_ast();
	print_data(svacio); printf("\n");
	
	/* 7. LIST vacia */
	printf("\n=== 7. LIST vacia ===\n");
	tdata lvacia = create_list();
	print_data(lvacia); printf("\n");
	
	/* 8. to_str: serializacion interna del TAD */
	printf("\n=== 8. to_str(lista) ===\n");
	tdata repr = to_str(lista);
	print_data(repr); printf("\n");
	
	/* limpieza */
	destroy(s1); destroy(s2); destroy(s3); destroy(s4); destroy(s5);
	destroy(s6); destroy(s7); destroy(s8);
	destroy(sa1); destroy(sa2); destroy(sb1); destroy(sb2);
	destroy(lista); destroy(lista2); destroy(set);
	destroy(sub1); destroy(sub2);
	destroy(setA); destroy(setB); destroy(cart);
	destroy(svacio); destroy(lvacia); destroy(repr);
	
	return 0;
}

