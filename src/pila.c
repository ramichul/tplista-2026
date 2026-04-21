#include "lista.h"
#include "pila.h"

struct pila {
	lista_t *lista;
};

pila_t *pila_crear()
{
	pila_t *nueva_pila = calloc(1, sizeof(pila_t));
	if (nueva_pila == NULL)
		return NULL;

	nueva_pila->lista = lista_crear();
	if (nueva_pila->lista == NULL) {
		free(nueva_pila);
		return NULL;
	}

	return nueva_pila;
}

pila_t *pila_apilar(pila_t *pila, void *elemento)
{
	if (pila == NULL)
		return NULL;

	if (lista_insertar_posicion(pila->lista, 0, elemento) == pila->lista)
		return pila;
	return NULL;
}

void *pila_desapilar(pila_t *pila)
{
	if (pila == NULL)
		return NULL;

	return lista_eliminar_posicion(pila->lista, 0);
}

void *pila_tope(pila_t *pila)
{
	if (pila == NULL)
		return NULL;

	return lista_obtener_posicion(pila->lista, 0);
}

size_t pila_cantidad(pila_t *pila)
{
	if (pila == NULL)
		return 0;

	return lista_cantidad(pila->lista);
}

void pila_destruir(pila_t *pila)
{
	pila_destruir_todo(pila, NULL);
}

void pila_destruir_todo(pila_t *pila, void (*destructor)(void *))
{
	lista_destruir_todo(pila->lista, destructor);
	free(pila);
}
