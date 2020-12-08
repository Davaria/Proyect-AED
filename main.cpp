#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
using namespace std;

// una estructura respresenta un
// peso de una arista en un grafo
// Arista
// class Edge
// {
// public:
//   int src, dest, weight;
// };

// class Graph
// {
// private:
//   void aletory();

// public:
//   int V, E;

//   ~Graph();
//   void generateAdj(int); // Generar matriz de adjecencia
//   void printAdj();       //Imprimir matriz
//   void printDot();       //Generar un archivo .dot
//   void createGraph(Graph &);
//   // graph representa una arreglo de aristas.
//   Edge *edge;
// };

// // void Graph::generateAdj(int v)
// // {
// //   V = v;
// //   matriz = new int *[V];
// //   for (int i = 0; i < V; i++)
// //     matriz[i] = new int[V];

// //   ifstream file;
// //   ofstream vertex;
// //   vertex.open("vertex.dot");
// //   file.open("./matriz.txt");
// //   vertex << "graph A {" << endl;
// //   for (int i = 0; i < V; i++)
// //   {
// //     vertex << "\t" << i << ";" << endl;
// //     for (size_t j = 0; j < V; j++)
// //     {
// //       file >> matriz[i][j];

// //       // cout << matriz[i][j];
// //       // if (rand() % 2 == 1)
// //       // {
// //       //   matriz[i][j] = 1;
// //       //   matriz[j][i] = 1;
// //       // }
// //       // else
// //       // {
// //       //   matriz[i][j] = 0;
// //       //   matriz[j][i] = 0;
// //       // }
// //     }
// //     // matriz[i][i] = 0;
// //   }
// //   vertex << "}";
// //   vertex.close();
// //   file.close();
// //   system("dot -Tpng ./vertex.dot -o vertex.png");
// //   this->aletory();
// // }

// void Graph::printAdj()
// {

//   cout << "  ";
//   for (int i = 0; i < V; i++)
//     cout << i + 1 << " ";
//   cout << endl;
//   for (int i = 0; i < V; i++)
//   {
//     cout << i + 1 << " ";
//     for (size_t j = 0; j < V; j++)
//       cout << matriz[i][j] << " ";
//     cout << endl;
//   }
// }

// // Crear un grafo con V vertices and E aristas
// void Graph::createGraph(Graph &graph)
// {
//   // Contamos el numero total de enlaces
//   int edge{0};
//   for (size_t i = 0; i < V; i++)
//   {
//     for (size_t j = 0; j < V; j++)
//     {
//       if (matriz[i][j])
//         edge++;
//     }
//   }
//   graph.E = edge;
//   graph.edge = new Edge[E];
//   srand(time(NULL)); // para generar numeros aleatorios

//   ofstream file;
//   file.open("tree.dot");
//   file << "graph A {" << endl;

//   for (size_t i = 0; i < V; i++)
//   {
//     for (size_t j = i; j < V; j++)
//     {
//       if (matriz[i][j])
//       {

//         graph.edge[i].src = i;
//         graph.edge[i].dest = j;
//         graph.edge[i].weight = 1 + rand() % 10; // generamos pesos aleatorios de 10
//         file << "\t" << i << " --" << j << " [label = \"" << graph.edge[i].weight << "\" ];" << endl;
//       }
//     }
//   }
//   file << "}";
//   file.close();
//   system("dot -Tpng ./tree.dot -o tree.png");
// }

// void Graph::aletory()
// {
//   int account{0};
//   for (size_t i = 0; i < V; i++)
//   {
//     for (size_t j = i; j < V; j++)
//     {
//       (matriz[i][j] == 0)
//           ? account += 1
//           : account;
//     }
//   }
//   account -= V;
//   srand(time(NULL));
//   int limit = rand() % 2 + 1;
//   cout << "La aletoriedad es de : " << limit << endl;

//   for (;;)
//   {
//     ofstream file;
//     file.open("./coordenadas.txt", ios::trunc);
//     account = 0;
//     for (size_t i = 0; i < V - 1; i++)
//     {
//       for (size_t j = i; j < V; j++)
//       {
//         if (i != j)
//         {
//           if (!matriz[i][j] && rand() % 2 == 1)
//           {
//             matriz[i][j] = 1;
//             matriz[j][i] = 1;
//             account++;
//             file << i << " " << j << endl;
//             // Almacenamos las variables en un archivo
//             cout << account << endl;
//           }
//         }
//       }
//     };
//     file.close();

//     if (account == limit)
//       break;

//     ifstream coord;
//     coord.open("./matriz.txt");
//     int i{0}, j{0};
//     while (!coord.eof())
//     {
//       coord >> i >> j;
//       matriz[i][j] = matriz[j][i] = 0;
//     };
//     coord.close();
//   };
// }

// // una estructura representa un subset para encontrar una union
// class subset
// {
// public:
//   int parent;
//   int rank;
// };

// // Una función de utilidad para encontrar el conjunto de un elemento i (utiliza la técnica de compresión de ruta)
// int find(subset subsets[], int i)
// {
//   // encontrar root y hacer root como padre de i (compresión de ruta)
//   if (subsets[i].parent != i)
//     subsets[i].parent = find(subsets, subsets[i].parent);

//   return subsets[i].parent;
// }

// // Una funcion que hace la union de dos conjuntos de x e y (utiliza la union por rango)
// void Union(subset subsets[], int x, int y)
// {
//   int xroot = find(subsets, x);
//   int yroot = find(subsets, y);

//   // Adjuntar arbol de rango mas pequeño bajo la raíz del arbol de alto rango (union por rango)
//   if (subsets[xroot].rank < subsets[yroot].rank)
//     subsets[xroot].parent = yroot;
//   else if (subsets[xroot].rank > subsets[yroot].rank)
//     subsets[yroot].parent = xroot;

//   // Si los rangos son los mismos, entonces haga uno como raíz e incremente su rango por uno
//   else
//   {
//     subsets[yroot].parent = xroot;
//     subsets[xroot].rank++;
//   }
// }

// // Compare dos bordes según sus pesos.
// // Se utiliza en qsort() para ordenar una matriz de bordes
// int myComp(const void *a, const void *b)
// {
//   Edge *a1 = (Edge *)a;
//   Edge *b1 = (Edge *)b;
//   return a1->weight > b1->weight;
// }

// // Algoritmo de kruskall
// void kruskall(Graph &graph)
// {
//   int V = graph.V;
//   Edge result[V];
//   int e = 0; // Una variable de índice, utilizada para result[]
//   int i = 0; // Una variable de índice, utilizada para aristas ordenadas

//   /*
//   Paso 1: Ordene todos los enlaces en orden no decreciente de su peso. Si no se nos permite cambiar el gráfico dado, podemos crear una copia de la matriz de enlaces
//   */
//   qsort(graph.edge, graph.E, sizeof(graph.edge[0]), myComp);

//   // Crear  un subconjunto
//   subset *subsets = new subset[(V * sizeof(subset))];

//   // Crear subconjuntos V con elementos individuales
//   for (int v = 0; v < V; ++v)
//   {
//     subsets[v].parent = v;
//     subsets[v].rank = 0;
//   }

//   // El numero de aristas es igual a V-1
//   while (e < V - 1 && i < graph.E)
//   {
//     // Paso 2: Elija el borde más pequeño. E incrementar el índice para la siguiente iteración
//     Edge next_edge = graph.edge[i++];

//     int x = find(subsets, next_edge.src);
//     int y = find(subsets, next_edge.dest);

//     /*
//       Si incluir este borde no causa ciclo, inclinelo en el resultado e incremente el índice de resultado para el siguiente borde
//      */
//     if (x != y)
//     {
//       result[e++] = next_edge;
//       Union(subsets, x, y);
//     }
//   }

//   cout << "Algoritmo de Kruskall " << endl;
//   int minimumCost = 0;
//   ofstream kruskall;
//   kruskall.open("kruskall.dot");
//   kruskall << "graph A {" << endl;
//   for (i = 0; i < e; ++i)
//   {
//     kruskall << "\t" << result[i].src << " -- " << result[i].dest << " [label = \"" << result[i].weight << "\" ];" << endl;
//     cout << result[i].src << " -- " << result[i].dest
//          << " == " << result[i].weight << endl;
//     minimumCost = minimumCost + result[i].weight;
//   }
//   kruskall << "}";
//   kruskall.close();
//   cout << "Costo minimo de el arbol de expasion minimo: " << minimumCost
//        << endl;
//   system("dot -Tpng ./kruskall.dot -o kruskall.png");
// }

void readFile(const string location_file)
{
  ifstream graph;
  ofstream file;

  graph.open(location_file);
  file.open("graph.dot");

  int v1{0}, v2{0};

  file << "graph A {" << endl;
  while (!graph.eof())
  {
    graph >> v1;
    graph >> v2;
    file << "\t" << v1 << " -- " << v2 << ";" << endl;
  }
  file << "}";
  graph.close();
  file.close();
  system("dot -Tpng ./graph.dot -o graph.png");
};

int main()
{
  // Se trabaja con el caso base
  // int V = 4;

  // Graph grafo;
  // grafo.generateAdj(V);
  // grafo.printAdj();
  // grafo.createGraph(grafo);
  // kruskall(grafo);
  readFile("nodes.txt");

  return 0;
}
