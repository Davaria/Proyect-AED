# Proyecto "EL VIAJERO"

Consulte la documentacion detallada -> [Documentacion Oficial](https://www.notion.so/Proyecto-EL-VIAJERO-05de199d0d3442fdad76d47358df7339)

El reto es conseguir un ciclo cuyo coste sea menor que 22000.

## Contribuidores

1.  Luis Angel Bustamante Torres
1.  Luis Alberto Ccalluchi Lopez

## Antes de empezar

Para inicializar el proyecto debemos tener herramientas nesesarias.

- Compilador `g++` (G++ es un compilador de línea de órdenes que compila y enlaza programas en C++)
- Editor de codigo
  - VSCode
  - Vim

1. Compilar el codigo

   ```cpp
   g++ grafo.cpp
   ```

2. Ejecutar el programa

   ```cpp
   ./a.out
   ```

3. Verificar si nuestro codigo es correcto con el archivo `comprobar.c` y generar el script `.out`

   ```cpp
   g++ comprobar.c
   ```

4. Finalmente, ejecutar el programa

   ```cpp
   ./a.out
   ```

**Resultado esperado:**

```bash
Coste: 25186 Nodos: 1373 Nodo1: 712
El ciclo encontrado es correcto.
```

## Propuesta

La resolución se basa en el uso de algoritmos de Floyd-Warshall y Prim.

## Implementacion

1. Creacion de la clase Grafo

   - `Grafo(int vertex)` → Constructor de clase que recibira como parametro el numero total de vertice, el cual creara las matrices de rutas y matriz.

   - `void add_arista(int i, j ,weight)` → Funcion vacia que creara las relaciones de nuestros grafo, una matriz de adyacencia.

   - `void Grafo::floyd_warshall()` → Funcion vacia que hallara el grafo completo con todas las rutas*.*
   - `int min_ciclo(int nodo_inicio, int nodo_siguiente, bool status)` → Funcion entera que se basa en el algoritmo de prim y recibira como
     1. Primer parametro nuestro nodo de inicio `712`
     2. Segundo parametro cualquier nodo de nuestros grafos de nodos
     3. Tercer parametro un booleano, el cual añadira a un lista enlazada donde se almacenara nuestro camino de nodos con la ruta mas optima.
   - `int get_ruta(int a, int b)` → Funcion entera que lo que hace es buscar la ruta desde un nodo a otro por medio de sus antecesores, retorna el numero de nodos que visita.
   - `void salida()` → Funcion vacia la cual almacenamos nuestros coste del ciclo, numero de vertices y nuetro ciclo en un archivo de salida `output.txt`.

2. Constructor de clase → `Grafo(int vertex)`

Las variables miembro `matriz` y `ruta` se les reservara memoria dado que son matrices y se les declara como valores 0.

3. Matriz de adyacencia → `void add_arista(int i, j ,weight)`

La variable miembro `matriz` una variable que es una matriz de adyacencia de dos dimensiones.

4. Algoritmo de wharsall → `void Grafo::floyd_warshall()`

   ### Primera Parte

   En los primeros dos `for` tenemos tres condicionales

   1. Primer condicional → `if (i != j && matriz[i][j] == 0)`

      Si en nuestra matriz de adyacencia esta en la diagonal principal o si el valor de la posicion de nuestra matriz `matriz[i][j]` es 0.

      **_Entonces,_** el valor de la matriz `matriz[i][j]` toma un valor infinito `INF`.

   2. Segundo condicional → `if (matriz[i][j] == INF)`

      Si en nuestra matriz de adyacencia el valor de la matriz `matriz[i][j]` es un valor infinito `INF`.

      **_Entonces,_** el valor de la `ruta[i][j]` tomara un valor infinito `-1` que indicara que la ruta no exite para `ruta[i][j]`

   3. Tercer condicional

      Caso contrario al segundo caso `ruta[i][j]` tomara el valor de j "el nodo apuntado por i".

   4. Algoritmo de Prim → `int min_ciclo(int nodo_inicio, int nodo_siguiente, bool status)`

   Funcion entera que se basa en el algoritmo de prim

   ### Segunda Parte

   Siguiendo con la explicacion tenemos dos condicionales.

   1. Primer condicional → `matriz[i][k] == INF || matriz[k][j] == INF`

      Si en nuestra matriz de adyacencia `matriz[j][k]` o `matriz[k][j]` tiene un valor `INF`

      **\*Entonces,** continue la ejecucion del codigo\*

   2. Segundo condicional → `(matriz[i][j] > matriz[i][k] + matriz[k][j])`

      Si en nuestra matriz de adyacencia el valor de la matriz `matriz[i][j]` es mayor entonces.

      **_Entonces,_** el valor de la `ruta[i][j]` actualizara el valor con la suma de `ruta[i][k]` y `ruta[k][j]` .Por ultimo `ruta[i][j]` tomara el valor de `ruta[i][k]`

5. Algoritmo de Prim → `int min_ciclo(int nodo_inicio, int nodo_siguiente, bool status)`

   Funcion entera que se basa en el algoritmo de prim

   1. El atributo de clase `longitud` es lo que retornada en nuestra funcion

   2. Si status es true nuestro agrera a los dos nodos al vector `ruta2` "vector de nuestro ciclo de menor coste"

   3. Dentro de nuestro `while` si nuestro cambio es menor a `n_vertices` "total de vertices" y q sea diferente de 0.

   4. Dentro de nuestro for comparamos

      1. Primer condicional → `if (matriz[vis][i] != 0 && (!visited[i]))`

         Lo cual indicaria que si ese nodo noha sido visitado y su valor es diferente de node pasa al siguiente condicional

         - `if(matriz[vis][i] < min)`

           Solo si `matriz[vis][i]` es menor entonces se actualizn los valores con los valores minimos.

      2. Antes de salir del while

      - Nuestro arreglo booleano `visited` se actualiza
      - `cambio` incrementa
      - longitud se actualiza con el valor de la matriz de adyacencia minima.
      - Por ultimo min toma el valor de infinito para volver encontrar el menor nodo en nuestro for.

   5. Por ultimo, nuestra longitud tomara el anterior nodo con nuestro nodo de inicio `712` para volver al inicio de nuestro ciclo. Y asi obtenemos el coste de minimo de nuestro ciclo.

## Observaciones

1. Como parte del proyecto se nos dio un archivo `entrada.txt` segun las indicaciones:

   **_"A continuación vienen N líneas, una por cada nodo. Cada línea i-ésima contiene dos enteros separados por un espacio en blanco: Xi, Yi, que indican las coordenadas relativas de la ciudad i-ésima en el mapa. Esta información se ofrece simplemente a efectos de visualización del grafo."_**

   Se trabajo con el archivo `input.txt` que es una replica de `entrada.txt` sin N lineas.

2. El costo computacional de la funcion miembro `void floyd_warshall` de la clase `Graph` es de n⁵, el cual para un entorno profesional no es recomendable.

## Resultados

El costo que se obtuvo en este reto es de 25186.

## Referencias

---

1. [Algoritmo de Prim](https://en.wikipedia.org/wiki/Prim's_algorithm#:~:text=In%20computer%20science%2C%20Prim%27s%20%28also%20known%20as%20Jarn%C3%ADk%27s%29,vertex%20at%20a%20time%2C%20from%20an%20arbitrary%20)
2. [Algoritmo de Floyd-Warshall](https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm#:~:text=Floyd%E2%80%93Warshall%20algorithm.%20In%20computer%20science%2C%20the%20Floyd%E2%80%93Warshall%20algorithm,negative%20edge%20weights%20%28but%20with%20no%20negative%20cycles%29.)
