#include <stdio.h>
#include <string.h>
#include "src/lista.h"
#include "src/pila.h"
#include "src/constantes.h"

double efectuar_operacion_suma(double numero_1, double numero_2)
{
	return numero_1 + numero_2;
}

double efectuar_operacion_resta(double numero_1, double numero_2)
{
	return numero_1 - numero_2;
}

double efectuar_operacion_multiplicacion(double numero_1, double numero_2)
{
	return numero_1 * numero_2;
}

double efectuar_operacion_division(double numero_1, double numero_2)
{
	return numero_1 / numero_2;
}

bool argumento_representa_operando(char *argumento)
{
	return atof(argumento) != 0 || strcmp(argumento, "0") == 0;
}

int identificar_indice_operador(char operador)
{
	char OPERADORES_VALIDOS[CANTIDAD_OPERADORES] = { '+', '-', '*', '/' };

	int indice_operador = -1;

	int i = 0;
	bool operador_identificado = false;
	while (i < CANTIDAD_OPERADORES && !operador_identificado) {
		if (operador == OPERADORES_VALIDOS[i]) {
			indice_operador = i;
			operador_identificado = true;
		}
		i++;
	}

	return indice_operador;
}

int parsear_argumentos(int argc, char **argv, bool *argumento_es_operando)
{
	int i = 1;
	bool flag_argumento_invalido = false;
	int cantidad_operandos = 0;
	int cantidad_operadores = 0;

	while (i < argc && !flag_argumento_invalido) {
		if (argumento_representa_operando(argv[i])) {
			argumento_es_operando[i - 1] = true;
			cantidad_operandos++;
		} else if (identificar_indice_operador(argv[i][0]) != -1) {
			cantidad_operadores++;
		} else {
			flag_argumento_invalido = true;
		}
		i++;
	}
	if (cantidad_operandos != cantidad_operadores + 1)
		flag_argumento_invalido = true;

	if (flag_argumento_invalido)
		return ERROR_ENTRADA_INVALIDA;
	return SIN_ERRORES;
}

double calcular_resultado(int argc, char **argv, pila_t *pila,
			  bool *argumento_es_operando, bool *flag_error_calculo)
{
	double (*operaciones[CANTIDAD_OPERADORES])(double, double) = {
		efectuar_operacion_suma, efectuar_operacion_resta,
		efectuar_operacion_multiplicacion, efectuar_operacion_division
	};

	int i = 1;
	while (i < argc && !(*flag_error_calculo)) {
		if (argumento_es_operando[i - 1]) {
			double *operando = calloc(1, sizeof(double));
			*operando = atof(argv[i]);
			pila_apilar(pila, operando);
		} else {
			double *numero_1 = pila_desapilar(pila);
			double *numero_2 = pila_desapilar(pila);

			if (numero_1 == NULL || numero_2 == NULL) {
				*flag_error_calculo = true;
			} else {
				int indice_operador =
					identificar_indice_operador(argv[i][0]);
				double *resultado_operacion =
					calloc(1, sizeof(double));
				*resultado_operacion =
					operaciones[indice_operador](*numero_2,
								     *numero_1);
				pila_apilar(pila, resultado_operacion);
			}

			free(numero_1);
			free(numero_2);
		}
		i++;
	}

	if (!(*flag_error_calculo)) {
		double *resultado_final = pila_desapilar(pila);
		double copia_aux_resultado_final = *resultado_final;
		free(resultado_final);
		return copia_aux_resultado_final;
	}
	return ERROR_CALCULO_INVALIDO;
}

int main(int argc, char **argv)
{
	bool *argumento_es_operando =
		calloc(1, ((long unsigned int)argc - 1) * sizeof(bool));

	if (parsear_argumentos(argc, argv, argumento_es_operando) ==
	    ERROR_ENTRADA_INVALIDA) {
		free(argumento_es_operando);
		printf(AVISO_ERROR_ENTRADA);
		return 0;
	}

	pila_t *pila = pila_crear();
	bool flag_error_calculo = false;
	double resultado = calcular_resultado(
		argc, argv, pila, argumento_es_operando, &flag_error_calculo);
	if (flag_error_calculo) {
		free(argumento_es_operando);
		pila_destruir_todo(pila, free);
		printf(AVISO_ERROR_ENTRADA);
		printf(AVISO_ERROR_CALCULO);
		return 0;
	}

	free(argumento_es_operando);
	pila_destruir_todo(pila, free);
	printf(AVISO_RESULTADO, resultado);
	return 0;
}