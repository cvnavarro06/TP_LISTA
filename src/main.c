#include "cola.h"
#include "pila.h"
#include "lista.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#define ROJO_INTENSO "\x1b[0;91m"
#define AMARRILO_INTENSO "\x1b[1;93m"

#define RESETEO_DE_COLOR   "\x1b[0m"


#define EXITO 0
#define ERROR -1

#define OPERADOR 1
#define CONJUNTOS 2

#define OPERADOR_SUMA '+'
#define OPERADOR_RESTA '-'
#define OPERADOR_DIVISION '/'
#define OPERADOR_MULTIPLICACION '*'

#define CARACTER_NULO '\0'
#define SEPARADOR ','
#define EMPTY 'E'

const char *FORMATO_ESCRITURA_CONJUNTO = "%d%c";

const char *FORMATO_ESCRITURA_CONJUNTO_VACIO = "E%c";

/*
 * La cola debe estar previamente creada.
 *
 * Devuelve true si la operación ha sido exitosa, caso contrario devuelve false por algún en la operación.
*/
bool parsear_conjunto(cola_t *cola, char *conjunto, char separador)
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

	return parsear_conjunto(cola, conjunto + 1, separador);
}

/*
 * Se espera una varable booleana para indicar si ocurrio un error de division por cero.
 * Por otro lado se espera una variable de indice para analizar si realizar una operación o una asignación.
 *
 * Procede a hacer la operacion en base al operador.
*/
void calculador_con_operador(int *numero, int numero_2, char operador, size_t j, bool *err_div)
{
	if (j == 0) {
		*numero = numero_2;
	} else {

		if (operador == OPERADOR_SUMA) {
			*numero += numero_2; 
		} else if (operador == OPERADOR_RESTA) {
			*numero -= numero_2;
		} else if (operador == OPERADOR_MULTIPLICACION) {
			*numero *= numero_2;
		} else if (operador == OPERADOR_DIVISION) {
			
			if (numero_2 == 0) {
				*err_div = true;
			} else {
				*numero /= numero_2;
			}
		}
	}
}

/*
 * //
 *
 *	Devuelve la longitud del número y si es negativo se le suma uno por el signo.
*/
size_t longitud_del_numero(int numero)
{
	double num;

	if (numero == 0) {
		return 1;
	} else if (numero < 0) { //Caso número menor a 0 (negativo)
		//Sumo 1 más para contar el signo menos
		num = log10(abs(numero)) + 2;
	} else {
		num = log10(numero) + 1;
	}
	
	return (size_t)num;
}

/*
 * Se espara una lista válida junto a su tope de conjuntos (longitud mínima)
 *
 * Devuelve un string con un nuevo conjunto, almacenado en el HEAP, aplicandolé la operación indicada
 * 
*/
char *calculadora_de_conjuntos(lista_t *lista, int tope, char operador)
{
	if (lista == NULL || operador == ' ') {
		return NULL;
	}

	//Multiplico por 3 para abarcar un espacio "Empty" + separador + caractér nulo
	char *conjunto_final = malloc(sizeof(char) * 3);

	if (conjunto_final == NULL) {
		return NULL;
	}
	//Inicializo conjunto_final
	conjunto_final[0] = CARACTER_NULO;

	bool err = false;

	for (size_t i = 0; i<tope && !err; i++) {
		
		int numero = 0;

		bool err_div = false;

		size_t j = 0;

		//Utilizo el iterador de listas
		lista_iterador_t *iterador = lista_iterador_crear(lista);

		while(lista_iterador_se_puede_iterar(iterador) && !err_div) {

			cola_t *cola_actual = (cola_t*)lista_iterador_obtener_elemento(iterador);

			int data = (int)(intptr_t)cola_desencolar(cola_actual);
		
			calculador_con_operador(&numero, data, operador, j, &err_div);
			
			j++;

			lista_iterador_siguiente(iterador);
		}
		
		lista_iterador_destruir(iterador);

		size_t tamanio_conjunto = strlen(conjunto_final);

		if (!err_div){

			size_t size = longitud_del_numero(numero);

			//Sumo +2 para el separador y el caractér nulo
			char *aux = realloc(conjunto_final, sizeof(char) * (size + tamanio_conjunto + 2));

			if (aux == NULL) {
				err = true;
			} else {
				conjunto_final = aux;

				sprintf(conjunto_final + tamanio_conjunto, FORMATO_ESCRITURA_CONJUNTO, numero, SEPARADOR);

			}
		} else {
			
			//Sumo +3 para el E, el separator y el caractér nulo
			char *aux = realloc(conjunto_final, tamanio_conjunto + 3);

			if (aux == NULL) {
				err = true;
			} else {
				conjunto_final = aux;
				sprintf(conjunto_final + tamanio_conjunto, FORMATO_ESCRITURA_CONJUNTO_VACIO, SEPARADOR);
			}

		}
	}

	if (err) {
		return NULL;
	}

	return conjunto_final;
}


/*
 * Se espera un conjunto válido
 *	
 * Devuelve el conjunto con los espacios restantes marcados como vacio (E).
 * Se espera que el usuario libere la memoria del conjunto.
 * En caso de error se libera automaticamente la memoria asociada al conjunto y devuelve NULL.
*/
char *rellenar_espacios_vacios(char *conjunto, int long_min, int long_max)
{
	if (conjunto == NULL) {
		return NULL;
	}
	
	bool err = false;

	size_t tamanio_conjunto_nuevo = strlen(conjunto);

	int espacios_vacios = long_max - long_min;

	//Multiplico por 2 para inlcuir los separadores + 1 del caractér nulo.
	char *aux = realloc(conjunto, sizeof(char) * (tamanio_conjunto_nuevo + (((size_t)espacios_vacios * 2) + 1)));

	if (aux == NULL) {
		free(conjunto);
		err = true;;

	} else {
		conjunto = aux;
		
		for (int k = 0; k<espacios_vacios; k++) {
			tamanio_conjunto_nuevo = strlen(conjunto);
			sprintf(conjunto + tamanio_conjunto_nuevo, FORMATO_ESCRITURA_CONJUNTO_VACIO, SEPARADOR);
		}
	}

	if (err) {
		return NULL;
	}

	return conjunto;
}


int main(int argc, char **argv)
{
	if (argc < 2) {

		printf("=============================\n"
			   "  Linea de comando esperada\n"
			   "=============================\n"
			   ROJO_INTENSO"    Ha ocurrido un error\n\n"RESETEO_DE_COLOR
			   "- ./[ejecutable] [operador] (conjuntos) ...\n\n"
			   "- Lista de operadores: [+, -, *, /]\n");

		return ERROR;
	}

	lista_t *lista = lista_crear();

	int longitud_max = -1;

	int longitud_min = 1000000000;
	
	bool err = false;

	//for para cargar la lista de colas con los conjuntos
	for (size_t i = CONJUNTOS; i < (size_t)argc && !err; i++) {

		cola_t *cola = cola_crear();
		
		if (!parsear_conjunto(cola, argv[i], SEPARADOR)) {
			err = true;
		} else {
		
			int longitud = (int)cola_cantidad(cola);
			
			if (longitud > longitud_max) longitud_max = longitud;
			
			if (longitud < longitud_min) longitud_min = longitud;
			
			lista_insertar(lista, cola, i - 2);
		}
	}

	char *conjunto_nuevo = calculadora_de_conjuntos(lista, longitud_min, *argv[OPERADOR]);

	if (conjunto_nuevo == NULL) {
		err = true;
	}

	if (!err){

		if (longitud_max != longitud_min) {
			conjunto_nuevo = rellenar_espacios_vacios(conjunto_nuevo, longitud_min, longitud_max);

			if (conjunto_nuevo == NULL) {
				err = true;
			}
		}
	}

	if (err) {
		lista_destruir_todo(lista, (void (*)(void*))cola_destruir);
		return ERROR;
	}

	size_t tamanio_conjunto = strlen(conjunto_nuevo);

	conjunto_nuevo[tamanio_conjunto - 1] = CARACTER_NULO;

	printf(AMARRILO_INTENSO"%s\n"RESETEO_DE_COLOR, conjunto_nuevo);

	free(conjunto_nuevo);

	lista_destruir_todo(lista, (void (*)(void*))cola_destruir);

	return EXITO;
}
