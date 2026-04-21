#define SIN_ERRORES 0
#define ERROR_ENTRADA_INVALIDA 1
#define ERROR_CALCULO_INVALIDO 2

#define AVISO_RESULTADO "\nResultado: \033[38;5;216;1m%f\033[0m.\n\n"
#define AVISO_ERROR_ENTRADA \
	"\n\033[38;5;202;1mERROR\033[0m: La entrada es inválida. Recuerde que la operación a calcular debe estar en notación polaca inversa para que el programa la reconozca. Solo se aceptan los operadores '+', '-', '*' y '/'.\n\n"
#define AVISO_ERROR_CALCULO \
	"\033[38;5;214;1mAVISO\033[0m: Este error ocurrió durante el cálculo. Aseguresé de que el orden de la operación sea correcto.\n\n"

#define CANTIDAD_OPERADORES 4