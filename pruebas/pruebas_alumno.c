#include "pa2m.h"
#include "../src/cola.h"
#include "../src/lista.h"
#include "../src/pila.h"

int comparador_enteros_son_iguales(const void *elemento1, const void *elemento2)
{
	bool enteros_son_iguales = *((int *)elemento1) == *((int *)elemento2);
	if (enteros_son_iguales)
		return 0;
	return -1;
}

bool funcion_generica_comparador_enteros(void *elemento1, void *elemento2)
{
	return *((int *)elemento1) == *((int *)elemento2);
}

bool funcion_generica_reemplazar_todos(void *elemento1, void *elemento2)
{
	*((int *)elemento1) = *((int *)elemento2);
	return true;
}

bool comprobar_array_verificaciones(bool *verificaciones, size_t tope)
{
	bool comprobado = true;

	for (size_t i = 0; i < tope; i++) {
		if (!verificaciones[i])
			comprobado = false;
	}

	return comprobado;
}

void lista_crear_devuelve_lista_valida()
{
	lista_t *lista = lista_crear();

	pa2m_afirmar(lista != NULL, "lista_crear() devuelve una lista válida");
	lista_destruir(lista);
}

void lista_crear_devuelve_lista_vacia()
{
	lista_t *lista = lista_crear();

	pa2m_afirmar(lista_vacia(lista),
		     "lista_crear() devuelve una lista vacía");
	lista_destruir(lista);
}

void lista_vacia_toma_lista_nula_como_vacia()
{
	pa2m_afirmar(
		lista_vacia(NULL),
		"lista_vacia() recibe una lista nula y la asume como vacía");
}

void lista_vacia_reconoce_lista_vacia()
{
	lista_t *lista = lista_crear();

	pa2m_afirmar(
		lista_vacia(lista),
		"lista_vacia() recibe una lista vacía y la reconoce como tal");
	lista_destruir(lista);
}

void lista_vacia_reconoce_lista_no_vacia()
{
	lista_t *lista = lista_crear();
	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_insertar(lista, &elementos[i]);
	}

	pa2m_afirmar(
		!lista_vacia(lista),
		"lista_vacia() recibe una lista no vacía y la reconoce como tal");
	lista_destruir(lista);
}

void lista_cantidad_toma_lista_nula_como_vacia()
{
	pa2m_afirmar(
		lista_cantidad(NULL) == 0,
		"lista_cantidad() recibe una lista nula y la asume como vacía");
}

void lista_cantidad_devuelve_0_con_lista_vacia()
{
	lista_t *lista_vacia = lista_crear();

	pa2m_afirmar(lista_cantidad(lista_vacia) == 0,
		     "lista_cantidad() recibe una lista vacía y devuelve 0");
	lista_destruir(lista_vacia);
}

void lista_cantidad_devuelve_valor_correcto()
{
	lista_t *lista = lista_crear();

	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_insertar(lista, &elementos[i]);
	}

	pa2m_afirmar(
		lista_cantidad(lista) == 3,
		"lista_cantidad() devuelve el valor correspondiente de elementos presentes");
	lista_destruir(lista);
}

void lista_insertar_no_agrega_elementos_a_lista_nula()
{
	int dato = 50;
	lista_t *resultado_insertar = lista_insertar(NULL, &dato);

	pa2m_afirmar(
		resultado_insertar == NULL,
		"lista_insertar() no intenta agregar elementos a una lista nula");
}

void lista_insertar_devuelve_puntero_al_insertar_correctamente()
{
	lista_t *lista = lista_crear();
	int dato = 50;
	lista_t *resultado_insertar = lista_insertar(lista, &dato);

	pa2m_afirmar(
		resultado_insertar == lista,
		"lista_insertar() devuelve un puntero a la misma lista cuando se inserta con éxito");
	lista_destruir(lista);
}

void lista_insertar_agrega_elemento_a_lista_vacia()
{
	lista_t *lista = lista_crear();
	int dato = 50;
	lista_insertar(lista, &dato);
	int *elemento_inicio = lista_obtener_posicion(lista, 0);

	pa2m_afirmar(
		elemento_inicio == &dato,
		"lista_insertar() agrega un elemento correctamente a una lista vacía");
	lista_destruir(lista);
}

void lista_insertar_agrega_elemento_a_lista_no_vacia()
{
	lista_t *lista = lista_crear();
	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_insertar(lista, &elementos[i]);
	}

	int *elemento_fin = lista_obtener(lista);

	pa2m_afirmar(
		elemento_fin == &elementos[2],
		"lista_insertar() agrega un elemento correctamente a una lista no vacía");
	lista_destruir(lista);
}

void lista_insertar_agrega_elemento_nulo_correctamente()
{
	lista_t *lista = lista_crear();
	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_insertar(lista, &elementos[i]);
	}
	lista_insertar(lista, NULL);

	void *elemento_fin = lista_obtener(lista);

	pa2m_afirmar(elemento_fin == NULL && lista_cantidad(lista) == 4,
		     "lista_insertar() agrega un elemento nulo correctamente");
	lista_destruir(lista);
}

void lista_insertar_cambia_cantidad_de_elementos_correctamente()
{
	lista_t *lista = lista_crear();
	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_insertar(lista, &elementos[i]);
	}

	pa2m_afirmar(
		lista_cantidad(lista) == 3,
		"lista_insertar() cambia la cantidad de elementos correctamente");
	lista_destruir(lista);
}

void lista_insertar_posicion_no_agrega_elementos_a_lista_nula()
{
	int dato = 50;
	lista_t *resultado_insertar = lista_insertar_posicion(NULL, 0, &dato);

	pa2m_afirmar(
		resultado_insertar == NULL,
		"lista_insertar_posicion() no intenta agregar elementos a una lista nula");
}

void lista_insertar_posicion_devuelve_puntero_al_insertar_correctamente()
{
	lista_t *lista = lista_crear();
	int dato = 50;
	lista_t *resultado_insertar = lista_insertar_posicion(lista, 0, &dato);

	pa2m_afirmar(
		resultado_insertar == lista,
		"lista_insertar_posicion() devuelve un puntero a la misma lista cuando se inserta con éxito");
	lista_destruir(lista);
}

void lista_insertar_posicion_agrega_elemento_a_lista_vacia()
{
	lista_t *lista = lista_crear();
	int dato = 50;
	lista_insertar_posicion(lista, 0, &dato);
	int *elemento_insertado = lista_obtener(lista);

	pa2m_afirmar(
		elemento_insertado == &dato,
		"lista_insertar_posicion() agrega un elemento correctamente a una lista vacía");
	lista_destruir(lista);
}

void lista_insertar_posicion_agrega_elemento_nulo_correctamente()
{
	lista_t *lista = lista_crear();
	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_insertar(lista, &elementos[i]);
	}
	lista_insertar_posicion(lista, 1, NULL);

	void *ultimo_elemento_insertado = lista_obtener_posicion(lista, 1);

	pa2m_afirmar(
		ultimo_elemento_insertado == NULL && lista_cantidad(lista) == 4,
		"lista_insertar_posicion() agrega un elemento nulo correctamente");
	lista_destruir(lista);
}

void lista_insertar_posicion_agrega_elemento_al_principio_correctamente()
{
	lista_t *lista = lista_crear();

	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_insertar(lista, &elementos[i]);
	}

	int dato = 50;
	lista_insertar_posicion(lista, 0, &dato);
	int *elemento_inicio = lista_obtener_posicion(lista, 0);

	pa2m_afirmar(
		elemento_inicio == &dato,
		"lista_insertar_posicion() agrega un elemento al principio correctamente");
	lista_destruir(lista);
}

void lista_insertar_posicion_agrega_elemento_en_el_medio_correctamente()
{
	lista_t *lista = lista_crear();

	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_insertar(lista, &elementos[i]);
	}

	int dato = 50;
	size_t posicion = 1;
	lista_insertar_posicion(lista, posicion, &dato);

	int *elemento_anterior = lista_obtener_posicion(lista, posicion - 1);
	int *elemento_insertado = lista_obtener_posicion(lista, posicion);
	int *elemento_siguiente = lista_obtener_posicion(lista, posicion + 1);

	pa2m_afirmar(
		elemento_anterior == &elementos[0] &&
			elemento_insertado == &dato &&
			elemento_siguiente == &elementos[1],
		"lista_insertar_posicion() agrega un elemento en el medio correctamente");
	lista_destruir(lista);
}

void lista_insertar_posicion_agrega_elemento_al_final_correctamente()
{
	lista_t *lista = lista_crear();

	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_insertar(lista, &elementos[i]);
	}

	int dato = 50;
	size_t posicion = lista_cantidad(lista);
	lista_insertar_posicion(lista, posicion, &dato);
	int *elemento_final = lista_obtener(lista);

	pa2m_afirmar(
		elemento_final == &dato,
		"lista_insertar_posicion() agrega un elemento al final correctamente");
	lista_destruir(lista);
}

void lista_insertar_posicion_agrega_elementos_en_una_posicion_invalida()
{
	lista_t *lista = lista_crear();
	int dato = 50;
	lista_insertar_posicion(lista, 5, &dato);
	int *elemento_final = lista_obtener(lista);

	pa2m_afirmar(
		elemento_final == &dato,
		"lista_insertar_posicion() recibe una posición inválida y agrega el elemento al final de la lista correctamente");
	lista_destruir(lista);
}

void lista_insertar_posicion_cambia_cantidad_de_elementos_correctamente()
{
	lista_t *lista = lista_crear();
	int dato = 50;
	lista_insertar_posicion(lista, 0, &dato);

	pa2m_afirmar(
		lista_cantidad(lista) == 1,
		"lista_insertar_posicion() cambia la cantidad de elementos correctamente");
	lista_destruir(lista);
}

void lista_obtener_ignora_lista_nula()
{
	void *resultado_busqueda = lista_obtener(NULL);

	pa2m_afirmar(resultado_busqueda == NULL,
		     "lista_obtener() no intenta buscar en una lista nula");
}

void lista_obtener_ignora_lista_vacia()
{
	lista_t *lista = lista_crear();

	void *resultado_busqueda = lista_obtener(lista);

	pa2m_afirmar(resultado_busqueda == NULL,
		     "lista_obtener() no intenta buscar en una lista vacía");
	lista_destruir(lista);
}

void lista_obtener_encuentra_elemento_presente()
{
	lista_t *lista = lista_crear();
	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_insertar(lista, &elementos[i]);
	}

	int *resultado_busqueda = lista_obtener(lista);

	pa2m_afirmar(resultado_busqueda == &elementos[2],
		     "lista_obtener() logra encontrar el último elemento");
	lista_destruir(lista);
}

void lista_obtener_encuentra_elemento_presente_y_extrae_datos_correctamente()
{
	lista_t *lista = lista_crear();
	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_insertar(lista, &elementos[i]);
	}

	int *resultado_busqueda = lista_obtener(lista);

	pa2m_afirmar(
		resultado_busqueda == &elementos[2],
		"lista_obtener() logra encontrar el último elemento y extrae sus datos correctamente");
	lista_destruir(lista);
}

void lista_obtener_posicion_ignora_lista_nula()
{
	void *resultado_busqueda = lista_obtener_posicion(NULL, 0);

	pa2m_afirmar(
		resultado_busqueda == NULL,
		"lista_obtener_posicion() no intenta buscar en una lista nula");
}

void lista_obtener_posicion_ignora_lista_vacia()
{
	lista_t *lista = lista_crear();

	void *resultado_busqueda = lista_obtener_posicion(lista, 0);

	pa2m_afirmar(
		resultado_busqueda == NULL,
		"lista_obtener_posicion() no intenta buscar en una lista vacía");
	lista_destruir(lista);
}

void lista_obtener_posicion_ignora_posicion_invalida()
{
	lista_t *lista = lista_crear();
	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_insertar(lista, &elementos[i]);
	}

	void *resultado_busqueda = lista_obtener_posicion(lista, 5);

	pa2m_afirmar(
		resultado_busqueda == NULL,
		"lista_obtener_posicion() no intenta buscar el elemento en una posición inválida");
	lista_destruir(lista);
}

void lista_obtener_posicion_encuentra_elemento_presente()
{
	lista_t *lista = lista_crear();
	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_insertar(lista, &elementos[i]);
	}

	int *resultado_busqueda = lista_obtener_posicion(lista, 1);

	pa2m_afirmar(
		resultado_busqueda == &elementos[1],
		"lista_obtener_posicion() logra encontrar un elemento en una posición intermedia");
	lista_destruir(lista);
}

void lista_obtener_posicion_encuentra_elemento_presente_y_extrae_datos_correctamente()
{
	lista_t *lista = lista_crear();
	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_insertar(lista, &elementos[i]);
	}

	int *resultado_busqueda = lista_obtener_posicion(lista, 1);

	pa2m_afirmar(
		resultado_busqueda == &elementos[1],
		"lista_obtener_posicion() logra encontrar un elemento en una posición intermedia y extrae sus datos correctamente");
	lista_destruir(lista);
}

void lista_eliminar_no_intenta_eliminar_de_lista_nula()
{
	void *elemento_eliminado = lista_eliminar(NULL);

	pa2m_afirmar(
		elemento_eliminado == NULL,
		"lista_eliminar() no intenta eliminar elementos de una lista nula");
}

void lista_eliminar_no_intenta_eliminar_de_lista_vacia()
{
	lista_t *lista_vacia = lista_crear();
	void *elemento_eliminado = lista_eliminar(lista_vacia);

	pa2m_afirmar(
		elemento_eliminado == NULL,
		"lista_eliminar() no intenta eliminar elementos de una lista vacía");
	lista_destruir(lista_vacia);
}

void lista_eliminar_elimina_elemento_y_extrae_datos_correctamente()
{
	lista_t *lista = lista_crear();

	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_insertar(lista, &elementos[i]);
	}

	int *elemento_eliminado = lista_eliminar(lista);

	pa2m_afirmar(
		elemento_eliminado == &elementos[2],
		"lista_eliminar() elimina un elemento y extrae sus datos correctamente");
	lista_destruir(lista);
}

void lista_eliminar_elimina_elemento_y_lo_remueve_de_la_lista()
{
	lista_t *lista = lista_crear();

	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_insertar(lista, &elementos[i]);
	}

	lista_eliminar(lista);
	int *elemento_final = lista_obtener(lista);

	pa2m_afirmar(
		elemento_final == &elementos[1],
		"lista_eliminar() elimina un elemento y ya no forma parte de la lista");
	lista_destruir(lista);
}

void lista_eliminar_cambia_cantidad_de_elementos_correctamente()
{
	lista_t *lista = lista_crear();
	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_insertar(lista, &elementos[i]);
	}

	lista_eliminar(lista);

	pa2m_afirmar(
		lista_cantidad(lista) == 2,
		"lista_eliminar() cambia la cantidad de elementos correctamente");
	lista_destruir(lista);
}

void lista_eliminar_posicion_no_intenta_eliminar_de_lista_nula()
{
	void *elemento_eliminado = lista_eliminar_posicion(NULL, 0);

	pa2m_afirmar(
		elemento_eliminado == NULL,
		"lista_eliminar_posicion() no intenta eliminar elementos de una lista nula");
}

void lista_eliminar_posicion_no_intenta_eliminar_de_lista_vacia()
{
	lista_t *lista_vacia = lista_crear();
	void *elemento_eliminado = lista_eliminar_posicion(lista_vacia, 0);

	pa2m_afirmar(
		elemento_eliminado == NULL,
		"lista_eliminar_posicion() no intenta eliminar elementos de una lista vacía");
	lista_destruir(lista_vacia);
}

void lista_eliminar_posicion_no_intenta_eliminar_elemento_en_posicion_invalida()
{
	lista_t *lista = lista_crear();

	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_insertar(lista, &elementos[i]);
	}

	void *elemento_eliminado = lista_eliminar_posicion(lista, 5);

	pa2m_afirmar(
		elemento_eliminado == NULL,
		"lista_eliminar_posicion() no intenta eliminar un elemento en una posición inválida");
	lista_destruir(lista);
}

void lista_eliminar_posicion_elimina_elemento_y_extrae_datos_correctamente()
{
	lista_t *lista = lista_crear();

	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_insertar(lista, &elementos[i]);
	}

	int *elemento_eliminado = lista_eliminar_posicion(lista, 1);

	pa2m_afirmar(
		elemento_eliminado == &elementos[1],
		"lista_eliminar_posicion() elimina un elemento y extrae sus datos correctamente");
	lista_destruir(lista);
}

void lista_eliminar_posicion_elimina_elemento_y_mantiene_orden()
{
	lista_t *lista = lista_crear();

	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_insertar(lista, &elementos[i]);
	}

	size_t posicion = 1;
	int *elemento_siguiente = lista_obtener_posicion(lista, posicion + 1);
	lista_eliminar_posicion(lista, posicion);
	int *nuevo_elemento_siguiente = lista_obtener_posicion(lista, posicion);

	pa2m_afirmar(
		elemento_siguiente == nuevo_elemento_siguiente,
		"lista_eliminar_posicion() elimina un elemento y mantiene el orden correcto dentro de la lista");
	lista_destruir(lista);
}

void lista_eliminar_posicion_cambia_cantidad_de_elementos_correctamente()
{
	lista_t *lista = lista_crear();
	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_insertar(lista, &elementos[i]);
	}

	lista_eliminar_posicion(lista, 1);

	pa2m_afirmar(
		lista_cantidad(lista) == 2,
		"lista_eliminar_posicion() cambia la cantidad de elementos correctamente");
	lista_destruir(lista);
}

void lista_buscar_ignora_lista_nula()
{
	int dato = 5;
	size_t posicion = 0;
	bool busqueda_fue_exitosa = lista_buscar(
		NULL, &dato, comparador_enteros_son_iguales, &posicion);

	pa2m_afirmar(!busqueda_fue_exitosa,
		     "lista_buscar() no intenta buscar en una lista nula");
}

void lista_buscar_ignora_lista_vacia()
{
	lista_t *lista = lista_crear();
	int dato = 5;
	size_t posicion = 0;
	bool busqueda_fue_exitosa = lista_buscar(
		lista, &dato, comparador_enteros_son_iguales, &posicion);

	pa2m_afirmar(!busqueda_fue_exitosa,
		     "lista_buscar() no intenta buscar en una lista vacía");
	lista_destruir(lista);
}

void lista_buscar_ignora_comparador_nulo()
{
	lista_t *lista = lista_crear();
	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_insertar(lista, &elementos[i]);
	}

	int dato = 5;
	size_t posicion = 0;
	bool busqueda_fue_exitosa = lista_buscar(lista, &dato, NULL, &posicion);

	pa2m_afirmar(!busqueda_fue_exitosa,
		     "lista_buscar() no intenta utilizar un comparador nulo");
	lista_destruir(lista);
}

void lista_buscar_encuentra_elemento_presente_y_devuelve_true()
{
	lista_t *lista = lista_crear();
	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_insertar(lista, &elementos[i]);
	}

	int dato = 3;
	size_t posicion = 0;
	bool busqueda_fue_exitosa = lista_buscar(
		lista, &dato, comparador_enteros_son_iguales, &posicion);

	pa2m_afirmar(
		busqueda_fue_exitosa,
		"lista_buscar() logra encontrar un elemento y devuelve true");
	lista_destruir(lista);
}

void lista_buscar_encuentra_elemento_presente_y_modifica_variable_posicion()
{
	lista_t *lista = lista_crear();
	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_insertar(lista, &elementos[i]);
	}

	int dato = 3;
	size_t posicion = 0;
	lista_buscar(lista, &dato, comparador_enteros_son_iguales, &posicion);

	pa2m_afirmar(
		posicion == 2,
		"lista_buscar() logra encontrar un elemento y modifica la variable de posición correctamente");
	lista_destruir(lista);
}

void lista_buscar_devuelve_false_buscando_elemento_no_presente()
{
	lista_t *lista = lista_crear();
	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_insertar(lista, &elementos[i]);
	}

	int dato = 5;
	size_t posicion = 0;
	bool busqueda_fue_exitosa = lista_buscar(
		lista, &dato, comparador_enteros_son_iguales, &posicion);

	pa2m_afirmar(
		!busqueda_fue_exitosa,
		"lista_buscar() devuelve false al intentar buscar un elemento no presente");
	lista_destruir(lista);
}

void lista_buscar_no_modifica_variable_posicion_buscando_elemento_no_presente()
{
	lista_t *lista = lista_crear();
	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_insertar(lista, &elementos[i]);
	}

	int dato = 5;
	size_t posicion = 5;
	lista_buscar(lista, &dato, comparador_enteros_son_iguales, &posicion);

	pa2m_afirmar(
		posicion == 5,
		"lista_buscar() no modifica el valor de la variable de posición si no encuentra el elemento");
	lista_destruir(lista);
}

void lista_con_cada_elemento_ignora_lista_nula()
{
	int dato = 5;
	size_t cantidad_elementos_afectados = lista_con_cada_elemento(
		NULL, funcion_generica_comparador_enteros, &dato);

	pa2m_afirmar(
		cantidad_elementos_afectados == 0,
		"lista_con_cada_elemento() no intenta iterar sobre una lista nula");
}

void lista_con_cada_elemento_ignora_funcion_nula_sobre_lista_valida()
{
	lista_t *lista = lista_crear();
	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_insertar(lista, &elementos[i]);
	}

	int dato = 5;
	size_t cantidad_elementos_afectados =
		lista_con_cada_elemento(lista, NULL, &dato);

	pa2m_afirmar(
		cantidad_elementos_afectados == 0,
		"lista_con_cada_elemento() no intenta iterar sobre una lista válida con una función nula");
	lista_destruir(lista);
}

void lista_con_cada_elemento_funciona_sobre_lista_vacia()
{
	lista_t *lista = lista_crear();

	int dato = 50;
	size_t cantidad_elementos_afectados = lista_con_cada_elemento(
		lista, funcion_generica_comparador_enteros, &dato);

	pa2m_afirmar(
		cantidad_elementos_afectados == 0,
		"lista_con_cada_elemento() funciona al usarse sobre una lista vacía");
	lista_destruir(lista);
}

void lista_con_cada_elemento_devuelve_cantidad_correcta_de_elementos_afectados_iteracion_cortada()
{
	lista_t *lista = lista_crear();
	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_insertar(lista, &elementos[i]);
	}

	int dato = 1;
	size_t cantidad_elementos_afectados = lista_con_cada_elemento(
		lista, funcion_generica_comparador_enteros, &dato);

	pa2m_afirmar(
		cantidad_elementos_afectados == 2,
		"lista_con_cada_elemento() corta la iteración y devuelve la cantidad correcta de elementos a los cuales se le aplicó la función");
	lista_destruir(lista);
}

void lista_con_cada_elemento_devuelve_cantidad_correcta_de_elementos_afectados_iteracion_completa()
{
	lista_t *lista = lista_crear();
	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_insertar(lista, &elementos[i]);
	}

	int dato = 3;
	size_t cantidad_elementos_afectados = lista_con_cada_elemento(
		lista, funcion_generica_reemplazar_todos, &dato);

	pa2m_afirmar(
		cantidad_elementos_afectados == 3,
		"lista_con_cada_elemento() completa la iteración y devuelve la cantidad correcta de elementos a los cuales se le aplicó la función");
	lista_destruir(lista);
}

void lista_con_cada_elemento_aplica_la_funcion_sobre_todo_elemento()
{
	lista_t *lista = lista_crear();
	int elementos[] = { 5, 2, 9 };
	for (size_t i = 0; i < 3; i++) {
		lista_insertar(lista, &elementos[i]);
	}

	int dato = 1;
	size_t cantidad_elementos_afectados = lista_con_cada_elemento(
		lista, funcion_generica_reemplazar_todos, &dato);
	int *primer_elemento = lista_obtener_posicion(lista, 0);
	int *segundo_elemento = lista_obtener_posicion(lista, 1);
	int *tercer_elemento = lista_obtener_posicion(lista, 2);

	pa2m_afirmar(
		cantidad_elementos_afectados == 3 && *primer_elemento == dato &&
			*segundo_elemento == dato && *tercer_elemento == dato,
		"lista_con_cada_elemento() aplíca una función genérica sobre todos los elementos correctamente");
	lista_destruir(lista);
}

void lista_iterador_crear_no_crea_un_iterador_para_lista_nula()
{
	lista_iterador_t *iterador_externo = lista_iterador_crear(NULL);

	pa2m_afirmar(
		iterador_externo == NULL,
		"lista_iterador_crear() no intenta crear un iterador para una lista nula");
	lista_iterador_destruir(iterador_externo);
}

void lista_iterador_crear_crea_un_iterador_para_lista_vacia_correctamente()
{
	lista_t *lista = lista_crear();
	lista_iterador_t *iterador_externo = lista_iterador_crear(lista);

	pa2m_afirmar(
		iterador_externo != NULL,
		"lista_iterador_crear() crea un iterador para una lista vacía correctamente");
	lista_iterador_destruir(iterador_externo);
	lista_destruir(lista);
}

void lista_iterador_crear_crea_un_iterador_para_lista_valida_correctamente()
{
	lista_t *lista = lista_crear();
	int dato = 50;
	lista_insertar(lista, &dato);
	lista_iterador_t *iterador_externo = lista_iterador_crear(lista);

	pa2m_afirmar(
		iterador_externo != NULL,
		"lista_iterador_crear() crea un iterador para una lista válida correctamente");
	lista_iterador_destruir(iterador_externo);
	lista_destruir(lista);
}

void lista_iterador_crear_inicializa_el_iterador_en_el_primer_elemento()
{
	lista_t *lista = lista_crear();
	int elementos[] = { 5, 2, 9 };
	for (size_t i = 0; i < 3; i++) {
		lista_insertar(lista, &elementos[i]);
	}

	lista_iterador_t *iterador_externo = lista_iterador_crear(lista);
	int *elemento_actual = lista_iterador_actual(iterador_externo);

	pa2m_afirmar(
		iterador_externo != NULL && elemento_actual == &elementos[0],
		"lista_iterador_crear() crea un iterador y lo inicializa en el primer elemento");
	lista_iterador_destruir(iterador_externo);
	lista_destruir(lista);
}

void lista_iterador_avanzar_avanza_al_siguiente_elemento_correctamente()
{
	lista_t *lista = lista_crear();
	int elementos[] = { 1, 2 };
	for (size_t i = 0; i < 2; i++) {
		lista_insertar(lista, &elementos[i]);
	}

	lista_iterador_t *iterador_externo = lista_iterador_crear(lista);
	lista_iterador_avanzar(iterador_externo);
	int *elemento_actual = lista_iterador_actual(iterador_externo);

	pa2m_afirmar(
		elemento_actual == &elementos[1],
		"lista_iterador_avanzar() avanza al siguiente elemento correctamente");
	lista_iterador_destruir(iterador_externo);
	lista_destruir(lista);
}

void lista_iterador_hay_mas_elementos_toma_iterador_nulo()
{
	pa2m_afirmar(
		lista_iterador_hay_mas_elementos(NULL) == false,
		"lista_iterador_hay_mas_elementos() toma un iterador nulo y lo considera como finalizado");
}

void lista_iterador_hay_mas_elementos_reconoce_lista_sin_finalizar()
{
	lista_t *lista = lista_crear();
	int elementos[] = { 1, 2 };
	for (size_t i = 0; i < 2; i++) {
		lista_insertar(lista, &elementos[i]);
	}

	lista_iterador_t *iterador_externo = lista_iterador_crear(lista);
	bool hay_mas_al_principio =
		lista_iterador_hay_mas_elementos(iterador_externo);

	pa2m_afirmar(
		hay_mas_al_principio,
		"lista_iterador_hay_mas_elementos() reconoce que la lista no ha finalizado");
	lista_iterador_destruir(iterador_externo);
	lista_destruir(lista);
}

void lista_iterador_hay_mas_elementos_reconoce_fin_de_lista()
{
	lista_t *lista = lista_crear();
	int elementos[] = { 1, 2 };
	for (size_t i = 0; i < 2; i++) {
		lista_insertar(lista, &elementos[i]);
	}

	lista_iterador_t *iterador_externo = lista_iterador_crear(lista);
	lista_iterador_avanzar(iterador_externo);
	lista_iterador_avanzar(iterador_externo);
	lista_iterador_avanzar(iterador_externo);
	bool hay_mas_al_final =
		lista_iterador_hay_mas_elementos(iterador_externo);

	pa2m_afirmar(
		!hay_mas_al_final,
		"lista_iterador_hay_mas_elementos() reconoce el final de la lista correctamente");
	lista_iterador_destruir(iterador_externo);
	lista_destruir(lista);
}

void lista_iterador_actual_ignora_lista_nula()
{
	void *elemento_actual = lista_iterador_actual(NULL);

	pa2m_afirmar(
		elemento_actual == NULL,
		"lista_iterador_actual() devuelve NULL si se usa sobre un iterador nulo");
}

void lista_iterador_actual_devuelve_null_si_no_hay_mas_elementos()
{
	lista_t *lista = lista_crear();
	int elementos[] = { 1, 2 };
	for (size_t i = 0; i < 2; i++) {
		lista_insertar(lista, &elementos[i]);
	}

	lista_iterador_t *iterador_externo = lista_iterador_crear(lista);
	lista_iterador_avanzar(iterador_externo);
	lista_iterador_avanzar(iterador_externo);
	lista_iterador_avanzar(iterador_externo);
	void *elemento_actual = lista_iterador_actual(iterador_externo);

	pa2m_afirmar(
		elemento_actual == NULL,
		"lista_iterador_actual() devuelve NULL si no hay más elementos");
	lista_iterador_destruir(iterador_externo);
	lista_destruir(lista);
}

void lista_iterador_actual_extrae_datos_correctamente()
{
	lista_t *lista = lista_crear();
	int elementos[] = { 1, 2 };
	for (size_t i = 0; i < 2; i++) {
		lista_insertar(lista, &elementos[i]);
	}

	lista_iterador_t *iterador_externo = lista_iterador_crear(lista);
	int *elemento_actual = lista_iterador_actual(iterador_externo);

	pa2m_afirmar(
		elemento_actual == &elementos[0],
		"lista_iterador_actual() extrae los datos del elemento actual correctamente");
	lista_iterador_destruir(iterador_externo);
	lista_destruir(lista);
}

void pila_crear_devuelve_pila_valida()
{
	pila_t *pila = pila_crear();

	pa2m_afirmar(pila != NULL, "pila_crear() devuelve una pila válida");
	pila_destruir(pila);
}

void pila_crear_devuelve_pila_vacia()
{
	pila_t *pila = pila_crear();

	pa2m_afirmar(pila_cantidad(pila) == 0,
		     "pila_crear() devuelve una pila vacía");
	pila_destruir(pila);
}

void pila_cantidad_toma_pila_nula_como_vacia()
{
	pa2m_afirmar(
		pila_cantidad(NULL) == 0,
		"pila_cantidad() recibe una pila nula y la asume como vacía");
}

void pila_cantidad_devuelve_0_con_pila_vacia()
{
	pila_t *pila = pila_crear();

	pa2m_afirmar(pila_cantidad(pila) == 0,
		     "pila_cantidad() recibe una pila vacía y devuelve 0");
	pila_destruir(pila);
}

void pila_cantidad_devuelve_valor_correcto()
{
	pila_t *pila = pila_crear();
	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		pila_apilar(pila, &elementos[i]);
	}

	pa2m_afirmar(
		pila_cantidad(pila) == 3,
		"pila_cantidad() devuelve el valor correspondiente de elementos presentes");
	pila_destruir(pila);
}

void pila_tope_sobre_pila_nula_devuelve_null()
{
	void *elemento_tope = pila_tope(NULL);
	pa2m_afirmar(
		elemento_tope == NULL,
		"pila_tope() devuelve puntero nulo al usarse sobre una pila nula");
}

void pila_tope_sobre_pila_vacia_devuelve_null()
{
	pila_t *pila = pila_crear();
	void *elemento_tope = pila_tope(pila);

	pa2m_afirmar(
		elemento_tope == NULL,
		"pila_tope() devuelve puntero nulo al usarse sobre una pila vacía");
	pila_destruir(pila);
}

void pila_tope_encuentra_elemento_del_tope()
{
	pila_t *pila = pila_crear();

	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		pila_apilar(pila, &elementos[i]);
	}

	int *elemento_tope = pila_tope(pila);
	pa2m_afirmar(elemento_tope != NULL,
		     "pila_tope() logra encontrar el elemento del tope");
	pila_destruir(pila);
}

void pila_tope_extrae_datos_correctamente()
{
	pila_t *pila = pila_crear();

	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		pila_apilar(pila, &elementos[i]);
	}

	int *elemento_tope = pila_tope(pila);
	pa2m_afirmar(
		elemento_tope == &elementos[2],
		"pila_tope() logra encontrar el elemento del tope y extrae sus datos correctamente");
	pila_destruir(pila);
}

void pila_apilar_no_agrega_elementos_a_pila_nula()
{
	int dato = 50;
	pila_t *resultado_apilar = pila_apilar(NULL, &dato);

	pa2m_afirmar(
		resultado_apilar == NULL,
		"pila_apilar() no intenta agregar elementos a una pila nula");
}

void pila_apilar_devuelve_puntero_al_insertar_correctamente()
{
	pila_t *pila = pila_crear();
	int dato = 50;
	pila_t *resultado_apilar = pila_apilar(pila, &dato);

	pa2m_afirmar(
		resultado_apilar == pila,
		"pila_apilar() devuelve un puntero a la misma pila cuando se inserta con éxito");
	pila_destruir(pila);
}

void pila_apilar_agrega_elemento_a_pila_vacia()
{
	pila_t *pila = pila_crear();
	int dato = 50;
	pila_apilar(pila, &dato);
	int *elemento_tope = pila_tope(pila);

	pa2m_afirmar(
		elemento_tope == &dato,
		"pila_apilar() agrega un elemento a una pila vacía correctamente");
	pila_destruir(pila);
}

void pila_apilar_agrega_elemento_a_pila_no_vacia()
{
	pila_t *pila = pila_crear();
	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		pila_apilar(pila, &elementos[i]);
	}
	int *elemento_tope = pila_tope(pila);

	pa2m_afirmar(
		elemento_tope == &elementos[2],
		"pila_apilar() agrega un elemento a una pila no vacía correctamente");
	pila_destruir(pila);
}

void pila_apilar_cambia_cantidad_de_elementos_correctamente()
{
	pila_t *pila = pila_crear();
	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		pila_apilar(pila, &elementos[i]);
	}

	pa2m_afirmar(
		pila_cantidad(pila) == 3,
		"pila_apilar() cambia la cantidad de elementos correctamente");
	pila_destruir(pila);
}

void pila_apilar_siempre_agrega_al_tope_de_la_pila()
{
	pila_t *pila = pila_crear();
	int elementos[] = { 1, 2, 3, 88, 2, 11, 5, 92 };
	bool verificaciones[] = { false, false, false, false,
				  false, false, false, false };
	for (size_t i = 0; i < 8; i++) {
		pila_apilar(pila, &elementos[i]);
	}
	for (size_t i = 0; i < 8; i++) {
		int *desapilado = pila_desapilar(pila);
		if (desapilado == &elementos[7 - i])
			verificaciones[i] = true;
	}

	pa2m_afirmar(
		comprobar_array_verificaciones(verificaciones, 8),
		"pila_apilar() siempre agrega elementos al tope de la pila");
	pila_destruir(pila);
}

void pila_desapilar_no_intenta_eliminar_de_pila_nula()
{
	void *elemento_desapilado = pila_desapilar(NULL);
	pa2m_afirmar(
		elemento_desapilado == NULL,
		"pila_desapilar() no intenta eliminar elementos de una pila nula");
}

void pila_desapilar_no_intenta_eliminar_de_pila_vacia()
{
	pila_t *pila = pila_crear();
	void *elemento_desapilado = pila_desapilar(pila);

	pa2m_afirmar(
		elemento_desapilado == NULL,
		"pila_desapilar() no intenta eliminar elementos de una pila vacía");
	pila_destruir(pila);
}

void pila_desapilar_elimina_elemento_y_extrae_datos_correctamente()
{
	pila_t *pila = pila_crear();

	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		pila_apilar(pila, &elementos[i]);
	}

	int *elemento_eliminado = pila_desapilar(pila);

	pa2m_afirmar(
		elemento_eliminado == &elementos[2],
		"pila_desapilar() elimina un elemento del tope y extrae sus datos correctamente");
	pila_destruir(pila);
}

void pila_desapilar_elimina_elemento_y_lo_remueve_de_la_pila()
{
	pila_t *pila = pila_crear();

	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		pila_apilar(pila, &elementos[i]);
	}

	pila_desapilar(pila);
	int *elemento_tope = pila_tope(pila);

	pa2m_afirmar(
		elemento_tope == &elementos[1],
		"pila_desapilar() elimina un elemento del tope y ya no forma parte de la pila");
	pila_destruir(pila);
}

void pila_desapilar_cambia_cantidad_de_elementos_correctamente()
{
	pila_t *pila = pila_crear();

	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		pila_apilar(pila, &elementos[i]);
	}

	pila_desapilar(pila);

	pa2m_afirmar(
		pila_cantidad(pila) == 2,
		"pila_desapilar() cambia la cantidad de elementos correctamente");
	pila_destruir(pila);
}

void cola_crear_devuelve_cola_valida()
{
	cola_t *cola = cola_crear();

	pa2m_afirmar(cola != NULL, "cola_crear() devuelve una cola válida");
	cola_destruir(cola);
}

void cola_crear_devuelve_cola_vacia()
{
	cola_t *cola = cola_crear();

	pa2m_afirmar(cola_cantidad(cola) == 0,
		     "cola_crear() devuelve una cola vacía");
	cola_destruir(cola);
}

void cola_cantidad_toma_cola_nula_como_vacia()
{
	pa2m_afirmar(
		cola_cantidad(NULL) == 0,
		"cola_cantidad() recibe una cola nula y la asume como vacía");
}

void cola_cantidad_devuelve_0_con_cola_vacia()
{
	cola_t *cola = cola_crear();

	pa2m_afirmar(cola_cantidad(cola) == 0,
		     "cola_cantidad() recibe una cola vacía y devuelve 0");
	cola_destruir(cola);
}

void cola_cantidad_devuelve_valor_correcto()
{
	cola_t *cola = cola_crear();
	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		cola_encolar(cola, &elementos[i]);
	}

	pa2m_afirmar(
		cola_cantidad(cola) == 3,
		"cola_cantidad() devuelve el valor correspondiente de elementos presentes");
	cola_destruir(cola);
}

void cola_frente_sobre_cola_nula_devuelve_null()
{
	void *elemento_frente = cola_frente(NULL);
	pa2m_afirmar(
		elemento_frente == NULL,
		"cola_frente() devuelve puntero nulo al usarse sobre una cola nula");
}

void cola_frente_sobre_cola_vacia_devuelve_null()
{
	cola_t *cola = cola_crear();
	void *elemento_frente = cola_frente(cola);

	pa2m_afirmar(
		elemento_frente == NULL,
		"cola_frente() devuelve puntero nulo al usarse sobre una cola vacía");
	cola_destruir(cola);
}

void cola_frente_encuentra_elemento_del_frente()
{
	cola_t *cola = cola_crear();

	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		cola_encolar(cola, &elementos[i]);
	}

	int *elemento_frente = cola_frente(cola);
	pa2m_afirmar(elemento_frente != NULL,
		     "cola_frente() logra encontrar el elemento del frente");
	cola_destruir(cola);
}

void cola_frente_extrae_datos_correctamente()
{
	cola_t *cola = cola_crear();

	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		cola_encolar(cola, &elementos[i]);
	}

	int *elemento_frente = cola_frente(cola);
	pa2m_afirmar(
		elemento_frente == &elementos[0],
		"cola_frente() logra encontrar el elemento del frente y extrae sus datos correctamente");
	cola_destruir(cola);
}

void cola_encolar_no_agrega_elementos_a_cola_nula()
{
	int dato = 50;
	cola_t *resultado_encolar = cola_encolar(NULL, &dato);

	pa2m_afirmar(
		resultado_encolar == NULL,
		"cola_encolar() no intenta agregar elementos a una cola nula");
}

void cola_encolar_devuelve_puntero_al_insertar_correctamente()
{
	cola_t *cola = cola_crear();
	int dato = 50;
	cola_t *resultado_encolar = cola_encolar(cola, &dato);

	pa2m_afirmar(
		resultado_encolar == cola,
		"cola_encolar() devuelve un puntero a la misma cola cuando se inserta con éxito");
	cola_destruir(cola);
}

void cola_encolar_agrega_elemento_a_cola_vacia()
{
	cola_t *cola = cola_crear();
	int dato = 50;
	cola_t *resultado_encolar = cola_encolar(cola, &dato);

	pa2m_afirmar(
		resultado_encolar == cola,
		"cola_encolar() agrega un elemento a una cola vacía correctamente");
	cola_destruir(cola);
}

void cola_encolar_agrega_elemento_a_cola_no_vacia()
{
	cola_t *cola = cola_crear();
	int elementos[] = { 1, 2, 3 };
	cola_t *resultado_encolar;
	for (size_t i = 0; i < 3; i++) {
		resultado_encolar = cola_encolar(cola, &elementos[i]);
	}

	pa2m_afirmar(
		resultado_encolar == cola,
		"cola_encolar() agrega un elemento a una cola no vacía correctamente");
	cola_destruir(cola);
}

void cola_encolar_cambia_cantidad_de_elementos_correctamente()
{
	cola_t *cola = cola_crear();
	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		cola_encolar(cola, &elementos[i]);
	}

	pa2m_afirmar(
		cola_cantidad(cola) == 3,
		"cola_encolar() cambia la cantidad de elementos correctamente");
	cola_destruir(cola);
}

void cola_encolar_siempre_agrega_al_final_de_la_cola()
{
	cola_t *cola = cola_crear();
	int elementos[] = { 1, 2, 3, 88, 2, 11, 5, 92 };
	bool verificaciones[] = { false, false, false, false,
				  false, false, false, false };
	for (size_t i = 0; i < 8; i++) {
		cola_encolar(cola, &elementos[i]);
	}
	for (size_t i = 0; i < 8; i++) {
		int *desencolado = cola_desencolar(cola);
		if (desencolado == &elementos[i])
			verificaciones[i] = true;
	}

	pa2m_afirmar(
		comprobar_array_verificaciones(verificaciones, 8),
		"cola_encolar() siempre agrega elementos al final de la cola");
	cola_destruir(cola);
}

void cola_desencolar_no_intenta_eliminar_de_cola_nula()
{
	void *elemento_desencolado = cola_desencolar(NULL);
	pa2m_afirmar(
		elemento_desencolado == NULL,
		"cola_desencolar() no intenta eliminar elementos de una cola nula");
}

void cola_desencolar_no_intenta_eliminar_de_cola_vacia()
{
	cola_t *cola = cola_crear();
	void *elemento_desencolado = cola_desencolar(cola);

	pa2m_afirmar(
		elemento_desencolado == NULL,
		"cola_desencolar() no intenta eliminar elementos de una cola vacía");
	cola_destruir(cola);
}

void cola_desencolar_elimina_elemento_y_extrae_datos_correctamente()
{
	cola_t *cola = cola_crear();

	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		cola_encolar(cola, &elementos[i]);
	}

	int *elemento_eliminado = cola_desencolar(cola);

	pa2m_afirmar(
		*elemento_eliminado == elementos[0],
		"cola_desencolar() elimina un elemento del frente y extrae sus datos correctamente");
	cola_destruir(cola);
}

void cola_desencolar_elimina_elemento_y_lo_remueve_de_la_cola()
{
	cola_t *cola = cola_crear();

	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		cola_encolar(cola, &elementos[i]);
	}

	cola_desencolar(cola);
	int *elemento_frente = cola_frente(cola);

	pa2m_afirmar(
		elemento_frente == &elementos[1],
		"cola_desencolar() elimina un elemento del frente y ya no forma parte de la cola");
	cola_destruir(cola);
}

void cola_desencolar_cambia_cantidad_de_elementos_correctamente()
{
	cola_t *cola = cola_crear();

	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		cola_encolar(cola, &elementos[i]);
	}

	cola_desencolar(cola);

	pa2m_afirmar(
		cola_cantidad(cola) == 2,
		"cola_desencolar() cambia la cantidad de elementos correctamente");
	cola_destruir(cola);
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de funcionalidades básicas de lista");
	lista_crear_devuelve_lista_valida();
	lista_crear_devuelve_lista_vacia();
	lista_vacia_toma_lista_nula_como_vacia();
	lista_vacia_reconoce_lista_vacia();
	lista_vacia_reconoce_lista_no_vacia();
	lista_cantidad_toma_lista_nula_como_vacia();
	lista_cantidad_devuelve_0_con_lista_vacia();
	lista_cantidad_devuelve_valor_correcto();

	pa2m_nuevo_grupo("Pruebas de inserción");
	lista_insertar_no_agrega_elementos_a_lista_nula();
	lista_insertar_devuelve_puntero_al_insertar_correctamente();
	lista_insertar_agrega_elemento_a_lista_vacia();
	lista_insertar_agrega_elemento_a_lista_no_vacia();
	lista_insertar_agrega_elemento_nulo_correctamente();
	lista_insertar_cambia_cantidad_de_elementos_correctamente();
	lista_insertar_posicion_no_agrega_elementos_a_lista_nula();
	lista_insertar_posicion_devuelve_puntero_al_insertar_correctamente();
	lista_insertar_posicion_agrega_elemento_a_lista_vacia();
	lista_insertar_posicion_agrega_elemento_nulo_correctamente();
	lista_insertar_posicion_agrega_elemento_al_principio_correctamente();
	lista_insertar_posicion_agrega_elemento_en_el_medio_correctamente();
	lista_insertar_posicion_agrega_elemento_al_final_correctamente();
	lista_insertar_posicion_agrega_elementos_en_una_posicion_invalida();
	lista_insertar_posicion_cambia_cantidad_de_elementos_correctamente();

	pa2m_nuevo_grupo("Pruebas de obtención");
	lista_obtener_ignora_lista_nula();
	lista_obtener_ignora_lista_vacia();
	lista_obtener_encuentra_elemento_presente();
	lista_obtener_encuentra_elemento_presente_y_extrae_datos_correctamente();
	lista_obtener_posicion_ignora_lista_nula();
	lista_obtener_posicion_ignora_lista_vacia();
	lista_obtener_posicion_ignora_posicion_invalida();
	lista_obtener_posicion_encuentra_elemento_presente();
	lista_obtener_posicion_encuentra_elemento_presente_y_extrae_datos_correctamente();

	pa2m_nuevo_grupo("Pruebas de eliminación");
	lista_eliminar_no_intenta_eliminar_de_lista_nula();
	lista_eliminar_no_intenta_eliminar_de_lista_vacia();
	lista_eliminar_elimina_elemento_y_extrae_datos_correctamente();
	lista_eliminar_elimina_elemento_y_lo_remueve_de_la_lista();
	lista_eliminar_cambia_cantidad_de_elementos_correctamente();
	lista_eliminar_posicion_no_intenta_eliminar_de_lista_nula();
	lista_eliminar_posicion_no_intenta_eliminar_de_lista_vacia();
	lista_eliminar_posicion_no_intenta_eliminar_elemento_en_posicion_invalida();
	lista_eliminar_posicion_elimina_elemento_y_extrae_datos_correctamente();
	lista_eliminar_posicion_elimina_elemento_y_mantiene_orden();
	lista_eliminar_posicion_cambia_cantidad_de_elementos_correctamente();

	pa2m_nuevo_grupo("Pruebas de búsqueda");
	lista_buscar_ignora_lista_nula();
	lista_buscar_ignora_lista_vacia();
	lista_buscar_ignora_comparador_nulo();
	lista_buscar_encuentra_elemento_presente_y_devuelve_true();
	lista_buscar_encuentra_elemento_presente_y_modifica_variable_posicion();
	lista_buscar_devuelve_false_buscando_elemento_no_presente();
	lista_buscar_no_modifica_variable_posicion_buscando_elemento_no_presente();

	pa2m_nuevo_grupo("Pruebas de iteración interna");
	lista_con_cada_elemento_ignora_lista_nula();
	lista_con_cada_elemento_ignora_funcion_nula_sobre_lista_valida();
	lista_con_cada_elemento_funciona_sobre_lista_vacia();
	lista_con_cada_elemento_devuelve_cantidad_correcta_de_elementos_afectados_iteracion_cortada();
	lista_con_cada_elemento_devuelve_cantidad_correcta_de_elementos_afectados_iteracion_completa();
	lista_con_cada_elemento_aplica_la_funcion_sobre_todo_elemento();

	pa2m_nuevo_grupo("Pruebas de iteración externa");
	lista_iterador_crear_no_crea_un_iterador_para_lista_nula();
	lista_iterador_crear_crea_un_iterador_para_lista_vacia_correctamente();
	lista_iterador_crear_crea_un_iterador_para_lista_valida_correctamente();
	lista_iterador_crear_inicializa_el_iterador_en_el_primer_elemento();
	lista_iterador_avanzar_avanza_al_siguiente_elemento_correctamente();
	lista_iterador_hay_mas_elementos_toma_iterador_nulo();
	lista_iterador_hay_mas_elementos_reconoce_lista_sin_finalizar();
	lista_iterador_hay_mas_elementos_reconoce_fin_de_lista();
	lista_iterador_actual_ignora_lista_nula();
	lista_iterador_actual_devuelve_null_si_no_hay_mas_elementos();
	lista_iterador_actual_extrae_datos_correctamente();

	pa2m_nuevo_grupo("Pruebas de pila");
	pila_crear_devuelve_pila_valida();
	pila_crear_devuelve_pila_vacia();
	pila_cantidad_toma_pila_nula_como_vacia();
	pila_cantidad_devuelve_0_con_pila_vacia();
	pila_cantidad_devuelve_valor_correcto();
	pila_tope_sobre_pila_nula_devuelve_null();
	pila_tope_sobre_pila_vacia_devuelve_null();
	pila_tope_encuentra_elemento_del_tope();
	pila_tope_extrae_datos_correctamente();
	pila_apilar_no_agrega_elementos_a_pila_nula();
	pila_apilar_devuelve_puntero_al_insertar_correctamente();
	pila_apilar_agrega_elemento_a_pila_vacia();
	pila_apilar_agrega_elemento_a_pila_no_vacia();
	pila_apilar_cambia_cantidad_de_elementos_correctamente();
	pila_apilar_siempre_agrega_al_tope_de_la_pila();
	pila_desapilar_no_intenta_eliminar_de_pila_nula();
	pila_desapilar_no_intenta_eliminar_de_pila_vacia();
	pila_desapilar_elimina_elemento_y_extrae_datos_correctamente();
	pila_desapilar_elimina_elemento_y_lo_remueve_de_la_pila();
	pila_desapilar_cambia_cantidad_de_elementos_correctamente();

	pa2m_nuevo_grupo("Pruebas de cola");
	cola_crear_devuelve_cola_valida();
	cola_crear_devuelve_cola_vacia();
	cola_cantidad_toma_cola_nula_como_vacia();
	cola_cantidad_devuelve_0_con_cola_vacia();
	cola_cantidad_devuelve_valor_correcto();
	cola_frente_sobre_cola_nula_devuelve_null();
	cola_frente_sobre_cola_vacia_devuelve_null();
	cola_frente_encuentra_elemento_del_frente();
	cola_frente_extrae_datos_correctamente();
	cola_encolar_no_agrega_elementos_a_cola_nula();
	cola_encolar_devuelve_puntero_al_insertar_correctamente();
	cola_encolar_agrega_elemento_a_cola_vacia();
	cola_encolar_agrega_elemento_a_cola_no_vacia();
	cola_encolar_cambia_cantidad_de_elementos_correctamente();
	cola_desencolar_no_intenta_eliminar_de_cola_nula();
	cola_desencolar_no_intenta_eliminar_de_cola_vacia();
	cola_desencolar_elimina_elemento_y_extrae_datos_correctamente();
	cola_desencolar_elimina_elemento_y_lo_remueve_de_la_cola();
	cola_desencolar_cambia_cantidad_de_elementos_correctamente();

	return pa2m_mostrar_reporte();
}
