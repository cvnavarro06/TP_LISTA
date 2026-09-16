#include "cola.h"
#include "pila.h"
#include "lista.h"
#include <stdint.h>
#include <stdio.h>

struct nodo {
	void *data;
	struct nodo *siguiente;
};

struct cola {
	struct nodo *principio;
	struct nodo *final;
	size_t cantidad;
};

struct pila {
	struct nodo *tope;
	size_t cantidad;
};

struct lista 
{
	struct nodo *cabeza;
	size_t cantidad;
};

#define EXITO 0
#define ERROR -1


int main()
{
	//COLA

	//cola_t *cola = cola_crear();
//
	//if (cola == NULL) {
	//	printf("Ha ocurrido un error al crear la cola\n");
	//	return ERROR;
	//} else {
	//	printf("Se ha creado correctamente la cola\n");
	//}
//
	//int numero = 2;
	//cola_encolar(cola, &numero);
//
	//int numero1 = 4;
	//cola_encolar(cola, &numero1);
//
	//int numero2 = 6;
	//cola_encolar(cola, &numero2);
//
	//printf("=============================\n");
	//printf("     ESTRUCTURA COLA\n");
	//printf("=============================\n");
//
	//printf(" ___\n");
	//printf("|%d", *(int *)cola->principio->data);
	//printf("%d", *(int *)cola->principio->siguiente->data);
	//printf("%d|\n", *(int *)cola->final->data);
	//printf(" ---\n\n");
//
	//printf("Cantidad previamente a desencolar: %ld\n", cola->cantidad);
//
	//int tope_cola = *(int *)cola_desencolar(cola);
//
	//printf("Tope: %d\n", tope_cola);
//
	//printf("Cantidad ya habiendo desencolado: %ld\n\n", cola->cantidad);
//
	//cola_destruir(cola);
	////PILA-------------------------------------------------------
//
	//pila_t *pila = pila_crear();
//
	//if (pila == NULL) {
	//	printf("Ha ocurrido un error al crear la pila\n");
	//	return ERROR;
	//} else {
	//	printf("La pila ha sido creada correctamente!\n");
	//}
//
	//int p1 = 1;
	//pila_apilar(pila, &p1);
//
	//int p2 = 3;
	//pila_apilar(pila, &p2);
//
	//int p3 = 5;
	//pila_apilar(pila, &p3);
//
	//printf("=============================\n");
	//printf("     ESTRUCTURA PILA\n");
	//printf("=============================\n");
//
	//printf(" _\n");
	//printf("|%d|\n", *(int *)pila->tope->data);
	//printf("|%d|\n", *(int *)pila->tope->siguiente->data);
	//printf("|%d|\n", *(int *)pila->tope->siguiente->siguiente->data);
	//printf(" -\n");
//
	//printf("Cantidad previa a desapilar: %ld\n", pila->cantidad);
//
	//int tope_pila = *(int *)pila_desapilar(pila);
//
	//printf("Tope: %d\n", tope_pila);
//
	//printf("Cantidad ya habiendo desapilado: %ld\n", pila->cantidad);
//
	//pila_destruir(pila);

	//LISTA------------------------------------------------------

	lista_t *lista = lista_crear();

	if (lista == NULL) {
		printf ("Ha ocurrido un error a la hora de crear la lista\n");
		return ERROR;
	} else {
		printf("La lista ha sido creada con éxito!\n");
	}

	printf("Cantidad de elementos de la lista: %ld\n\n", lista_cantidad(lista));

	
	if (lista_esta_vacia(lista)) {
		printf("La lista está vacia\n");
	}

	int array[10] = {1,4,2,3,7,8,4,9};
	int tope_array = 8;

	for (size_t i = 0; i<tope_array; i++) {
		if (lista_insertar(lista, &array[i], i)) {
			printf("%ld_ Se ha ingresado el numero %d a la lista!\n", i + 1, array[i]);
		} else {
			printf("Ha ocurrido un error a la hora de introducir un dato a la lista\n");
		}
	}

	printf("Cantidad de elementos de la lista: %ld\n\n", lista_cantidad(lista));

	printf("primero: %d\n", *(int*)lista->cabeza->data);
	printf("segundo: %d\n", *(int*)lista->cabeza->siguiente->data);

	printf("Lista creada:\n\n");

	printf("LISTA");

	for (size_t i = 0; i<tope_array; i++) {
		int *tope = lista_obtener(lista, i);
		printf("-%d", *tope); 
	}
	printf("\n\n");

	int tope_ar = tope_array;

	for (size_t i = 0; i<tope_array; i++) {
		int *tope = lista_eliminar(lista, 0);
		
		if (tope != NULL) {
			printf("%ld_ Se ha eliminado el número: %d\n\n", i + 1, *tope);

			if (lista->cabeza != NULL){
				printf("Nuevo encabezado de la lista %d\n\n", *(int*)lista->cabeza->data);

				printf("LISTA");

				tope_ar--;

				for (size_t j = 0; j<tope_ar; j++) {
					int *tope_top = lista_obtener(lista, j);
					printf("-%d", *tope_top); 
				}
				printf("\n\n");

			}
		}
	}

	printf("Cantidad de elementos de la lista: %ld\n\n", lista_cantidad(lista));

	lista_destruir(lista);

	return EXITO;
}
