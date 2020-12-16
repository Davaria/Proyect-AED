#include <fstream>
#include "lista.cpp"

#define INF 99999

using namespace std;

class Grafo
{
    int **ruta;       //para la matriz de rutas
    int **matriz;     //para la matriz de distancias
    Lista<int> ruta2; //para guardar la ruta de los nodos
    int n_vertices;   //numero de vertices
    int longitud;     //coste del ciclo

    fstream output; //para el arcvhivo de salida

public:
    Grafo(int);
    void add_arista(int, int, int);
    void floyd_warshall();
    int min_ciclo(int, int, bool);
    int get_ruta(int, int);
    void salida();
};

Grafo::Grafo(int n)
{
    n_vertices = n;
    //reservar memoria
    matriz = new int *[n_vertices + 1];
    for (int i = 1; i <= n_vertices; i++)
    {
        matriz[i] = new int[n_vertices + 1];
        for (int j = 0; j <= n_vertices; j++)
        {
            matriz[i][j] = 0;
        }
    }

    ruta = new int *[n_vertices + 1];
    for (int i = 1; i <= n_vertices; i++)
    {
        ruta[i] = new int[n_vertices + 1];
        for (int j = 0; j <= n_vertices; j++)
        {
            ruta[i][j] = 0;
        }
    }
}

void Grafo::add_arista(int i, int j, int weight)
{
    matriz[i][j] = weight;
    matriz[j][i] = weight;
}

//Para obtener la ruta
int Grafo::get_ruta(int a, int b)
{
    int temp = a, cont{0};
    // La segunda línea te pide el número de nodos que visita
    while (temp != ruta[temp][b])
    {
        temp = ruta[temp][b];
        output << temp << endl;
        cont++;
    }
    return cont;
}

//Para el archivo de salida
void Grafo::salida()
{
    output.open("output.txt");
    output << longitud << endl;
    output << n_vertices + 1 << endl;
    int _i = 1, n, cont = 1;
    Lista<int>::Iterador i;
    Lista<int>::Iterador j = ruta2.begin();
    output << *j << endl;

    for (i = ruta2.begin(); _i < ruta2.get_size(); i++)
    {
        n = *(++j);
        cont = cont + get_ruta(*i, n);

        _i++;
    }

    output.seekp(6);
    output << cont << endl;
    cout << "Vertices visitados " << cont << endl;
    output.close();
}

// Porque tiene que hallar el grafo completo
// Con todas las rutas
void Grafo::floyd_warshall()
{
    for (int i = 1; i <= n_vertices; i++)
    {
        for (int j = 1; j <= n_vertices; j++)
        {
            if (i != j && matriz[i][j] == 0)
                matriz[i][j] = INF;

            if (matriz[i][j] == INF)
                ruta[i][j] = -1;
            else
                ruta[i][j] = j;
        }
    }

    for (int k = 1; k <= n_vertices; k++)
    {
        for (int i = 1; i <= n_vertices; i++)
        {
            for (int j = 1; j <= n_vertices; j++)
            {
                if (matriz[i][k] == INF || matriz[k][j] == INF)
                    continue;

                if (matriz[i][j] > matriz[i][k] + matriz[k][j])
                {
                    matriz[i][j] = matriz[i][k] + matriz[k][j];
                    ruta[i][j] = ruta[i][k];
                }
            }
        }
    }
}

// Es un algoritmo que se basa en Prim árbol de expansión mínima
// Y busca un camino recorriendo todos los nodos

int Grafo::min_ciclo(int begin_node, int second_node, bool status)
{
    longitud = matriz[begin_node][second_node];
    if (status)
    {
        ruta2.insertar(begin_node);
        ruta2.insertar(second_node);
    }

    bool visited[n_vertices + 1];
    for (int i = 1; i <= n_vertices; i++)
    {
        visited[i] = false;
    }

    int q;
    q = second_node;
    visited[second_node] = true;

    int vis, min = INF;
    int cambio = 1;
    //Para encontrar un arbol de expansion minima
    while (q != 0 && cambio < n_vertices)
    {
        vis = q;
        q = 0;

        for (int i = 1; i <= n_vertices; i++)
        {
            if (matriz[vis][i] != 0 && (!visited[i]))
            {
                if (matriz[vis][i] < min)
                {
                    q = i;
                    min = matriz[vis][i];
                }
            }
        }
        if (status)
            ruta2.insertar(q);
        visited[q] = true;
        cambio++;
        longitud = longitud + matriz[vis][q];
        min = INF;
    }
    if (status)
        ruta2.insertar(begin_node);
    longitud = longitud + matriz[q][begin_node];
    return longitud;
}

int main()
{
    int vertex{0}, edge{0}, node_begin{0};
    ifstream input("input.txt");
    input >> vertex;
    input >> edge;
    input >> node_begin;
    cout << "Vertices: " << vertex << endl
         << "Aristas: " << edge << endl
         << "Inicio: " << node_begin << endl;

    Grafo graph(vertex);

    int src{0}, dest{0}, weight{0};
    while (!input.eof())
    {
        input >> src >> dest >> weight;
        graph.add_arista(src, dest, weight);
    }
    input.close();

    graph.floyd_warshall();

    int test, minn = 99999, nmin; //348 nodo
    for (int i = 1; i <= vertex; i++)
    {
        test = graph.min_ciclo(node_begin, i, false);
        if (test < minn)
        {
            minn = test;
            nmin = i;
        }
    }
    cout << nmin << endl;

    cout << graph.min_ciclo(node_begin, nmin, true) << endl;
    graph.salida();
}
