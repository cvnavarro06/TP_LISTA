<div align="left">
    <img width="32px" src="img/algo2.svg">
</div>

# TP - TDA Lista/Pila/cola

## Información personal

* **Nombre** = Constantino Valentín Navarro
* **Padrón** = 114821
* **E-mail** = cvnavarro@fi.uba.ar
* **User de github** = cvnavarro06

---

## Índice
* [1. Instrucciones para el uso correcto del programa](#1-instrucciones-para-el-uso-correcto-del-programa)
  * [Compilación](#compilación)
  * [Correr programa](#correr-programa)
  * [Correr valgrind](#correr-valgrind)
* [2. Funcionamiento](#2-Funcionamiento)
* [3. Estructura](#3-Estructura)
  * [3.1. Diagrama de memoria](#31-Diagrama-de-memoria)
  * [3.2. Análisis de complejidades](#32-Análisis-de-complejidades)
* [4. Decisiones de diseño y/o complejidades de implementación](#4-Decisiones-de-diseño-yo-complejidades-de-implementación)
* [5. Respuestas a las preguntas teóricas](#5-Respuestas-a-las-preguntas-teóricas)
---
<br>

# 1. Instrucciones para el uso correcto del programa

## Compilación
```
make compile NOMBRE=[opcional]
```
---
## Correr programa
```
./<ejecutable> <operador> <conjuntos> ...
```
---
### Mas detalles de compilación
```
make exp
```

---
## Correr pruebas

### Primero compilo las mismas
```
make compile_test NOMBRE_TEST=[Opcional]
```

### Correr pruebas
```
make test
```
---

## Correr valgrind
```
./valgrind --leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes -s ./<ejecutable> <operador> <conjuntos> ...
```
---

## Para más información
```
make manual
```
---
<br>

# 2. Funcionamiento del programa

Este programa simula una especie de calculadora la cual acepta entre [1;+∞] conjuntos. Dichos conjuntos son enviados por el usuario por medio de la línea de comando. <br>
A lo que conjuntos se refiere, podemos ver un ejemplo del mismo: `"12,43,56" "3,2,8,9"`.<br>
La responsabilidad del programa ante recibir `n` parámetros será de ir separando número por número. La forma que tiene de ir separando el conjunto, el programa, será leyendo hasta que encuentre el separador esperado, dicho separador será una coma (`,`). Siguiendo el ejemplo brindado, vemos que se pueden mandar 2 conjuntos con longitudes distintas, hablesé de longitud como cantidad de números entre los separadores. **¿Cómo funciona internamente el programa?**

### Algoritmo interno del programa
Como dijimos anteriormente, este programa es una especie de calculadora la cual calcula, valga la redundancia, los conjuntos enviados por línea de comando, la forma que tiene de calcular es la siguiente:

En la línea de comando, junto al ejecutable, se espera que el usuario, previamente a enviar los conjuntos, mande un operador matemático (Para más información ejecute la línea de comando [make exp](#mas-detalles-de-compilación)).

Luego a los conjuntos se los almacena en la estructura de datos `Cola`, para dicho almacenamiento, un algortimo de `parsear_conjunto()` convertirá el string conjunto a números enteros, el cómo se almacenaran los números en la `cola` es simple, se leerá un número hasta encontrar el separador (`,`) para poder separarlo del conjunto original, luego de separarlo, al número del conjuto, se le cambia el tipo de dato `string -> int`.

Al tener todos los números separados en una cola, la misma, será almacenada dentro de una `lista`, dicha `lista` contendrá a todos los conjuntos enviados por el usuario. En el momento que se van almacenando las `colas` en la `lista` se va calculando cuál es el tamaño más chico de todos los conjuntos, mismamente se hace para saber cuanto de largo tiene el conjunto más largo. **¿Para qué se hace esto?**

### Calculo de conjuntos
Para calcular los conjuntos enviados por el usuario, la longitud mínima es vital para el conjunto a mostrar, ya que le indicaremos al programa hasta que números hacer `x` operación. ¿Por qué se hace eso?

- ¿Acaso tiene sentido hacer una operación de un número con un espacio vacío?
  
  No, por esa razón requerimos de saber cuanto es la longitud mínima, pero ahora tenemos otra pregunta presente

- ¿Qué harémos con el resto de números?
  
  Utlizaremos un dato anteriormente mencionado, _longitud máxima_. Con este dato rellenaremos hasta el máximo simbolizando un espacio vacío (`E`).

Ahora que tenemos esos conceptos cubiertos, pasemos a como se calculan los conjuntos.

Recordemos que cada conjunto esta almacenado en una `cola`, aprovecharemos su caracteristica principal (**FIFO**) para calcular según el espacio en donde se encuentra cada número.

- ¿Tiene sentido calcular el primer número con alguno en otra posición?

  La respuesta es que no, se tienen que calcular los que estan en la misma posición en distintos conjuntos.


## Flujo del `main.c`

DIA

GRA

MA

---

## Funciones de [`main.c`](main.c)

### parsear_conjunto()
Esta función se encargará de ir parseando todos los números del conjunto e ir guardandolos en una estructura de datos `cola`.<br>
La forma en que la función guarda los numeros es en base a separar cada número, tomando como separador (`,`), cuando cada número es separado se almacenará en cada contenedor/nodo de `cola`.

#### Complejidad
**O(n)**: La función tiene un proceso recursivo, el cuál esta demostrado que agrega una complejidad O(n), por otro lado la forma en que se lee cada número separado 

### calculadora_de_conjuntos()
Esta función se encargará de ir sumando los números correspondientes siguiendo la lógica explicada [**aquí**](#calculo-de-conjuntos).


### rellenar_espacios()
Esta función se encargará de rellenar los espacios donde la `calculadora_de_conjuntos()` ha dejado vacios, para más información de click [**aquí**](#calculo-de-conjuntos) 

#### Complejidad
**O(n)**: Al tener que utilizar un iterador que recorrerá `n` veces se determina dicha complejidad. Como adicional agrego al analisis que la complejidad de la función `sprintf()` es despreciable ya que recorrerá un máximo de 2 veces por iteración volviendolo despreciable al saber la cantidad de veces (`m`).


# Funciones de `lista.c`

## Desiciones de diseño de lista.c

### Estructura de `lista`
```
struct lista
{
  struct nodo* cabeza;
  struct nodo* final;
  size_t cantidad;
};
```

Para implementar una estructura de `lista` utilice una forma de almacenar datos a base de `nodos`, el mismo `struct lista` tendrá acceso a una cabeza de lista y a un final de la misma, esto nos permitirá tener más control de flujo a la hora de querer hacer operaciones en la misma.

Como adicional he agregado un campo de `cantidad` el cual representa la cantidad de elementos que se encuentrar en la estructura de datos.

### Diagrama de memoria


### Implementación de la estructura
Para armar la estructura de `lista` se opto por elegir el tipo de **lista simplemente enlazada**.



---

### lista_crear()
Crea una lista y la devuelve

#### Complejidad

**O(1)**: La función reserva un bloque de memoria para la estructura principal (`struct lista`) usando `malloc` e inicializa sus campos (`cantidad, cabeza, final`).

### lista_cantidad()
Devuelve la cantidad de elementos que almacena el `struct lista`.

#### Complejidad

**O(1)**: Accede de manera directa al campo `cantidad` almacenado previamente en la estructura de la lista y se retorna.

### lista_esta_vacia()
Devuelve **true** si la lista esta vacía

#### Complejidad

**O(1)**: Accede al campo `cantidad` y evalúa si es menor o igual a **0**, retornando el valor booleano resultante.

### lista_insertar()
Inserta un dato en la posición dada de la lista y devuelve **true** si pudo lograrlo. Si la `posición` está mas allá del final de la lista, no se puede insertar y devuelve **false**.

#### Complejidad

**O(n)**: Previamente a recorrer la lista para insertar, en caso de querer insertar al principio y exactamente al final de la lista, esta operación tiene una complejidad de tiempo constante **O(1)** verificando las cabeceras, en el peor de los casos (insertar en una `posición` del medio).

### lista_eliminar()
Elimina un dato en la `posición` dada de la `lista` y devuelve el elemento eliminado. En caso de que la posición esté mas allá del final de la `lista`, no se va a poder eliminar el elemento y devolverá **NULL**.

#### Complejidad

**O(n)**: Se iterará linealmente utilizando un bucle while sobre los nodos de la estructura desde la cabeza hasta dar con el nodo ubicado en la posición objetivo, desenlazándolo y liberando su memoria.
En el mejor de los casos será **O(1)** si se desea eliminar los elementos de las cabeceras (`inicio, final`)

### lista_remplazar()
Reemplaza un dato en la posición dada de la lista y lo devuelve.

#### Complejidad

**O(n)**: Se iterará un bucle while para avanzar nodo a nodo hasta coincidir con la `posición` solicitada y sobreescribir el valor de  `data`.

### lista_obtener()
Devuelve el elemento que se encuentra en la posición solicitada de la `lista`.

#### Complejidad

**O(n)**: Se realiza un bucle while desde el inicio para poder devolver la información almacenada en ese nodo específico.

### lista_buscar()
Busca un elemento en la `lista` utilizando una función de comparación (comparador), en caso de encontrarlo devolverá la `posición` en la que se encuentra pero si no lo encuentra devuelve **-1**. Si se provee el puntero encontrado se almacenará allí el `elemento` encontrado o **NULL** en caso de no hallarse, siempre y cuando sea distinto de **NULL**.

#### Complejidad

**O(n)**: Se realiza una iteración lineal evaluando nodo por nodo invocando a la función comparador(buscado, actual->data). En el peor de los casos (el elemento está al final o no existe), recorrerá la lista entera.

### lista_iterar()
Recorre la lista aplicando la función `f` sobre los elementos y devuelve la `cantidad` total de veces que fue invocada dicha función. Si la función `f` devuevle false, se deja de iterar.

#### Complejidad

**O(n)**: Itera la lista evaluando de forma continua `!f(actual->data, extra)` en un bucle while hasta que se acaben los nodos o se altere la bandera **stop**.

### lista_destruir()
Libera la lista y toda la memoria asociada

#### Complejidad

**O(n)**: Se implementa un diseño recursivo para la estructura de la función. Va a ir liberando nodo por nodo repetidas veces hasta llegar al final para liberar finalmente el contenedor principal (`lista`).

### lista_destruir_todo()
Libera la `lista` y toda la memoria de los nodos asociados, aplicandole una función destructora enviada por parámetro para liberar el dato almacenado en la `lista`, el cual contendrá memoria reservada dinámicamente.

#### Complejidad

**O(n)**: Funciona con un modelo de llamadas recursivas idéntico al de lista_destruir(), pero con un cambio adicional de invocar la función `destructor(data)`.

---

## Iterador de la lista

¿A que nos referimos con **Iterador de la lista**?

Cuando hablamos de un iterador de la estructura de datos $lista$, hablamos de un TDA **externo** el cuál proveé entre sus cualidades, una lista breve de funciones capaces de poder controlar un recorrido/iteración de lista mucho más flexible. Cuando nos referimos a controlar la iteración de la $lista$

---

### lista_iterador_crear()
Crea un iterador de lista y lo devuelve.

#### Complejidad

**O(1)**: Solo se reservará un bloque de memoria.

### lista_iterador_se_puede_iterar()
Devuelve **true** si hay mas elementos para iterar.

#### Complejidad

**O(1)**: Evalua si el elemento en donde se encuentra es distinto de **NULL** por lo que solamente hace una verificación

### lista_iterador_siguiente()
Avanzará al siguiente nodo de la lista que contiene el iterador

#### Complejidad

**O(1)**: Solamente hará una operación de desplazarse al siguiente nodo de la `lista` del iterador.  

### lista_iterador_obtener_elemento()
Devuelve el `dato` almacenado en el elemento actual de la `lista` que contiene el iterador.

#### Complejidad

**O(1)**: Solamente accederá al elemento del nodo actual, por ende se basa en una sola operación. 

### lista_iterador_destruir()
Se encargará de destruir `iterador` y su memoria perteneciente.

#### Complejidad

**O(1)**: Se realiza una única operación de liberació (`free()`) a la estructura `iterador`.

---
<br>

# Funciones de pila.c

## Desiciones de diseño

### Estructura de `pila`
```
struct pila
{
  lista_t *lista;
};
```
Para armar la estructura de pila, opté por utilizar el struct de lista, pero **¿Por qué?**

Al tener una estrctura de `lista` como contenedor, puedo optar por resolver las funciones primitivas de `pila` con funciones primitivas de `lista`, como resultado obtendremos que el responsable de que las estructuras de datos funcionen correctamente es `lista`.

La única responsabilidad de la estructura de pila es en como hace el flujo de información, recordemos que esta estructura sigue el principio de (**LIFO**)

---

### pila_crear()
Crea una `pila` y lo devuelve.

#### Complejidad
**O(1)**: Crea una pila en base a la función [`lista_crear()`](#lista_crear).

### pila_apilar()
Agrega un elemento en el tope de la `pila` y devuelve un valor booleano.

#### Complejidad
**O(1)**: Invoca a `lista_insertar()`. Insertar en la posición 0 de la lista enlazada solo requiere actualizar el puntero a la cabeza (lista->cabeza) e incrementar el contador, operando en tiempo constante.

### pila_desapilar()
Remueve el elemento ubicado en el tope de la pila y devuelve su valor.

#### Complejidad
**O(1)**: Llama a `lista_eliminar()` y elimina la cabeza de la lista lo cual implica desvincular el primer nodo y liberar su bloque en O(1) sin necesidad de realizar ninguna iteración.

### pila_tope()
Devuelve el elemento que se encuentra en el tope de la `pila`

#### Complejidad
**O(1)**: Utiliza `lista_obtener()` y accede al elemento inicial se resuelve inmediatamente leyendo el atributo de datos en la cabeza de la lista.

### pila_esta_vacia()
Devuelve **true** si la lista se encuentra vacía.

#### Complejidad
**O(1)**: Utiliza la función `lista_esta_vacia()`, la cual evalúa directamente el atributo cantidad en tiempo constante.

### pila_cantidad()
Devuelve la cantidad total de elementos actuales almacenados.

#### Complejidad
**O(1)**: Utiliza la función `lista_cantidad()` para retornar directamente el valor del contador almacenado en la estructura interna.

### pila_destruir()
Libera la memoria de la estructura.

#### Complejidad
**O(n)**: Utilza la función **lista_destruir()** en donde se recorre de manera iterativa cada nodo siendo de tiempo `n`.

# Funciones de cola.c

## Desiciones de diseño

### Estructura de `cola`

```
struct cola
{
  lista_t *lista;
};
```
Al igual que la estructura de `pila`, opté por delegar todas las operaciones a las primitivas de `lista`. La única diferencia sería en como se comporta el flujo de información, ya que la cola sigue el principio de (**FIFO**).

---

### cola_crear()
Crea una `cola` y la devuelve

#### Complejidad
**O(1)**: Para crear la estructura se llama a la función `lista_crear()` la cual tiene un tiempo de ejecución constante.

### cola_encolar()
Agrega un elemento al final de la cola y devuelve true si la operación tuvo éxito.

#### Complejidad
**O(1)**: Para encolar,la función llama a `lista_insertar()` y le indicamos que queremos insertar exactamente en la última posición, la propia función accedera de forma directa a través de su puntero `lista->final`, lo que evita iterar los nodos y convierte a esta operación en tiempo constante

### cola_desencolar()
Eliminará el elemento que se encuentra al frente, o sea el primero, de la `cola`

#### Complejidad
**O(1)**: Utiliza `lista_eliminar()` para remover el elemento, en donde se eliminará en la posición cero.

### cola_frente()
Devuelve el elemento que se encuentra al frente de la `cola` pero sin removerlo de la misma estructura.

#### Complejidad
**O(1)**: Se llama a la función `lista_obtener()` y se accede al primer elemento de la lista. Dicha operación es inmediata ya que solo lee el dato que se encuentra en la cabeza.

### cola_esta vacía()
Devuelve un valor booleano indicando si la estructura se encuentra vacía o no.

#### Complejidad
**O(1)**: Se llama a la función `lista_esta_vacia()` para verificar si la estructura de datos está vacía. La misma operación tiene una complejidad computacional constante.

### cola_cantidad()
Devuelve la cantidad de elementos que hay almacenados en la estructura.

#### Complejidad
**O(1)**: Se delega dicha operación a la función `lista_cantidad()`, dicha operación es inmediata.

### cola_destruir()
Libera toda la memoria asociada a la estructura de datos.

#### Complejidad
**O(n)**: Se llama a la función `lista_destruir()` para destruir cada nodo/contenedor asociado a la estructura. Dicha operación tiene una complejidad lineal. 

# Decisiones de diseño
