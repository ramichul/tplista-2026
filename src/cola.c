#include "lista.h"
#include "cola.h"

struct cola {
	lista_t *lista;
};

cola_t *cola_crear()
{
	cola_t *nueva_cola = calloc(1, sizeof(cola_t));
	if (nueva_cola == NULL)
		return NULL;

	nueva_cola->lista = lista_crear();
	if (nueva_cola->lista == NULL) {
		free(nueva_cola);
		return NULL;
	}

	return nueva_cola;
}

cola_t *cola_encolar(cola_t *cola, void *elemento)
{
	if (cola == NULL)
		return NULL;

	if (lista_insertar(cola->lista, elemento) == cola->lista)
		return cola;
	return NULL;
}

void *cola_desencolar(cola_t *cola)
{
	if (cola == NULL)
		return NULL;

	return lista_eliminar_posicion(cola->lista, 0);
}

void *cola_frente(cola_t *cola)
{
	if (cola == NULL)
		return NULL;
	if (cola_cantidad(cola) == 0)
		return NULL;

	return lista_obtener_posicion(cola->lista, 0);
}

size_t cola_cantidad(cola_t *cola)
{
	if (cola == NULL)
		return 0;

	return lista_cantidad(cola->lista);
}

void cola_destruir(cola_t *cola)
{
	cola_destruir_todo(cola, NULL);
}

void cola_destruir_todo(cola_t *cola, void (*destructor)(void *))
{
	lista_destruir_todo(cola->lista, destructor);
	free(cola);
}
