#include <fstream>
#include "lista.cpp"

#define INF 99999

using namespace std;

class Grafo{
    int** ruta;  //para la matriz de rutas
    int** matriz;  //para la matriz de distancias
    Lista<int> ruta2; //para guardar la ruta de los nodos
    int n_vertices; //numero de vertices
    int longitud;  //coste del ciclo

    fstream c_min; //para el arcvhivo de salida

    public: 
        Grafo(int n);
        void add_arista(int i, int j, int d);  
        void floyd_warshall();
        int min_ciclo(int inic,int inicio, bool est);
        int get_ruta(int a, int b);
        void salida();
};

Grafo::Grafo(int n){
    n_vertices=n;
    //reservar memoria
    matriz = new int* [n_vertices+1];
    for (int i = 1; i <= n_vertices; i++){
        matriz[i] = new int[n_vertices+1];
        for (int j = 0; j <= n_vertices; j++){
            matriz[i][j] = 0; 
        }
    }

    ruta = new int* [n_vertices+1];
    for (int i = 1; i <= n_vertices; i++){
        ruta[i] = new int[n_vertices+1];
        for (int j = 0; j <= n_vertices; j++){
            ruta[i][j] = 0;
        }
    }
}

void Grafo::add_arista(int i, int j, int d){
    matriz[i][j]=d;
    matriz[j][i]=d;
}

//Para obtener la ruta
int Grafo::get_ruta(int a,int b){
    int temp=a,cont=0;
    while (temp!=ruta[temp][b]){
        temp=ruta[temp][b];
        c_min<<temp<<endl;
        cont++;
    }
    return cont;
}

//Para el archivo de salida
void Grafo::salida(){
    c_min.open("cmin");
    c_min<<longitud<<endl;
    c_min<<n_vertices+1<<endl;
    int _i=1,n,cont=1;
    Lista<int>::Iterador i;
    Lista<int>::Iterador j=ruta2.begin();
    c_min<<*j<<endl;
    
    for (i = ruta2.begin(); _i < ruta2.get_size(); i++){
        n=*(++j);
        cont = cont + get_ruta(*i,n);
        
        _i++;
    }

    c_min.seekp(6);
    c_min<<cont<<endl;
    cout<<"Vertices visitados "<<cont<<endl;
}

void Grafo::floyd_warshall(){
    for (int i = 1; i <= n_vertices; i++){
        for (int j = 1; j <= n_vertices; j++){
            if (i!=j && matriz[i][j]==0)
                matriz[i][j]=INF;

            if (matriz[i][j] == INF)  
                ruta[i][j] = -1;  
            else
                ruta[i][j] = j;  
        }
    }

    for (int k = 1; k <= n_vertices; k++){
        for (int i = 1; i <= n_vertices; i++){
            for (int j = 1; j <= n_vertices; j++){
                if (matriz[i][k] == INF || matriz[k][j] == INF)  
                    continue;  
  
                if (matriz[i][j] > matriz[i][k] + matriz[k][j]) {  
                    matriz[i][j] = matriz[i][k] + matriz[k][j];
                    ruta[i][j] = ruta[i][k];
                }
            }
        }
    }
}

int Grafo::min_ciclo(int inic,int s,bool est){
    longitud=matriz[inic][s];
    if(est){
        ruta2.insertar(inic);
        ruta2.insertar(s);
    }

    bool visited[n_vertices+1];
    for (int i = 1; i <= n_vertices ; i++){
        visited[i]=false;
    }
    
    int q;
    q=s;
    visited[s] = true;
  
    int vis,min=INF;
    int cambio=1;
    //Para encontrar un arbol de expansion minima
    while (q!=0 && cambio < n_vertices ){
        vis = q;
        q=0;

        for (int i = 1; i <= n_vertices; i++){
            if (matriz[vis][i] != 0 && (!visited[i])){
                if(matriz[vis][i]<min){
                    q = i;
                    min=matriz[vis][i];
                }
            }
        }
        if(est)
            ruta2.insertar(q);
        visited[q] = true;
        cambio++;
        longitud = longitud + matriz[vis][q];
        min=INF;
    }
    if(est)
        ruta2.insertar(inic);
    longitud = longitud + matriz[q][inic];
    return longitud;
}

int main(){
    int v,a,inicio;
    ifstream in("input");
    in>>v;
    in>>a;
    in>>inicio;
    cout<<"Vertices "<<v<<" Aristas "<<a<<" Inicio "<<inicio<<endl;
    Grafo g(v);
    
    int i,j,d;
    while (!in.eof()){
        in>>i>>j>>d;
        g.add_arista(i,j,d);
    }

    g.floyd_warshall();
    //cout<<"Costo "<<g.min_ciclo(inicio,348)<<endl;

    
    //Para encontrar el nodo de inicio con menor coste
    int test,minn=99999,nmin;  //348 nodo
    for (int i = 1; i <= v; i++){
        test = g.min_ciclo(inicio,i,false);
        if(test<minn){
            minn=test;
            nmin=i;
        }
    }
    cout<<nmin<<endl;
    
    cout<<g.min_ciclo(inicio,nmin,true)<<endl;
    g.salida();
}
