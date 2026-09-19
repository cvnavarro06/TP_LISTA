#include "pila.h"
#include "lista.h"
#include <stdlib.h>

struct pila {
	lista_t *lista;

};

pila_t *pila_crear()
{
	pila_t *nueva_pila = malloc(sizeof(pila_t));
	if (nueva_pila == NULL) {
		return NULL;
	}

	nueva_pila->lista = lista_crear();
	if (nueva_pila->lista == NULL) {
		free(nueva_pila);
		return NULL;
	}

	return nueva_pila;
}

bool pila_apilar(pila_t *p, void *e)
{
	bool exito = false;

	if (p == NULL) {
		return exito;
	}

	if (lista_insertar(p->lista, e, 0)) {
		exito = true;
	}

	return exito;
}

void *pila_desapilar(pila_t *p)
{
	if (p == NULL || pila_esta_vacia(p)) {
		return NULL;
	}

	void *data = lista_eliminar(p->lista, 0);

	return data;
}

void *pila_tope(pila_t *p)
{
	if (p == NULL || pila_esta_vacia(p)) {
		return NULL;
	}

	void *data = lista_obtener(p->lista, 0);

	return data;
}

bool pila_esta_vacia(pila_t *p)
{
	bool vacia = false;

	if (p == NULL) {
		return !vacia;
	}

	if (lista_esta_vacia(p->lista)) {
		vacia = true;
	}

	return vacia;
}

size_t pila_cantidad(pila_t *p)
{
	size_t cantidad = 0;

	if (p == NULL) {
		return cantidad;
	}

	cantidad = lista_cantidad(p->lista);
	
	return cantidad;
}

void pila_destruir(pila_t *pila)
{
	if (pila == NULL) {
		return;
	}

	lista_destruir(pila->lista);
	free(pila);
}