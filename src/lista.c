#include "lista.h"


struct nodo
{
    void* data;
    struct nodo *siguiente;
};

struct lista 
{
    struct nodo *cabeza;
    size_t cantidad;
};

struct nodo *nuevo_nodo_lista(void *dato)
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

/*
 * Crea una lista y la devuelve.
 */
lista_t *lista_crear()
{
    lista_t *nueva_lista = { NULL };

    nueva_lista = malloc(sizeof(struct lista));
    nueva_lista->cabeza->data = 0;
    nueva_lista->cantidad = 0;
    nueva_lista->cabeza->siguiente = NULL;

    return nueva_lista;
}

/*
 * Devuelve la cantidad de elementos que almacena la lista.
 */
size_t lista_cantidad(lista_t *lista)
{
    return lista->cantidad;
}

/*
 * Devuelve true si la lista está vacía
 */
bool lista_esta_vacia(lista_t *lista)
{
    size_t cantidad = lista->cantidad;
    
    bool vacio = false;

    if (cantidad <= 0) {
        vacio = true;
    }

    return vacio;
}

/*
 * Inserta un dato en la posicion dada de la lista y devuelve true si pudo.
 *
 * Si la posición está mas allá del final de la lista, no se puede insertar.
 *
 * Si no puede insertar devuelve false.
 */
bool lista_insertar(lista_t *lista, void *dato, size_t posicion)
{

    bool exito = false;

    if (lista == NULL || posicion < 0) {
        return exito;
    } else if (posicion > lista->cantidad) {
        return exito;
    }

    size_t i = 0;

    struct nodo *actual = lista->cabeza;

    struct nodo *nodo_nuevo = nuevo_nodo_lista(dato);
    
    //
    while (actual != NULL && !exito) {

        struct nodo *aux = actual;

        if (lista_esta_vacia(lista)) {
            lista->cabeza = nodo_nuevo;
            exito = true;
        } else if (posicion - 1 == i) {
            nodo_nuevo = actual->siguiente;
            actual->siguiente = nodo_nuevo;
            exito = true;

        } else {
            actual = actual->siguiente;
            i++;
        }
    }

    if (exito) {
        lista->cantidad++;
    }

    return exito;
}

/*
 * Elimina un dato en la posicion dada de la lista y devuelve el elemento eliminado.
 *
 * Si la posición está mas allá del final de la lista, no se puede eliminar y devuelve NULL.
 */
void *lista_eliminar(lista_t *lista, size_t posicion)
{
    if (lista == NULL || lista_esta_vacia(lista)) {
        return NULL;
    }

    int i = 0;

    bool encontrado = false;
    
    void *data = { NULL };

    struct nodo *actual = lista->cabeza;

    struct nodo *aux;

    while (actual != NULL && !encontrado) {
        
        if (posicion - 1 == i) {
            aux = actual->siguiente;
            actual->siguiente = actual->siguiente->siguiente;
            data = aux->data;

            free(aux);
            encontrado = true;
        } else {
            actual = actual->siguiente;
            i++;
        }
    }


    return data;
}

/*
 * Reemplaza un dato en la posición dada de la lista y lo devuelve.
 */
void *lista_reemplazar(lista_t *lista, void *dato, size_t posicion);

/*
 * Devuelve el elemento que se encuentra en la posición de la lista.
 */
void *lista_obtener(lista_t *lista, size_t posicion);

/*
 * Busca un elemento en la lista utilizando el comparador. Si lo encuentra devuelve la posición en la que se encuentra.
 *
 * Si no lo encuentra devuelve -1.
 *
 * Si se provee el puntero encontrado, en dicho puntero se almacena el elemento encontrado o NULL en caso de no encontrarse.
 */
int lista_buscar(lista_t *lista, void *buscado,
		 int (*comparador)(void *, void *), void **encontrado);

/*
 * Recorre la lista aplicando la función f. Devuelve la cantidad de veces que fue invocada f.
 *
 * Si f devuevle false, se deja de iterar.
 */
size_t lista_iterar(lista_t *lista, bool (*f)(void *, void *), void *extra);

/*
 * Libera la lista y toda la memoria asociada.
 */
void lista_destruir(lista_t *lista)
{
    if (lista == NULL) {
        return;
    }

    if (lista->cabeza == NULL) {
        free(lista);
        return;
    }

    free(lista->cabeza->siguiente);
    
    lista_destruir(lista->cabeza->siguiente);
}

/*
 * Libera la lista y toda la memoria asociada.
 *
 * Adicionalmente aplica la función destructora a cada elemento almacenado *
 */
void lista_destruir_todo(lista_t *lista, void (*destructor)(void *));

/*
 * Crea un iterador de lista
 */
lista_iterador_t *lista_iterador_crear(lista_t *lista);

/*
 * Devuelve true si hay mas elementos para iterar
 */
bool lista_iterador_se_puede_iterar(lista_iterador_t *it);

/*
 * Avanza a la siguiente iteración
 */
void lista_iterador_siguiente(lista_iterador_t *it);

/*
 * Devuelve el elemento actual iterado
 */
void *lista_iterador_obtener_elemento(lista_iterador_t *it);

/*
 * Destruye el iterador
 */
void lista_iterador_destruir(lista_iterador_t *it);
