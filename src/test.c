#include "cola.h"
#include "pila.h"
#include <stdint.h>
#include <stdio.h>

struct nodo
{
    void *data;
    struct nodo *siguiente;
};

struct cola
{
    struct nodo *principio;
    struct nodo *final;
    size_t cantidad;
};

struct pila 
{
    struct nodo *tope;
    size_t cantidad;
};

#define EXITO 0
#define ERROR -1

#define OPERADOR 1

int redondear (float numero) 
{

	float decimal = numero - (int)numero;

	int numero_r;

	if (decimal >= 0.5) {
		numero_r = (int)numero + 1;
	} else {
		numero_r = (int)numero;
	}

	return numero_r;
}


int test()
{

	//COLA

	cola_t *cola = cola_crear();

	if (cola == NULL) {
		printf("Ha ocurrido un error al crear la cola\n");
		return ERROR;
	} else {
		printf("Se ha creado correctamente la cola\n");
	}

	int numero = 2;
	cola_encolar(cola, &numero);

	int numero1 = 4;
	cola_encolar(cola, &numero1);
	
	int numero2 = 6;
	cola_encolar(cola, &numero2);

	printf("=============================\n");
	printf("     ESTRUCTURA COLA\n");
	printf("=============================\n");

	printf(" ___\n");
	printf("|%d", *(int*)cola->principio->data);
	printf("%d", *(int*)cola->principio->siguiente->data);
	printf("%d|\n", *(int*)cola->final->data);
	printf(" ---\n\n");

	printf("Cantidad previamente a desencolar: %ld\n", cola->cantidad);

	int tope_cola = *(int*)cola_desencolar(cola);

	printf("Tope: %d\n", tope_cola);

	printf("Cantidad ya habiendo desencolado: %ld\n\n", cola->cantidad);
	
	cola_destruir(cola);
	//PILA-------------------------------------------------------

	pila_t *pila = pila_crear();

	if (pila == NULL) {
		printf("Ha ocurrido un error al crear la pila\n");
		return ERROR;
	} else {
		printf("La pila ha sido creada correctamente!\n");
	}

	int p1 = 1;
	pila_apilar(pila, &p1);

	int p2 = 3;
	pila_apilar(pila, &p2);

	int p3 = 5;
	pila_apilar(pila, &p3);


	printf("=============================\n");
	printf("     ESTRUCTURA PILA\n");
	printf("=============================\n");

	printf(" _\n");
	printf("|%d|\n", *(int*)pila->tope->data);
	printf("|%d|\n", *(int*)pila->tope->siguiente->data);
	printf("|%d|\n", *(int*)pila->tope->siguiente->siguiente->data);
	printf(" -\n");

	printf("Cantidad previa a desapilar: %ld\n", pila->cantidad);

	int tope_pila = *(int*)pila_desapilar(pila);

	printf("Tope: %d\n", tope_pila);

	printf("Cantidad ya habiendo desapilado: %ld\n", pila->cantidad);

	pila_destruir(pila);

	return EXITO;
}
