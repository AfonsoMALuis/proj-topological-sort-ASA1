#include <iostream>
#include <list>

unsigned long nInterventions = 0;
unsigned long *zeta;
bool *isHeadNode, *visited;

using namespace std;

class Graph{

public:
    unsigned long nNodes;
    list<unsigned long> *adj;
    Graph(unsigned long V);
    ~Graph();
    void addEdge(unsigned long src, unsigned long dest);
};

Graph::Graph(unsigned long V) {
    this->nNodes = V;
    this->adj = new list<unsigned long>[V];
}

void Graph::addEdge(unsigned long src, unsigned long dest) {
    adj[src].push_back(dest);
}

Graph::~Graph() {
}

void Topological_Sort_1(unsigned long u, Graph graph){
    visited[u] = true;

    for(unsigned long v: graph.adj[u]) {
        if (!visited[v]){
            Topological_Sort_1(v, graph);
        }
        zeta[u] = max(zeta[u], zeta[v]+1);
        if(isHeadNode[v]) {
            isHeadNode[v] = false;
            nInterventions--;
        }
    }

}

void Topological_Sort(Graph graph){
    isHeadNode = new bool[graph.nNodes];
    visited = new bool[graph.nNodes];
    zeta = new unsigned long[graph.nNodes];

    for (unsigned long i = 0; i < graph.nNodes; i++){
        isHeadNode[i] = visited [i] = false;
        zeta[i] = 1;
    }

    for (unsigned long i = 0; i < graph.nNodes; i++){
        if (!visited[i]){
            isHeadNode[i] = true;
            nInterventions++;
            Topological_Sort_1(i, graph);
        }
    }
}

Graph parseInputs() {
    unsigned long nNodes, nEdges;
    cin >> nNodes >> nEdges;
    Graph dominos = Graph(nNodes);
    if (nNodes < 2 || nEdges < 0){
        cerr << "The number of nodes must be >= 2 and the number of edges must be >= 0" << endl;
        exit(0);
    }
    for (unsigned long i = 0; i<nEdges; i++){
        unsigned long n1, n2;
        cin >> n1 >> n2;
        if ( n1 > nNodes || n2 > nNodes || n1 < 1 || n2 < 1){
            cerr << "The Node Number is invalid, please provide a number between 1 and " << nNodes << endl;
            exit(0);
        }
        dominos.addEdge(n1-1, n2-1);
    }
    return dominos;
}

int main() {
    Graph dominos = parseInputs();

    Topological_Sort(dominos);

    unsigned long maxValue=1;
    for (unsigned long i = 0; i < dominos.nNodes; i++){
      maxValue=max(maxValue, zeta[i]);
    }
    cout << nInterventions << " " << maxValue << endl;

    delete[] isHeadNode;
    delete[] visited;
    delete[] zeta;
    for (unsigned long i = 0; i < dominos.nNodes; i++){
        dominos.adj[i].clear();
    }
    delete[] dominos.adj;

    return 0;
}
