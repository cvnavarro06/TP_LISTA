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


# Funciones de `lista.c`

## Desiciones de diseño de lista.c


### Diagrama de memoria

Respondo la pregunta 1


### Estructura de `lista`

---

## lista_crear()
Crea una lista y la devuelve

#### Complejidad

**O(1)**: La función reserva un bloque de memoria para la estructura principal (`struct lista`) usando `malloc` e inicializa sus campos (`cantidad, cabeza, final`).

## lista_cantidad()
Devuelve la cantidad de elementos que almacena el `struct lista`.

#### Complejidad

**O(1)**: Accede de manera directa al campo `cantidad` almacenado previamente en la estructura de la lista y se retorna.

## lista_esta_vacia()
Devuelve **true** si la lista esta vacía

#### Complejidad

**O(1)**: Accede al campo `cantidad` y evalúa si es menor o igual a **0**, retornando el valor booleano resultante.

## lista_insertar()
Inserta un dato en la posición dada de la lista y devuelve **true** si pudo lograrlo. Si la `posición` está mas allá del final de la lista, no se puede insertar y devuelve **false**.

#### Complejidad

**O(n)**: Previamente a recorrer la lista para insertar, en caso de querer insertar al principio y exactamente al final de la lista, esta operación tiene una complejidad de tiempo constante **O(1)** verificando las cabeceras, en el peor de los casos (insertar en una `posición` del medio).

## lista_eliminar()
Elimina un dato en la `posición` dada de la `lista` y devuelve el elemento eliminado. En caso de que la posición esté mas allá del final de la `lista`, no se va a poder eliminar el elemento y devolverá **NULL**.

#### Complejidad

**O(n)**: Se iterará linealmente utilizando un bucle while sobre los nodos de la estructura desde la cabeza hasta dar con el nodo ubicado en la posición objetivo, desenlazándolo y liberando su memoria.
En el mejor de los casos será **O(1)** si se desea eliminar los elementos de las cabeceras (`inicio, final`)

## lista_remplazar()
Reemplaza un dato en la posición dada de la lista y lo devuelve.

#### Complejidad

**O(n)**: Se iterará un bucle while para avanzar nodo a nodo hasta coincidir con la `posición` solicitada y sobreescribir el valor de  `data`.

## lista_obtener()
Devuelve el elemento que se encuentra en la posición solicitada de la `lista`.

#### Complejidad

**O(n)**: Se realiza un bucle while desde el inicio para poder devolver la información almacenada en ese nodo específico.

## lista_buscar()
Busca un elemento en la `lista` utilizando una función de comparación (comparador), en caso de encontrarlo devolverá la `posición` en la que se encuentra pero si no lo encuentra devuelve **-1**. Si se provee el puntero encontrado se almacenará allí el `elemento` encontrado o **NULL** en caso de no hallarse, siempre y cuando sea distinto de **NULL**.

#### Complejidad

**O(n)**: Se realiza una iteración lineal evaluando nodo por nodo invocando a la función comparador(buscado, actual->data). En el peor de los casos (el elemento está al final o no existe), recorrerá la lista entera.

## lista_iterar()
Recorre la lista aplicando la función `f` sobre los elementos y devuelve la `cantidad` total de veces que fue invocada dicha función. Si la función `f` devuevle false, se deja de iterar.

#### Complejidad

**O(n)**: Itera la lista evaluando de forma continua `!f(actual->data, extra)` en un bucle while hasta que se acaben los nodos o se altere la bandera **stop**.

## lista_destruir()
Libera la lista y toda la memoria asociada

#### Complejidad

**O(n)**: Se implementa un diseño recursivo para la estructura de la función. Va a ir liberando nodo por nodo repetidas veces hasta llegar al final para liberar finalmente el contenedor principal (`lista`).

## lista_destruir_todo()
Libera la `lista` y toda la memoria de los nodos asociados, aplicandole una función destructora enviada por parámetro para liberar el dato almacenado en la `lista`, el cual contendrá memoria reservada dinámicamente.

#### Complejidad

**O(n)**: Funciona con un modelo de llamadas recursivas idéntico al de lista_destruir(), pero con un cambio adicional de invocar la función `destructor(data)`.

---

## Iterador de la lista

Respondo la pregunta del iterador (4)

## lista_iterador_crear()
Crea un iterador de lista y lo devuelve.

#### Complejidad

**O(1)**: Solo se reservará un bloque de memoria.

## lista_iterador_se_puede_iterar()
Devuelve **true** si hay mas elementos para iterar.

#### Complejidad

**O(1)**: Evalua si el elemento en donde se encuentra es distinto de **NULL** por lo que solamente hace una verificación

## lista_iterador_siguiente()
Avanzará al siguiente nodo de la lista que contiene el iterador

#### Complejidad

**O(1)**: Solamente hará una operación de desplazarse al siguiente nodo de la `lista` del iterador.  

## lista_iterador_obtener_elemento()
Devuelve el `dato` almacenado en el elemento actual de la `lista` que contiene el iterador.

#### Complejidad

**O(1)**: Solamente accederá al elemento del nodo actual, por ende se basa en una sola operación. 

## lista_iterador_destruir()
Se encargará de destruir `iterador` y su memoria perteneciente.

#### Complejidad

**O(1)**: Se realiza una única operación de liberació (`free()`) a la estructura `iterador`.

---
<br>

## Funciones de pila.c

## Funciones de cola.c

# Decisiones de diseño
