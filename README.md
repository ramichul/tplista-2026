# TP: TDA Lista/Pila/Cola
## Información del estudiante

* **Nombre y Apellido**: Ramiro Carrattini
* **Padrón**: 113212
* **Mail**: ramirocarrattini@gmail.com / rcarrattini@fi.uba.ar

---

# Índice

## 1. Instrucciones
### 1.1. Compilar el proyecto
```bash
gcc -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 -g main.c src/*.c -o calculadora_nip
gcc -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 -g src/*.c pruebas/pruebas_alumno.c -o pruebas_alumno
```

### 1.2. Ejecutar las pruebas
```bash
./calculadora_nip [expresión]
./pruebas_alumno
```

### 1.3. Ejecutar el programa con Valgrind
```bash
valgrind --leak-check=full ./calculadora_nip [expresión]
valgrind --leak-check=full ./pruebas_alumno
```
&nbsp;
## 2. Funcionamiento
### Estructuras
##### Lista
Es la estructura principal del proyecto. Está compuesta a la vez por otra estructura más pequeña, los nodos, formados por un puntero que representa su "contenido", el cual se puede acceder libremente por el usuario, y una referencia al siguiente nodo de la lista. Este último campo le da a la lista la característica de ser simplemente enlazada. La lista en sí contiene un puntero tanto al primer nodo como al final, junto con un conteo de elementos o "tope".

Se adjunta una visualización de la estructura:


![](https://i.imgur.com/5OKo6XV.png)


##### Pila y Cola

Ambas son una reutilización de la lista, por lo que comparten su estructura con ella. Su definición dentro del código es simplemente un puntero a una lista.

##### Iterador Externo

Se utiliza para iterar sobre la lista. Internamente contiene un puntero a un nodo específico de la lista. Al crearse, este apunta al `inicio` de la lista.
&nbsp;
### Primitivas
##### Lista

**`lista_t *lista_crear()`**: Crea una lista vacía y devuelve un puntero a la misma. Devuelve `NULL` en caso de error. Internamente, se realiza una reserva de memoria y se inicializan los 3 campos de la estructura mediante asignaciones simples. 
Su complejidad es de $O(1)$.


**`bool lista_vacia(lista_t *lista)`**: Devuelve `true` si la lista está vacía. Una lista nula se considera vacía. Internamente, se realizan chequeos simples relacionados al valor de `cantidad_nodos`. 
Su complejidad es $O(1)$.


**`size_t lista_cantidad(lista_t *lista)`**: Devuelve la cantidad de elementos en la lista o `0` en caso de error. 
Simplemente se devuelve el valor actual de `cantidad_nodos`, por lo que su complejidad es $O(1)$.


**`lista_t *lista_insertar(lista_t *lista, void *elemento)`**: Inserta un elemento al final de la lista. Devuelve la lista o `NULL` en caso de error. Su funcionamiento es el siguiente:
1. Se reserva memoria para un nuevo nodo que contiene el `dato` a insertar. 
2. Si la lista está vacía, se actualizan `inicio` y `fin` para que apunten al nuevo nodo.
3. En caso contrario, se utiliza el puntero `fin` para encontrar lo que antes era el último nodo. Se hace apuntar a `siguiente_nodo` y `fin` al nuevo nodo.
4. Se incrementa `cantidad_nodos`.

Una visualización simplificada de lo que hace la función se puede ver en el siguiente diagrama:

![](https://i.imgur.com/lAAVhI6.png)

Su complejidad es $O(1)$ ya que no necesita iterar sobre la lista (solo reasignar datos) para cumplir su función.

**`lista_t *lista_insertar_posicion(lista_t *lista, size_t posicion, void *elemento)`**: Inserta un elemento en la posición dada de la lista. Devuelve la lista o NULL en caso de error. Funciona así:
1. Si `posicion >= lista_cantidad(lista)`, esta función es idéntica a `lista_insertar`. Se delega la tarea a esta función.
2. Se reserva memoria para un nuevo nodo que contiene el `dato` a insertar.
3. Se busca el nodo que está actualmente en la posición en la que se va a insertar. Este será el `siguiente_nodo` del nuevo nodo.
4. Se busca el nodo anterior al que fue buscado en el paso 3, y se actualiza su puntero `siguiente_nodo` al nuevo nodo.
5. Se incrementa `cantidad_nodos`.

Una visualización simplificada de lo que hace la función se puede ver en el siguiente diagrama:


![](https://i.imgur.com/3lN744X.png)


Al tener que iterar para buscar nodos en posiciones intermedias dentro de la lista, la función recibe una complejidad de $O(n)$.

**`void *lista_obtener(lista_t \*lista)`**: Devuelve el último elemento de la lista (si existe). En caso de error devuelve NULL. Internamente, accede directamente a `lista->fin->contenido` y lo devuelve. 
Su complejidad es $O(1)$.

**`void *lista_obtener_posicion(lista_t *lista, size_t posicion)`**: Dada una `posicion` de la lista, devuelve el elemento en esa `posicion`. En caso de error devuelve NULL. 
Internamente, la función avanza en la lista `posicion` veces y devuelve el contenido del nodo en esa posición. Su complejidad es $O(n)$.

**`void *lista_eliminar(lista_t *lista)`**: Elimina el último elemento de la lista (si existe) y lo devuelve. En caso de error devuelve NULL. Su funcionamiento es el siguiente:
1. Identifica el nodo a eliminar (al que apunta `lista->fin`).
2. Luego, identifica el nodo anterior a este con la función `lista_buscar_nodo`.
3. Antes de eliminar, guarda el contenido del último nodo en un puntero auxiliar.
4. Actualiza `lista->fin` para que apunte al nodo anterior al último nodo.
5. Libera la memoria reservada para el último nodo.
6. Disminuye `cantidad_nodos`.

Al tener que iterar para buscar nodos en posiciones intermedias dentro de la lista, la función recibe una complejidad de $O(n)$.

**`void *lista_eliminar_posicion(lista_t *lista, size_t posicion)`**: Elimina un elemento de la lista en la `posicion` dada. Devuelve el elemento eliminado si la `posicion` es válida. En caso de error devuelve `NULL`. Funciona así:
1. Si se busca eliminar al inicio, se llama `lista_eliminar_inicio`. Esta hace algunas asignaciones especificas a ese caso, pero su funcionamiento es muy similar al resto de la función.
2. Si `posicion == lista_cantidad(lista)-1`, esta función es idéntica a `lista_eliminar`. Se delega la tarea a esta función.
3. Busca el nodo a eliminar y su anterior con la función `lista_buscar_nodo`.
4. Antes de eliminar, guarda el contenido del último nodo en un puntero auxiliar.
5. Hace que el nodo anterior apunte directamente al nodo siguiente del nodo que se eliminará.
6. Disminuye `cantidad_nodos`.

Una visualización simplificada de lo que hace la función se puede ver en el siguiente diagrama:


![](https://i.imgur.com/juFvcGy.png)


Al tener que iterar para buscar nodos en posiciones intermedias dentro de la lista, la función recibe una complejidad de $O(n)$.

**`bool lista_buscar(lista_t *lista, void *elemento, int (*comparador)(const void *, const void *), size_t *posicion)`**: Busca un `elemento` en la lista secuencialmente y devuelve `true` si lo encuentra. Si `posicion` es no nulo, almacena la `posicion` del primer `elemento` encontrado. Si no existe el elemento devuelve `false` y no se modifica `posicion`. Su funcionamiento es el siguiente:
1. Se empieza por el primer nodo de la lista.
2. Mientras que se pueda avanzar en la lista y no se haya encontrado lo buscado, se ejecuta `comparador` con el contenido del nodo actual y el `elemento` pasado por parametro.
3. Se va contando la cantidad de iteraciones en donde fallo `comparador`.
4. Una vez finalizada la busqueda y si fue encontrado el elemento, se actualiza `posicion` si es no nula.

Su complejidad es $O(n)$ ya que en el peor caso sería necesario recorrer toda la lista si el `elemento` buscado no está presente en ella.

**`size_t lista_con_cada_elemento(lista_t *lista, bool (*f)(void *, void *), void *extra)`**: Recorre los elementos de la lista y aplica a cada uno la función `f`. Cuando la función `f` devuelve `false` se deja de recorrer la lista. Devuelve la cantidad de elementos a los cuales se le aplicó `f`. Esta función corresponde a la implementación del **iterador interno** para la lista.

Su complejidad individual es de $O(n)$ ya que se itera sobre la cantidad total de $n$ nodos pertenecientes a la lista. Sin embargo, la función `f` puede afectar este valor. Si se considera a la variable $x$ como la cota de la complejidad de `f`, una manera más precisa de representar la complejidad final del iterador es $O(n*x)$.

**`void lista_destruir_todo(lista_t \*lista, void (*destructor)(void *))`**: Destruye la lista aplicando la función destructora a cada elemento.
Su complejidad individual es de $O(n)$ ó $O(n*x)$ por razones similares a la función anterior.

**`void lista_destruir(lista_t \*lista)`**: Destruye la lista. Esta función es una forma reducida de `lista_destruir_todo`. Su complejidad es de $O(n)$.

Para el iterador externo:

**`lista_iterador_t *lista_iterador_crear(lista_t *lista)`**: Crea un iterador externo para la lista. Realiza reservas de memoria y asignaciones de valores simples. Su complejidad es $O(1)$.

**`bool lista_iterador_hay_mas_elementos(lista_iterador_t *it)`**: Devuelve `true` si aún quedan elementos por iterar. Realiza un chequeo simple, se asegura que el nodo actual no sea nulo. Su complejidad es $O(1)$.

**`void lista_iterador_avanzar(lista_iterador_t *it)`**: Avanza el iterador a la siguiente iteración. Simplemente accede a `actual->siguiente_nodo`. Su complejidad es $O(1)$.

**`void *lista_iterador_actual(lista_iterador_t *it)`**: Devuelve el elemento de la iteración actual. Su complejidad es $O(1)$.

**`void lista_iterador_destruir(lista_iterador_t *it)`**: Destruye el iterador. Su complejidad es $O(1)$.
&nbsp;
##### Pila

**`pila_t *pila_crear()`**: Crea una pila vacía y devuelve un puntero a la misma. Devuelve `NULL` en caso de error. Su complejidad es de $O(1)$.

**`pila_t *pila_apilar(pila_t *pila, void *elemento)`**: Apila un `elemento` en la pila. Devuelve la pila o `NULL` en caso de error. Llama a `lista_insertar_posicion` con `posicion = 0`, por lo que no se necesita iterar sobre la lista para insertar. Su complejidad es $O(1)$.

**`void *pila_desapilar(pila_t *pila)`**: Desapila un elemento y lo devuelve. Devuelve `NULL` en caso de error. Llama a `lista_eliminar_posicion` con `posicion = 0`, por lo que no se necesita iterar sobre la lista para eliminar. Su complejidad es $O(1)$.

**`void *pila_tope(pila_t *pila)`**: Devuelve el primer elemento de la pila y lo devuelve (o NULL en caso de error). Llama a `lista_obtener_posicion` con `posicion = 0`. Su complejidad es $O(1)$.

**`size_t pila_cantidad(pila_t *pila)`**: Devuelve la cantidad de elementos en la pila. Esto es equivalente a devolver la cantidad de la lista interna de la estructura. Su complejidad es $O(1)$.

**`void pila_destruir_todo(pila_t *pila, void (*destructor)(void *))`**: Destruye la pila aplicando la función destructora a cada elemento. Es funcionalmente idéntica a `lista_destruir_todo`, por lo que comparte su cota de complejidad de $O(n*x)$.

**`void pila_destruir(pila_t *pila)`**: Destruye la pila. Es funcionalmente idéntica a `lista_destruir`, por lo que comparte su cota de complejidad de $O(n)$.
&nbsp;
##### Cola

**`cola_t *cola_crear()`**: Crea una cola vacía y devuelve un puntero a la misma. Devuelve `NULL` en caso de error. Su complejidad es de $O(1)$.

**`cola_t *cola_encolar(cola_t *cola, void *elemento)`**: Encola un `elemento`. Devuelve la cola o `NULL` en caso de error. Llama a `lista_insertar`. Su complejidad es $O(1)$.

**`void *cola_desencolar(cola_t *cola)`**: Desencola un elemento y lo devuelve. Devuelve `NULL` en caso de error. Llama a `lista_eliminar_posicion` con `posicion = 0`, por lo que no se necesita iterar sobre la lista para eliminar. Su complejidad es $O(1)$.

**`void *cola_frente(cola_t *cola)`**: Devuelve el primer elemento de la cola y lo devuelve (o NULL en caso de error). Llama a `lista_obtener_posicion` con `posicion = 0`. Su complejidad es $O(1)$.

**`size_t cola_cantidad(cola_t *cola)`**: Devuelve la cantidad de elementos en la cola. Esto es equivalente a devolver la cantidad de la lista interna de la estructura. Su complejidad es $O(1)$.

**`void cola_destruir_todo(cola_t *cola, void (*destructor)(void *))`**: Destruye la pila aplicando la función destructora a cada elemento. Es funcionalmente idéntica a `lista_destruir_todo`, por lo que comparte su cota de complejidad de $O(n*x)$.

**`void cola_destruir(cola_t *cola)`**: Destruye la pila. Es funcionalmente idéntica a `lista_destruir`, por lo que comparte su cota de complejidad de $O(n)$.
&nbsp;
## 3. Respuestas a las preguntas teóricas
 - **Explicar qué es una lista, lista enlazada y lista doblemente enlazada.**
   - Explicar las características de cada una.
   - Explicar las diferencias internas de implementación.
   - Explicar ventajas y desventajas de cada una, si existen.

Una lista es un *Tipo de Dato Abstracto* que permite almacenar distintos elementos dentro de ella. Su principal carácteristica es que no sigue ningún "principio de manipulación" de elementos: para el usuario, todo elemento está disponible para su acceso, y en ningún momento se restringe este mismo. Los elementos dentro de esta lista siguen un orden especificado, y el lugar de cada elemento es numerado con un índice. 

Ambas listas simplemente y doblemente enlazadas se implementan mediante otro *TDA*, el nodo. Este es un contenedor para los datos que además dispone de una referencia a su siguiente (en caso de una lista simplemente enlazada) y su anterior (si es una lista doblemente enlazada). La lista en sí siempre mantiene una referencia a su primer nodo, y opcionalmente puede tener otra para su último nodo.

Existen varias maneras de implementar una lista, sea con un vector estático, uno dinámico o mediante nodos. Estos dos primeros se podrían considerar los más faciles de implementar, ya que no implícan un *TDA* separado como lo hacen las listas simple y doblemente enlazadas. El último método de implementación puede resultar mucho más complejo porque requiere un entendimiento sólido de otra estructura aparte de la lista misma, junto con su forma de manipulación apropiada y su comportamiento bajo diferentes casos.

La ventaja principal de las listas enlazadas es que no requieren reservas de regiones contiguas dentro de la memoria, si no que se reserva una pequeña región dentro de la memoria cada vez que se crea un nodo. Esto puede sumar a las desventajas de una lista implementada mediante un vector, ya que siempre requiere que su memoria reservada sea un bloque contiguo (cosa que puede traer problemas cuando la cantidad de elementos es muy grande). En cambio, la ventaja que tiene sobre sus alternativas es la simplicidad de su implementación.

Dentro de las listas implementadas con vectores, la lista basada en un vector estático es la más desventajosa por su espacio limitado de almacenamiento, cosa que puede resultar contraproducente en las situaciones donde se suele usar la estructura. Una lista que utiliza un vector dinámico no tiene esta desventaja, aunque sigue sufriendo de necesitar espacio contiguo en la memoria. 

Para las listas enlazadas, la lista simplemente enlazada tiene una ventaja sobre la doblemente enlazada también por su simplicidad, mientras que la lista doblemente enlazada gana en el frente de facilidad de manipulación al poder navegarse en ambas direcciones.

Se pueden visualizar las diferentes implementaciones de una lista mencionadas en este diagrama simplificado (dando por sentado que al usar nodos existe la estructura principal de la lista con sus punteros de inicio y fin):

![](https://i.imgur.com/rj2mrUl.png)


 - **Explicar qué es una lista circular y de qué maneras se puede implementar.**

Una lista circular es una implementación alternativa en donde el elemento final y el primer elemento de la lista tienen algún tipo de vínculo. En el caso de una lista simplemente enlazada, el último nodo podría contener una referencia al primer nodo de la lista, en vez de tener un siguiente nodo nulo. Si se trata de una lista doblemente enlazada, el primer y último nodo podrían estar conectados entre sí de dos formas posibles.

Se pueden visualizar las diferentes implementaciones de una lista circular mencionadas en este diagrama simplificado (otra vez obviando la estructura principal de la lista y sus punteros):

![](https://i.imgur.com/dxEbOGf.png)


- **Explicar la diferencia de funcionamiento entre cola y pila.**

Una cola y una pila son ambas una colección de elementos en orden, como lo es la lista. La diferencia entre como funcionan radíca en como se pueden manipular y/o acceder a sus elementos: Una cola sigue el principio *FIFO* (*First In, First Out*), es decir, el primer elemento en entrar es además es el primero en salir, como ocurriria por ejemplo con una cola en un supermercado. Se encola por el final, y se desencola por el frente. Por otro lado, una pila sigue el principio *LIFO* (*Last In, First Out*). El ultimo elemento en entrar es el primero en salir: si se piensa, por ejemplo, en una pila de papeles a revisar, generalmente los primeros en ser vistos son los más recientes. Se apila y desapila por el elemento de arriba, o el tope.

 Se puede observar como se mueven los elementos dentro de una cola o una pila en los siguientes diagramas:

![](https://i.imgur.com/CDwNwpX.png)

- **Explicar la diferencia entre un iterador interno y uno externo.**

Un iterador interno es aquel que recibe únicamente una función del usuario, y luego se encarga de aplicarla sobre cada elemento de la colección. Es decir, la iteración no está a cargo del usuario, solo que se hace con ella.

Por otro lado, cada paso del iterador externo está a cargo del usuario: el usuario elige cuando avanzar y cuando no, cuando aplicar una función y cuando no y que funciones aplicar sobre que elementos. Se dá la libertad total al usuario de iterar sobre la lista como lo necesite.

Otra diferencia entre ambos es que mientras el iterador interno se implementa mediante una función, el iterador externo es un *TDA* entero aparte que complementa la estructura principal.