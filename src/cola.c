#include "cola.h"
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

struct nodo *nuevo_nodo_cola(void *dato)
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


cola_t *cola_crear()
{
    cola_t *nueva_cola = malloc(sizeof(cola_t));

    if (nueva_cola == NULL) {
        return NULL;
    } else {
        nueva_cola->principio = NULL;
        nueva_cola->final = NULL;

        nueva_cola->cantidad = 0;
    }

    return nueva_cola;
}

bool cola_encolar(cola_t *c, void *e)
{
    bool exito = false;

    if (c == NULL) {
        return exito;
    }

    //Creo un nuevo nodo aislado
    struct nodo *nodo_nuevo = nuevo_nodo_cola(e);

    if (nodo_nuevo != NULL) {
        
        if (cola_esta_vacia(c)) {
            c->principio = nodo_nuevo;
            c->final = nodo_nuevo;
        } else {
            c->final->siguiente = nodo_nuevo;
            
            c->final = nodo_nuevo;

            c->final->siguiente = NULL;
        }
        c->cantidad++;
        exito = true;
    }
    
    return exito;
}

void *cola_desencolar(cola_t *c)
{
    if (c == NULL || cola_esta_vacia(c)) {
        return NULL;
    }


    //Linkeo el auxiliar con el nodo a desencolar
    struct nodo *nodo_a_sacar = c->principio;

    void *data = nodo_a_sacar->data;
    
    //Le paso el linkeo del principio al siguiente
    c->principio = c->principio->siguiente;
    
    if (c->principio == NULL) c->final = NULL;
    free(nodo_a_sacar);
    
    c->cantidad--;

    return data;
}

void *cola_frente(cola_t *c)
{
    if (c == NULL || cola_esta_vacia(c)) {
        return NULL;
    }

    return c->final->data;
}

bool cola_esta_vacia(cola_t *c)
{
    bool vacio = false;

    if (c->cantidad <= 0) {
        vacio = true;
    }

    return vacio;
}

size_t cola_cantidad(cola_t *c)
{
    if (c == NULL) {
        return 0;
    }

    return c->cantidad;
}

void cola_destruir(cola_t *cola)
{
    if (cola == NULL) {
        return;
    }

    while (cola->principio != NULL) {
        struct nodo *aux = cola->principio->siguiente;

        free(cola->principio);

        cola->principio = aux;
    }

    free(cola);

}