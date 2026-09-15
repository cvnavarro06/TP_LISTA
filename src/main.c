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


int main(int argc, char **argv)
{
	
	if (argc < 4) {
		printf ("Error");
		return ERROR;
	}

	



	return EXITO;
}
