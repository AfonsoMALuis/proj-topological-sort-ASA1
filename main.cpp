#include <iostream>
#include <list>
#include <algorithm>

int Nnodes, Nedges, nInterventions = 0;
int *zeta;
bool *isHeadNode, *visited;

using namespace std;

class Graph{

public:
    int Nnodes;
    list<int> *adj;
    Graph(int V);
    ~Graph();
    void addEdge(int src, int dest);
};

Graph::Graph(int V) {
    this->Nnodes = V;
    this->adj = new list<int>[V];
}

void Graph::addEdge(int src, int dest) {
    adj[src].push_back(dest);
}

Graph::~Graph() {
//    for (int i = 0; i < Nnodes; i++){
//        adj[i].~list<int>();
//    }
//    adj->clear();
    //delete[] adj;
}

void Topological_Sort_1(int u, list<int> *adj){
    visited[u] = true;

    list<int>::iterator iterator;
    for(iterator = adj[u].begin(); iterator != adj[u].end(); iterator++) {
        if (!visited[*iterator]){
            Topological_Sort_1(*iterator, adj);
        }
        zeta[u] = max(zeta[u], zeta[*iterator]+1);
        if(isHeadNode[*iterator]) {
            isHeadNode[*iterator] = false;
            nInterventions--;
        }
    }

}

void Topological_Sort(Graph graph){
    isHeadNode = new bool[Nnodes];
    visited = new bool[Nnodes];
    zeta = new int[Nnodes];

    for (int i = 0; i < Nnodes; i++){
        isHeadNode[i] = visited [i] = false;
        zeta[i] = 1;
    }

    for (int i = 0; i < Nnodes; i++){
        if (!visited[i]){
            isHeadNode[i] = true;
            nInterventions++;
            Topological_Sort_1(i, graph.adj);
        }
    }
}

Graph parseInputs() {
    cin >> Nnodes >> Nedges;
    Graph dominos = Graph(Nnodes);
    if (Nnodes < 2 || Nedges < 0){
        cerr << "The number of nodes must be >= 2 and the number of edges must be >= 0" << endl;
        exit(0);
    }
    for (int i = 0; i<Nedges; i++){
        int n1, n2;
        cin >> n1 >> n2;
        if ( n1 > Nnodes || n2 > Nnodes || n1 < 1 || n2 < 1){
            cerr << "The Node Number is invalid, please provide a number between 1 and " << Nnodes << endl;
            exit(0);
        }
        dominos.addEdge(n1-1, n2-1);
    }
    return dominos;
}

int main() {
    Graph dominos = parseInputs();
    Topological_Sort(dominos);
//    for (int i = 0; i < Nnodes; i++){
//        if(isHeadNode[i])
//            nInterventions++;
//    }
    cout << nInterventions << " " << *max_element(zeta, zeta + Nnodes) << endl;
    delete[] isHeadNode;
    delete[] visited;
    delete[] zeta;
    return 0;
}
