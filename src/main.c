#include "cola.h"
#include "pila.h"
#include "lista.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

struct nodo 
{
	void *data;
	struct nodo *siguiente;
};

struct cola 
{
	struct nodo *principio;
	struct nodo *final;
};

struct pila 
{
	struct nodo *tope;
};

struct lista
{
	struct nodo *cabeza;
};

#define EXITO 0
#define ERROR -1

#define OPERADOR 1
#define CONJUNTOS 2

#define CARACTER_NULO '\0'
#define SEPARADOR ','




/*
 * La cola debe estar previamente creada.
 *
 * Devuelve true si la operación ha sido exitosa, caso contrario devuelve false por algún en la operación
*/
bool parsear_conjunto_aniado_cola(cola_t *cola, char *conjunto, char separador)
{

    if (cola == NULL || conjunto == NULL || separador == CARACTER_NULO){
        return false;
	}

	if (*conjunto == CARACTER_NULO) {
		return true;
	}

	char *numero = malloc(sizeof(char) + 1);

	if (numero == NULL) {
		return false;
	}

	size_t tope_numero = 0;

	bool err = false;

    while (*conjunto != separador && *conjunto != CARACTER_NULO && !err) {
		numero[tope_numero] = conjunto[0];
		tope_numero++;

		char *aux = realloc(numero, sizeof(char) * (tope_numero + 1));

		if (aux == NULL) {
			err = true;

		} else {
			numero = aux;

			//Avanzo aritméticamente
			conjunto++;
		}
    }

	if (err) {
		free(numero);
		return false;
	}

	numero[tope_numero] = CARACTER_NULO;

	int numero_transformado = atoi(numero);

	free(numero);

	if (!cola_encolar(cola, (void*)(intptr_t)numero_transformado)) {
		return false;
	}

	if (*conjunto == CARACTER_NULO) {
		return true;
	}

	return parsear_conjunto_aniado_cola(cola, conjunto + 1, separador);
}

int main(int argc, char **argv)
{

	if (argc < 3) {

		//Mensaje de error
		return ERROR;
	}

	lista_t *lista = lista_crear();

	int longitud_max = -1;

	//Proximamente a utilizar para una función de calculo
	int longitud_min = 1000000000;
	
	bool err = false;

	//For para cargar la lista de colas con los conjuntos
	for (size_t i = 2; i < (size_t)argc && !err; i++) {

		cola_t *cola = cola_crear();
		
		if (!parsear_conjunto_aniado_cola(cola, argv[i], SEPARADOR)) {
			err = true;
		} else {
		
			int longitud = (int)cola_cantidad(cola);
			
			if (longitud > longitud_max) longitud_max = longitud;
			
			if (longitud < longitud_min) longitud_min = longitud;
			
			lista_insertar(lista, cola, i - 2);
		}
	}

	if (err) lista_destruir_todo(lista, (void (*)(void*))cola_destruir);

	return EXITO;
}
