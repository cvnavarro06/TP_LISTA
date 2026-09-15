#include "pila.h"

struct nodo
{
    void *data;
    struct nodo *siguiente;
};

struct pila 
{
    struct nodo *tope;
    size_t cantidad;
};

struct nodo *nuevo_nodo_pila(void *dato)
{
    struct nodo *nodo_nuevo = malloc(sizeof(struct nodo));

    if (nodo_nuevo == NULL) {
        return NULL;
    } else {
        nodo_nuevo->data = dato;
        nodo_nuevo->siguiente = NULL;
    }

    return nodo_nuevo;  
}

pila_t *pila_crear()
{

    pila_t *pila_nueva = malloc(sizeof(pila_t));

    if (pila_nueva == NULL) {
        return NULL;
    } else {
        pila_nueva->tope = NULL;
        pila_nueva->cantidad = 0;
    }

    return pila_nueva;
}

bool pila_apilar(pila_t *p, void *e)
{
    bool exito = false;

    if (p == NULL) {
        return exito;
    }

    struct nodo *nodo_nuevo = nuevo_nodo_pila(e);

    if (nodo_nuevo != NULL) {
        
        if (pila_esta_vacia(p)) {
            p->tope = nodo_nuevo;
            p->tope->siguiente = NULL;
        } else {
            nodo_nuevo->siguiente = p->tope;
            p->tope = nodo_nuevo;
        }
        p->cantidad++;
        exito = true;
    }

    return exito;
}

void *pila_desapilar(pila_t *p)
{
    if (p == NULL || (p->tope == NULL) || pila_esta_vacia(p)) {
        return NULL;
    }

    struct nodo *nodo_a_sacar = p->tope;

    void *data = nodo_a_sacar->data;

    p->tope = p->tope->siguiente;

    free(nodo_a_sacar);

    p->cantidad--;
    
    return data;
}

void *pila_tope(pila_t *p)
{
    if (p == NULL || pila_esta_vacia(p)) {
        return NULL;
    }

    void *data = p->tope->data;

    return data;
}

bool pila_esta_vacia(pila_t *p)
{
    bool vacia = false;

    if (p == NULL) {
        return vacia;
    }

    if (p->cantidad <= 0) {
        vacia = true;
    }

    return vacia;
}

size_t pila_cantidad(pila_t *p)
{
    if (p == NULL) {
        return 0;
    }

    return p->cantidad;
}

void pila_destruir(pila_t *pila)
{
    if (pila == NULL) {
        return;
    }

    while(pila->tope != NULL) {
        struct nodo *aux = pila->tope->siguiente;

        free(pila->tope);

        pila->tope = aux;
    }

    free (pila);
}