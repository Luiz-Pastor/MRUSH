# MRUSH

## Introducción

El **ejecutable** obtenido de la compilación se encarga de encontrar tal número que, aplicando una función determinada, se obtenga otro número pasado como parámetro.

El **objetivo** del proyecto es aprender sobre la manipulación de hilos y la creación y comunicación de procesos


## Ejecución
Para poder ejecutar el programa, primero hemos de compilar el proyecto. Para ello, aplicaremos el comando `make`:
```bash
~ make
```

Una vez hecho, se habrá creado el ejecutable `mrush`. Este programa recibe 3 parámetros
```bash
~ ./mrush <TARGET_INI> <ROUNDS> <N_THREADS>
```
, donde:
- **TARGET_INI**: es el target inicial.
- **ROUNDS**: es el número de veces que se va a buscar un número, encadenando el resultado de las iteraciones. No puede ser negativo. En caso de ser 0, no se buscara el ningún número.
- **N_THREADS**: es el número de hilos que se va a usar a la hora de buscar un resultado. No puede ser negativo ni cero.

## Tests
El propio makefile tiene incorporado una regla para ejecutar las dos pruebas que aparecen en el enunciado del proyecto:
```bash
~ make test
```

Además, es posible ejecutar estos mismos tests usando la herramienta `valgrind`. En ella, se han incorporado tres flags:
- `--leak-check=full`: se encarga de comprobar si los procesos poseen leaks o memoria no liberada al finalizar la ejecución.
- `--track-fds=yes`: una vez terminado el proceso, informa sobre los **file descriptors** que se hayan quedado abiertos. En caso de haber mas de 3 (los fds predeterminados son **0**, **1** y **2** (entrada estandar, salida estandar y salida de errores estandar) y no hace falta que sean cerrados), significará que algun archivo o pipe se ha quedado abierto.
- `-s`: al terminar el proceso, informa con un resumen sobre los errores que se haya podido producir durante la ejecución.

Para ejecutarlo, podemos usar otra regla incorporada en el makefile:
```bash
~ make valgrind
```