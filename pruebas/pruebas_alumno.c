#include "pa2m.h"
#include "pila.h"
#include "cola.h"
#include "lista.h"

#include <stdint.h>
#include <stdio.h>

//PRUEBAS PARA COLA
void cola_pruebas_cola_crear_vacia()
{
	pa2m_nuevo_grupo("PRUEBAS CREAR COLA CON COLA VÁLIDA");

	cola_t *cola = cola_crear();

	pa2m_afirmar(cola != NULL, "Una cola ha sido creada exitosamente!");

	pa2m_afirmar(cola_esta_vacia(cola) == true,
		     "Una cola recién creada está vacía");

	pa2m_afirmar(
		cola_cantidad(cola) == 0,
		"Una cola recién creada tiene 0 elementos dentro de la misma");

	pa2m_afirmar(cola_frente(cola) == NULL,
		     "Ver el frente de una cola vacía devuelve NULL");

	pa2m_afirmar(cola_desencolar(cola) == NULL,
		     "Desencolar en una cola vacía devuelve NULL");

	cola_destruir(cola);
}

void cola_pruebas_cola_null()
{
	pa2m_nuevo_grupo("COLA PRUEBAS CON COLA NULL");

	int number = 10;

	pa2m_afirmar(cola_encolar(NULL, &number) == false,
		     "cola_encolar con cola NULL devuelve false");

	pa2m_afirmar(cola_desencolar(NULL) == NULL,
		     "cola_desencolar con cola NULL devuelve NULL");

	pa2m_afirmar(cola_frente(NULL) == NULL,
		     "cola_frente con cola NULL devuelve NULL");

	pa2m_afirmar(cola_esta_vacia(NULL) == true,
		     "cola_esta_vacia con cola NULL devuelve true");

	pa2m_afirmar(cola_cantidad(NULL) == 0,
		     "cola_cantidad con cola NULL devuelve 0");
}

void cola_operaciones_encolar_desencolar()
{
	pa2m_nuevo_grupo("OPERACIONES CON COLA (FIFO)");

	cola_t *cola = cola_crear();
	int n1 = 10;
	int n2 = 20;

	//Operaciones con encolar
	pa2m_afirmar(cola_encolar(cola, (void *)(intptr_t)n1) == true,
		     "Se puede encolar un primer elemento");

	pa2m_afirmar(cola_esta_vacia(cola) == false,
		     "La cola con un elemento ya no está vacía");

	pa2m_afirmar(cola_cantidad(cola) == 1,
		     "La cantidad de la cola es 1, (obtenido = %ld)",
		     cola_cantidad(cola));

	pa2m_afirmar(
		(int)(intptr_t)cola_frente(cola) == n1,
		"El frente apunta al primer elemento encolado (esperado = %i), (obtenido = %i)",
		n1, (int)(intptr_t)cola_frente(cola));

	//Encolo más elementos
	pa2m_afirmar(cola_encolar(cola, (void *)(intptr_t)n2) == true,
		     "Se puede encolar un segundo elemento");

	pa2m_afirmar(cola_cantidad(cola) == 2,
		     "La cantidad de la cola es 2 (obtenido = %ld)",
		     cola_cantidad(cola));

	pa2m_afirmar(
		(int)(intptr_t)cola_frente(cola) == n1,
		"El frente sigue siendo el primer elemento encolado (esperado = %i), (obtenido = %i)",
		n1, (int)(intptr_t)cola_frente(cola));

	//Operaciones con desencolar
	int numero1 = (int)(intptr_t)cola_desencolar(cola);
	pa2m_afirmar(
		numero1 == n1,
		"Desencolar devuelve el primer elemento insertado (esperado = %i), (obtenido = %i)",
		n1, numero1);

	pa2m_afirmar(cola_cantidad(cola) == 1,
		     "La cantidad disminuye a 2 (obtenido = %ld)",
		     cola_cantidad(cola));

	pa2m_afirmar(
		(int)(intptr_t)cola_frente(cola) == n2,
		"El nuevo frente es el segundo elemento insertado (esperado = %i), (obtenido = %i)",
		n2, (int)(intptr_t)cola_frente(cola));

	//Desencolo los elementos restantes
	int numero2 = (int)(intptr_t)cola_desencolar(cola);
	pa2m_afirmar(
		numero2 == n2,
		"Desencolar devuelve el segundo elemento (esperado = %i), (obtenido = %i)",
		n2, numero2);

	pa2m_afirmar(
		cola_cantidad(cola) == 0,
		"La cantidad de elementos de la cola es 0 (obtenido = %ld)",
		cola_cantidad(cola));

	pa2m_afirmar(cola_frente(cola) == NULL,
		     "Ver frente en cola vaciada devuelve NULL");

	cola_destruir(cola);
}

void cola_pruebas_elementos_null()
{
	pa2m_nuevo_grupo("OPERACIONES DE COLA CON ELEMENTOS NULL");

	cola_t *cola = cola_crear();
	int n1 = 42;

	pa2m_afirmar(cola_encolar(cola, NULL) == true,
		     "Se puede encolar NULL como elemento");
	pa2m_afirmar(cola_esta_vacia(cola) == false,
		     "La cola no está vacía si contiene un NULL");
	pa2m_afirmar(cola_cantidad(cola) == 1,
		     "La cantidad es 1 (obtenido = %ld)", cola_cantidad(cola));
	pa2m_afirmar(cola_frente(cola) == NULL,
		     "cola_frente devuelve NULL (el elemento guardado)");

	pa2m_afirmar(cola_encolar(cola, (void *)(intptr_t)n1) == true,
		     "Se encola un elemento válido tras el NULL");
	pa2m_afirmar(cola_cantidad(cola) == 2,
		     "La cantidad es 2 (obtenido = %ld)", cola_cantidad(cola));

	pa2m_afirmar(cola_desencolar(cola) == NULL,
		     "Desencolar primer elemento devuelve NULL");
	pa2m_afirmar((int)(intptr_t)cola_frente(cola) == n1,
		     "El nuevo frente es el elemento válido");

	int numero1 = (int)(intptr_t)cola_desencolar(cola);
	pa2m_afirmar(
		numero1 == n1,
		"Desencolar segundo elemento (esperado = %i), (obtenido = %i)",
		n1, numero1);

	cola_destruir(cola);
}

//PRUEBAS PARA PILA

void pila_pruebas_pila_crear_vacia()
{
	pa2m_nuevo_grupo("CREAR UNA PILA VÁLIDA");

	pila_t *pila = pila_crear();

	pa2m_afirmar(pila != NULL, "Se puede crear una pila correctamente");

	pa2m_afirmar(pila_esta_vacia(pila) == true,
		     "Una pila recién creada está vacía");

	pa2m_afirmar(pila_cantidad(pila) == 0,
		     "Una pila recién creada tiene cantidad 0");

	pa2m_afirmar(pila_tope(pila) == NULL,
		     "Ver el tope de una pila vacía devuelve NULL");

	pa2m_afirmar(pila_desapilar(pila) == NULL,
		     "Desapilar en una pila vacía devuelve NULL");

	pila_destruir(pila);
}

void pila_pruebas_pila_null()
{
	pa2m_nuevo_grupo("OPERACIONES CON UNA PILA NULL");

	int n1 = 10;

	pa2m_afirmar(pila_apilar(NULL, (void *)(intptr_t)n1) == false,
		     "pila_apilar con pila NULL devuelve false");

	pa2m_afirmar(pila_desapilar(NULL) == NULL,
		     "pila_desapilar con pila NULL devuelve NULL");

	pa2m_afirmar(pila_tope(NULL) == NULL,
		     "pila_tope con pila NULL devuelve NULL");

	pa2m_afirmar(pila_esta_vacia(NULL) == true,
		     "pila_esta_vacia con pila NULL devuelve true");

	pa2m_afirmar(pila_cantidad(NULL) == 0,
		     "pila_cantidad con pila NULL devuelve 0");
}

void pila_operaciones_apilar_desapilar()
{
	pa2m_nuevo_grupo("OPERACIONES CON PILA (LIFO)");

	pila_t *pila = pila_crear();
	int n1 = 10;

	//Apilo elementos
	pa2m_afirmar(pila_apilar(pila, (void *)(intptr_t)n1) == true,
		     "Se puede apilar un primer elemento");

	pa2m_afirmar(pila_esta_vacia(pila) == false,
		     "La pila ya no está vacía");

	pa2m_afirmar(pila_cantidad(pila) == 1,
		     "La cantidad de la pila es 1 (obtenido = %ld)",
		     pila_cantidad(pila));

	int nuevo_tope = (int)(intptr_t)pila_tope(pila);
	pa2m_afirmar(
		nuevo_tope == n1,
		"El tope apunta al primer elemento apilado (esperado = %i), (obtenido = %i)",
		n1, nuevo_tope);

	//Desapilo elementos

	nuevo_tope = (int)(intptr_t)pila_tope(pila);
	pa2m_afirmar(
		nuevo_tope == n1,
		"El nuevo tope es el primer elemento (nuevo tope = %i), (obtenido = %i)",
		n1, nuevo_tope);

	int numero1 = (int)(intptr_t)pila_desapilar(pila);
	pa2m_afirmar(
		numero1 == n1,
		"Desapilar devuelve el primer elemento (esperado = %i), (obtenido = %i)",
		n1, numero1);

	pa2m_afirmar(pila_esta_vacia(pila) == true,
		     "La pila vuelve a estar vacía");

	pa2m_afirmar(pila_cantidad(pila) == 0, "La cantidad es 0");

	pa2m_afirmar(pila_tope(pila) == NULL,
		     "Ver el tope en una pila vaciada devuelve NULL");

	pila_destruir(pila);
}

void pila_pruebas_elemento_null()
{
	pa2m_nuevo_grupo("OPERACIONES CON ELEMENTO NULL EN PILA");

	pila_t *pila = pila_crear();

	pa2m_afirmar(pila_apilar(pila, NULL) == true,
		     "Se puede apilar NULL como elemento");

	pa2m_afirmar(pila_esta_vacia(pila) == false,
		     "La pila no está vacía si contiene un NULL");

	pa2m_afirmar(pila_tope(pila) == NULL,
		     "El tope de la pila es el elemento NULL");

	pa2m_afirmar(pila_desapilar(pila) == NULL,
		     "Desapilar el último elemento devuelve NULL");

	pa2m_afirmar(pila_esta_vacia(pila) == true,
		     "La pila queda totalmente vacía");

	pila_destruir(pila);
}

//PRUEBAS PARA LISTA + SU ITERADOR

//Funciones auxiliares
int comparador_enteros(void *a, void *b)
{
	int dif = 0;

	if (a == b) {
		return dif;
	} else if ((intptr_t)a > (intptr_t)b) {
		dif = 1;
	} else {
		dif = -1;
	}
	return dif;
}

bool sumar_elementos(void *elemento, void *extra)
{
	int *suma = (int *)extra;
	*suma += (int)(intptr_t)elemento;
	return true;
}

static int elementos_destruidos = 0;

void destructor_contador(void *elemento)
{
	elementos_destruidos++;
}

void lista_pruebas_crear_lista_vacia()
{
	pa2m_nuevo_grupo("PRUEBA DE OPERACIONES EN LISTA VACIA");

	lista_t *lista = lista_crear();

	pa2m_afirmar(lista != NULL, "Se puede crar una lista correctamente");

	pa2m_afirmar(lista_esta_vacia(lista) == true,
		     "Una lista recién creada está vacía");

	pa2m_afirmar(lista_cantidad(lista) == 0,
		     "Una lista recién creada tiene 0 elementos");

	pa2m_afirmar(lista_obtener(lista, 0) == NULL,
		     "Obtener elemento en lista vacía devuelve NULL");

	pa2m_afirmar(lista_eliminar(lista, 0) == NULL,
		     "Eliminar elemento en lista vacía devuelve NULL");

	lista_destruir(lista);
}

void lista_pruebas_lista_null()
{
	pa2m_nuevo_grupo("PRUEBA DE OPERACIONES EN LISTA NULL");

	int n1 = 10;

	int data = 20;

	pa2m_afirmar(lista_cantidad(NULL) == 0,
		     "lista_cantidad con lista NULL devuelve 0");

	pa2m_afirmar(lista_insertar(NULL, (void *)(intptr_t)n1, 0) == false,
		     "lista_insertar con lista NULL devuelve false");

	pa2m_afirmar(lista_eliminar(NULL, 0) == NULL,
		     "lista_eliminar con lista NULL devuelve NULL");

	pa2m_afirmar(lista_obtener(NULL, 0) == NULL,
		     "lista_obtener con lista NULL devuelve NULL");

	pa2m_afirmar(lista_reemplazar(NULL, (void *)(intptr_t)data, 0) == NULL,
		     "lista_reemplazar con lista NULL devuelve NULL");
}

void lista_pruebas_insertar_y_eliminar()
{
	pa2m_nuevo_grupo("PRUEBA DE INSERTAR Y ELIMINAR EN LISTA");

	lista_t *lista = lista_crear();
	int n1 = 10;
	int n2 = 20;
	int n3 = 30;

	//Inserto al inicio y al final
	pa2m_afirmar(lista_insertar(lista, (void *)(intptr_t)n1, 0) == true,
		     "Inserto un elemento en la lista al inicio de la misma");

	pa2m_afirmar(lista_insertar(lista, (void *)(intptr_t)n3,
				    lista_cantidad(lista)) == true,
		     "Inserto un elemento al final de la lista");

	//Inserto en el medio
	pa2m_afirmar(lista_insertar(lista, (void *)(intptr_t)n2, 1) == true,
		     "Insertar elemento en el medio (pos 1)");

	//Inserto en una posición inválida
	pa2m_afirmar(lista_insertar(lista, (void *)(intptr_t)n1, 100) == false,
		     "Insertar en posición inválida devuelve false");

	//Elimino un número de la lista
	int numero_eliminado = (int)(intptr_t)lista_eliminar(lista, 1);
	pa2m_afirmar(numero_eliminado == n2,
		     "Eliminar en pos 1 devuelve %i, (obtenido = %i)", n2,
		     numero_eliminado);
	pa2m_afirmar(lista_cantidad(lista) == 2, "La cantidad disminuye a 2");

	lista_destruir(lista);
}

void lista_pruebas_reemplazar()
{
	pa2m_nuevo_grupo(
		"PRUEBA DE REMPLAZAR UN ELEMENTO EN LA POSICIÓN DESEADA");

	lista_t *lista = lista_crear();
	int n1 = 10;
	int n2 = 20;
	int nuevo = 99;

	lista_insertar(lista, (void *)(intptr_t)n1, 0);
	lista_insertar(lista, (void *)(intptr_t)n2, 1);

	int numero_anterior = (int)(intptr_t)lista_reemplazar(
		lista, (void *)(intptr_t)nuevo, 1);

	pa2m_afirmar(
		numero_anterior == n2,
		"Reemplazar en pos 1 devuelve el valor anterior (obtenido = %i)",
		n2, numero_anterior);

	pa2m_afirmar((int)(intptr_t)lista_obtener(lista, 1) == nuevo,
		     "El nuevo valor remplazado es %i (obtenido = %i)", nuevo,
		     (int)(intptr_t)lista_obtener(lista, 1));

	pa2m_afirmar(lista_reemplazar(lista, (void *)(intptr_t)nuevo, 10) ==
			     NULL,
		     "Reemplazar en posición fuera de rango devuelve NULL");

	lista_destruir(lista);
}

void lista_pruebas_buscar()
{
	pa2m_nuevo_grupo("PRUEBA DE BUSCAR EL ELEMENTO SOLICITADO EN LISTA");

	lista_t *lista = lista_crear();
	int n1 = 5;
	int n2 = 15;
	int n3 = 25;
	int no_existe = 99;

	lista_insertar(lista, (void *)(intptr_t)n1, 0);
	lista_insertar(lista, (void *)(intptr_t)n2, 1);
	lista_insertar(lista, (void *)(intptr_t)n3, 2);

	void *encontrado = NULL;
	int pos = lista_buscar(lista, (void *)(intptr_t)n2, comparador_enteros,
			       &encontrado);

	pa2m_afirmar(
		pos == 1,
		"Buscar elemento existente devuelve la posición correcta (esperado = 1), (obtenido = %i)",
		pos);
	pa2m_afirmar(
		(int)(intptr_t)encontrado == n2,
		"El puntero 'encontrado' contiene el elemento esperado (esperado = %i), (obtenido = %i)",
		n2, (int)(intptr_t)encontrado);

	pos = lista_buscar(lista, (void *)(intptr_t)no_existe,
			   comparador_enteros, &encontrado);
	pa2m_afirmar(pos == -1,
		     "Buscar elemento inexistente devuelve -1 (obtenido = %i)",
		     pos);
	pa2m_afirmar(encontrado == NULL,
		     "El puntero 'encontrado' almacena NULL cuando no existe");

	lista_destruir(lista);
}

void lista_pruebas_iterador_interno()
{
	pa2m_nuevo_grupo("PRUBA DEL ITERADOR INTERNO DE LISTA");

	lista_t *lista = lista_crear();
	int n1 = 10;
	int n2 = 20;
	int n3 = 30;

	lista_insertar(lista, (void *)(intptr_t)n1, 0);
	lista_insertar(lista, (void *)(intptr_t)n2, 1);
	lista_insertar(lista, (void *)(intptr_t)n3, 2);

	int suma = 0;
	int suma_esperada = 60;

	size_t iterados = lista_iterar(lista, sumar_elementos, &suma);

	pa2m_afirmar(
		iterados == 3,
		"El iterador interno recorrió los 3 elementos (obtenido = %ld)",
		iterados);
	pa2m_afirmar(
		suma_esperada == 60,
		"La suma total acumulada por el iterador es %i (obtenido = %i)",
		suma_esperada, suma);

	lista_destruir(lista);
}

void lista_pruebas_iterador_externo()
{
	pa2m_nuevo_grupo("PRUEBA DEL ITERADOR EXTERNO DE LISTA");

	lista_t *lista = lista_crear();

	int n1 = 100;
	int n2 = 200;

	lista_insertar(lista, (void *)(intptr_t)n1, 0);
	lista_insertar(lista, (void *)(intptr_t)n2, 1);

	lista_iterador_t *it = lista_iterador_crear(lista);

	pa2m_afirmar(lista_iterador_se_puede_iterar(it) == true,
		     "Se puede iterar con elementos cargados");
	pa2m_afirmar(
		(int)(intptr_t)lista_iterador_obtener_elemento(it) == n1,
		"Al iterarse una posición se espera el primer elemento (obtenido = %i)",
		(int)(intptr_t)lista_iterador_obtener_elemento(it));

	lista_iterador_siguiente(it);
	lista_iterador_siguiente(it);

	pa2m_afirmar(lista_iterador_se_puede_iterar(it) == false,
		     "No se puede iterar tras llegar al final");
	pa2m_afirmar(lista_iterador_obtener_elemento(it) == NULL,
		     "Obtener elemento al final devuelve NULL");

	lista_iterador_destruir(it);

	lista_destruir(lista);
}

void lista_pruebas_destruir_todo()
{
	pa2m_nuevo_grupo(
		"PRUEBA DE OPERACIÓN LISTA DESTRUIR TODO CON DESTRUCTOR");

	lista_t *lista = lista_crear();

	int n1 = 10;
	int n2 = 30;
	int n3 = 50;

	//Inserto en lista
	lista_insertar(lista, (void *)(intptr_t)n1, 0);
	lista_insertar(lista, (void *)(intptr_t)n2, 1);
	lista_insertar(lista, (void *)(intptr_t)n3, 2);

	lista_destruir_todo(lista, destructor_contador);

	//Simulo que le he pasadso un destructor, solamente me interesa que se haya iterado las veces impuestas
	pa2m_afirmar(
		elementos_destruidos == 3,
		"lista_destruir_todo invocó la función destructora 3 veces (obtenido = %i)",
		elementos_destruidos);
}

int main()
{
	//Pruebas para cola
	pa2m_nuevo_grupo("== PRUEBAS TDA COLA ==");
	cola_pruebas_cola_crear_vacia();
	cola_pruebas_cola_null();
	cola_operaciones_encolar_desencolar();
	cola_pruebas_elementos_null();

	//Pruebas para pila
	pa2m_nuevo_grupo("== PRUEBAS TDA PILA ==");
	pila_pruebas_pila_crear_vacia();
	pila_pruebas_pila_null();
	pila_operaciones_apilar_desapilar();
	pila_pruebas_elemento_null();

	//Pruebas para lista + iterador
	pa2m_nuevo_grupo("== PRUEBAS TDA LISTA ==");
	lista_pruebas_crear_lista_vacia();
	lista_pruebas_lista_null();
	lista_pruebas_insertar_y_eliminar();
	lista_pruebas_reemplazar();
	lista_pruebas_buscar();
	lista_pruebas_iterador_interno();
	lista_pruebas_iterador_externo();
	lista_pruebas_destruir_todo();

	return pa2m_mostrar_reporte();
}