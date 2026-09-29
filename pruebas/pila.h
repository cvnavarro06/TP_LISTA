#ifndef PILA_H_
#define PILA_H_
#include <stdlib.h>
#include <stdbool.h>

typedef struct pila pila_t;

pila_t *pila_crear();

bool pila_apilar(pila_t *p, void *e);

void *pila_desapilar(pila_t *p);

void *pila_tope(pila_t *p);

bool pila_esta_vacia(pila_t *p);

size_t pila_cantidad(pila_t *p);

void pila_destruir(pila_t *pila);

#endif // PILA_H_
