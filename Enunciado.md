# TDA Lista/Pila/Cola

Se pide implementar una lista simplemente enlazada, una pila y una cola según las interfaces definidas en clase.

Los TDAs entregados deberan compilar y pasar las pruebas dispuestas por la cátedra sin errores, adicionalmente estas pruebas deberán ser ejecutadas **sin pérdida de memoria**.

Recordar que es obligatorio entregar un informe que explique cómo se implementaron los TDAs, cómo funcionan, la complejidad de las operaciones y cualquier aclaración que sea necesaria para el corrector.

Recordar también que es obligatorio entregar **pruebas_alumno.c** con las pruebas realizadas para verificar 
el correcto funcionamiento de los TDA.

## main.c

En el archivo main.c se debe implementar un programa que por línea de comandos reciba una serie de operadores y operandos en notación polaca inversa e imprima por pantalla el resultado correcto o **ERROR** en caso de error.

Por ejemplo
```txt
./main 1 3 +
4
```

```txt
./main 5 4 8 2 * + 10 - +
15
```

```txt
./main 1 +
ERROR
```

## Restricciones

  Para que el trabajo se considere aprobado, la implementación debe cumplir los siguientes requisitos:

  - Las lista debe ser simplemente enlazada
  - Las operaciones **apilar**, **desapilar** y **tope** deben ser **O(1)**
  - Las operaciones **encolar**, **desencolar** y **frente** deben ser **O(1)**
  - Las implementaciones de pila y cola deben reutilizar la implementación de lista

## Parte teórica

Explicar teóricamente los siguientes puntos (no necesariamente en orden, pero por favor usando diagramas):

   - Explicar qué es una lista, lista enlazada y lista doblemente enlazada.
     - Explicar las características de cada una.
     - Explicar las diferencias internas de implementación.
     - Explicar ventajas y desventajas de cada una, si existen.
   - Explicar qué es una lista circular y de qué maneras se puede implementar.
   - Explicar la diferencia de funcionamiento entre cola y pila.
   - Explicar la diferencia entre un iterador interno y uno externo.
