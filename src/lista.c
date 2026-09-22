#include "lista.h"

#include <stdio.h>

#define ERROR -1

struct nodo 
{
	void *data;
	struct nodo *siguiente;
};

struct lista 
{
	struct nodo *cabeza;
	size_t cantidad;
};

struct lista_iterador {
	struct nodo *actual;
};

struct nodo *crear_nodo(void *dato)
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

	lista_t *nueva_lista = malloc(sizeof(struct lista));

    if (nueva_lista == NULL) {
        return NULL;
    }

	nueva_lista->cantidad = 0;
	nueva_lista->cabeza = NULL;

	return nueva_lista;
}

/*
 * Devuelve la cantidad de elementos que almacena la lista.
 */
size_t lista_cantidad(lista_t *lista)
{
	size_t cantidad = 0;

	if (lista == NULL) {
		return cantidad;
	}

	cantidad = lista->cantidad;

	return cantidad;
}

/*
 * Devuelve true si la lista está vacía
 */
bool lista_esta_vacia(lista_t *lista)
{
	bool vacia = false;
	
	if (lista == NULL) {
		return vacia;	
	}

	size_t cantidad = lista->cantidad;

	if (cantidad <= 0) {
		vacia = true;
	}

	return vacia;
}


bool insertar_en_lista(lista_t *lista, struct nodo *actual, size_t posicion, struct nodo *nodo_nuevo)
{
	bool exito = false;
	
	if (lista == NULL) {
		return exito;
	}

	size_t i = 0;

	if (posicion == 0) { // Caso límite
		nodo_nuevo->siguiente = lista->cabeza;
		lista->cabeza = nodo_nuevo;

		exito = true;
	}

	while (actual != NULL && !exito) {
       
		if (posicion - 1 == i) {
	   		nodo_nuevo->siguiente = actual->siguiente;
	   		actual->siguiente = nodo_nuevo;

	   		exito = true;
		} else {

	   	actual = actual->siguiente;
	   	i++;
	   	}
	}

	return exito;
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

	if (lista == NULL || posicion > lista->cantidad) {
		return exito;
	}

	struct nodo *nodo_nuevo = crear_nodo(dato);

	struct nodo *actual = lista->cabeza;

	exito = insertar_en_lista(lista, actual, posicion, nodo_nuevo);

	if (exito) {
		lista->cantidad++;
	}

	return exito;
}

void *eliminar_en_lista(lista_t *lista, struct nodo *actual, size_t posicion)
{
	if (actual == NULL) {
		return NULL;
	}

	size_t i = 0;

	bool encontrado = false;

	struct nodo *aux;

	void *data = { NULL };

	if (posicion == 0) {
        lista->cabeza = actual->siguiente;
        aux = actual;
        data = aux->data;
        free(aux);

        encontrado = true;
    }

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
 * Elimina un dato en la posicion dada de la lista y devuelve el elemento eliminado.
 *
 * Si la posición está mas allá del final de la lista, no se puede eliminar y devuelve NULL.
 */
void *lista_eliminar(lista_t *lista, size_t posicion)
{
	if (lista == NULL || lista_esta_vacia(lista)) {
		return NULL;
	}

	bool encontrado = false;

	void *data = { NULL };

	struct nodo *actual = lista->cabeza;

	data = eliminar_en_lista(lista, actual, posicion);

	if (data != NULL) {
		encontrado = true;
	}

    if (encontrado) {
        lista->cantidad--;
    }

	return data;
}


void *remplazar_en_lista(struct nodo *actual, size_t posicion, void *dato)
{

	if (actual == NULL) {
		return NULL;
	}
	
	void *data_replaced = { NULL };

	bool encontrado = false;

	size_t i = 0;

	while (actual != NULL && !encontrado) {
		if (posicion == i) {
			data_replaced = actual->data;
			actual->data = dato;

			encontrado = true;
		} else {
			i++;
			actual = actual->siguiente;
		}
	}

	return data_replaced;
}

/*
 * Reemplaza un dato en la posición dada de la lista y lo devuelve.
 */
void *lista_reemplazar(lista_t *lista, void *dato, size_t posicion)
{
	if (lista == NULL || lista_esta_vacia(lista)) {
		return NULL;
	} else if (posicion > lista->cantidad) {
		return NULL;
	}

	struct nodo *actual = lista->cabeza;

	void *data_replaced = remplazar_en_lista(actual, posicion, dato);

	return data_replaced;
}

void *obtener_en_lista(struct nodo *actual, size_t posicion)
{
	if (actual == NULL) {
		return NULL;
	}

	void *data = { NULL };
	
	size_t i = 0;

	bool encontrado = false;

	while (actual != NULL && !encontrado) {
		if (posicion == i) {
			data = actual->data;

			encontrado = true;
		} else {
			actual = actual->siguiente;
			i++;
		}
	}

	return data;
}

/*
 * Devuelve el elemento que se encuentra en la posición de la lista.
 */
void *lista_obtener(lista_t *lista, size_t posicion)
{
	if (lista == NULL || lista_esta_vacia(lista)) {
		return NULL;
	} else if (posicion > lista->cantidad) {
		return NULL;
	}

	struct nodo *actual = lista->cabeza;

	void *data = obtener_en_lista(actual, posicion);

	return data;
}

bool buscar_en_lista(struct nodo *actual, int *posicion, void *buscado, int(*comparador)(void*, void*),void **encontrado)
{
	if (actual == NULL);

	bool se_encontro = false;

	int i = 0;

	while (actual != NULL && !se_encontro) {
		if (comparador(buscado, actual->data) == 0) {
			*encontrado = actual->data;
			*posicion = i;

			se_encontro = true;
		} else {
			i++;
			actual = actual->siguiente;
		}
	}

	return se_encontro;
}

/*
 * Busca un elemento en la lista utilizando el comparador. Si lo encuentra devuelve la posición en la que se encuentra.
 *
 * Si no lo encuentra devuelve -1.
 *
 * Si se provee el puntero encontrado, en dicho puntero se almacena el elemento encontrado o NULL en caso de no encontrarse.
 */
int lista_buscar(lista_t *lista, void *buscado,
		 int (*comparador)(void *, void *), void **encontrado)
{
	if (lista == NULL || comparador == NULL || buscado == NULL) {
		return ERROR;
	}

	struct nodo *actual = lista->cabeza;
	
	int posicion;
	
	bool se_encontro = false;

	se_encontro = buscar_en_lista(actual, &posicion, buscado, comparador, encontrado);

	if (!se_encontro) {
		*encontrado = NULL;

		posicion = ERROR;
	}

	return posicion;
}

/*
 * Recorre la lista aplicando la función f. Devuelve la cantidad de veces que fue invocada f.
 *
 * Si f devuevle false, se deja de iterar.
 */
size_t lista_iterar(lista_t *lista, bool (*f)(void *, void *), void *extra)
{

	size_t contador = 0;

	if (lista == NULL || f == NULL || extra == NULL) {
		return contador;
	}

	struct nodo *actual = lista->cabeza;

	bool stop = false;

	while (actual != NULL && !stop) {
		contador++;

		if (!f(actual->data, extra)) {
			stop = true;
		}
	}

	return contador;
}

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

	struct nodo *aux = lista->cabeza;

	lista->cabeza = lista->cabeza->siguiente;

	free(aux);

	//Recursivo
	lista_destruir(lista);
}

/*
 * Libera la lista y toda la memoria asociada.
 *
 * Adicionalmente aplica la función destructora a cada elemento almacenado *
 */
void lista_destruir_todo(lista_t *lista, void (*destructor)(void *))
{
	if (lista == NULL || destructor == NULL) {
		return;
	}

	if (lista->cabeza == NULL) {
		free(lista);
		return;
	}

	struct nodo *aux = lista->cabeza;

	lista->cabeza = lista->cabeza->siguiente;

	destructor(aux->data);

	free(aux);

	lista_destruir_todo(lista, destructor);
}

/*
 * Crea un iterador de lista
 */
lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	if (lista == NULL || lista_esta_vacia(lista)) {
		return NULL;
	}

	struct lista_iterador *nuevo_iterador =
		malloc(sizeof(struct lista_iterador));

	if (nuevo_iterador == NULL) {
		return NULL;
	}

	nuevo_iterador->actual = lista->cabeza;

	return nuevo_iterador;
}

/*
 * Devuelve true si hay mas elementos para iterar
 */
bool lista_iterador_se_puede_iterar(lista_iterador_t *it)
{
	bool exito = false;

	if (it == NULL || it->actual == NULL) {
		return exito;
	} else {
		exito = true;
	}

	return exito;
}

/*
 * Avanza a la siguiente iteración
 */
void lista_iterador_siguiente(lista_iterador_t *it)
{
	if (it == NULL) {
		return;
	}

    it->actual = it->actual->siguiente;

}

/*
 * Devuelve el elemento actual iterado
 */
void *lista_iterador_obtener_elemento(lista_iterador_t *it)
{
	if (it == NULL) {
		return NULL;
	}

	return it->actual->data;
}

/*
 * Destruye el iterador
 */
void lista_iterador_destruir(lista_iterador_t *it)
{
	if (it == NULL) {
		return;
	}

	free(it);
}
