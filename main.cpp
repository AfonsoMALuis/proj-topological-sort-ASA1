#include <iostream>
#include <list>

int visited = 0, nSCC = 0, maxSCCElemnts = 0, nSCCElementsAux = 0;;

using namespace std;

// Data structure to store adjacency list nodes
//struct Node {
//    int val;
//    Node* next;
//};
//
// Data structure to store a graph edge
//struct Edge {
//    int src, dest;
//};
//
//class Graph {
//    // Function to allocate a new node for the adjacency list
//    Node* getAdjListNode(int dest, Node* head) {
//        Node* newNode = new Node;
//        newNode->val = dest;
//
//        // point new node to the current head
//        newNode->next = head;
//
//        return newNode;
//    }
//    int N;    // total number of nodes in the graph
//
//public:
//    // An array of pointers to Node to represent the
//    // adjacency list
//    Node **head;
//
//    vector<int> d, low;
//
//
//    // Constructor
//    Graph(Edge edges[], int n, int N) {
//        // allocate memory
//        head = new Node*[N]();
//        this->N = N;
//
//        this->d[N];
//        this->low[N];
//
//        // initialize head pointer for all vertices
//        for (int i = 0; i < N ; i++) {
//            head[i] = nullptr;
//        }
//
//        // add edges to the directed graph
//        for (int i = 0; i < n; i++) {
//            int src = edges[i].src;
//            int dest = edges[i].dest;
//
//            // insert at the beginning
//            Node* newNode = getAdjListNode(dest, head[src]);
//
//            // point head pointer to the new node
//            head[src] = newNode;
//        }
//    }
//    // Destructor
//    ~Graph() {
//        for (int i = 0; i < N; i++) {
//            delete[] head[i];
//        }
//
//        delete[] head;
//    }
//
//    int getNodeNumber(){
//        return N;
//    }
//};

class Graph{
    int Nnodes;
    list<int> *adj;

    void Tarjan_Visit(int u, int *d, int *low);

public:
    Graph(int V);
    void addEdge(int src, int dest);
    void SCC_Tarjan();
};

Graph::Graph(int V) {
    this->Nnodes = V;
    this->adj = new list<int>[V];
}

void Graph::addEdge(int src, int dest) {
    adj[src].push_back(dest);
}

void Graph::Tarjan_Visit(int u, int *d, int *low){
    d[u] = low[u] = visited;
    visited++;
    list<int>::iterator iterator;
    for(iterator = adj[u].begin(); iterator != adj[u].end(); iterator++){
        int v = *iterator;
        if (d[v] == -1)
            Tarjan_Visit(v, d, low);
        low[u] = min(low[u], low[v]);
    }
    if (d[u] == low[u]){
        nSCC++;
//        cout << u << ": d[u]= " << d[u] << " low[u]= " << low[u] << endl;
    }

}

void Graph::SCC_Tarjan() {
    int *d = new int[Nnodes];
    int *low = new int[Nnodes];

    for(int i = 0; i < Nnodes; i++){
        d[i] = -1;
        low[i] = -1;
    }

    for (int i = 0; i < Nnodes; i++){
        if (d[i] == -1)
            Tarjan_Visit(i, d, low);
    }
}

//void printList(Node* ptr)
//{
//    while (ptr != nullptr)
//    {
//        cout << " —> " << ptr->val+1 << " ";
//        ptr = ptr->next;
//    }
//    cout << endl;
//}

Graph parseInputs(){
    int Nnodes, Nedges;
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
        dominos.addEdge(n1, n2);
    }
    return dominos;
}

int main() {
    Graph dominos = parseInputs();
    dominos.SCC_Tarjan();


    cout << nSCC << " " /*<< maxSCCElemnts*/<< endl;


//    for (int i = 0; i < Nnodes ; i++)
//    {
//        // print given vertex
//        cout << i+1 << " ——";
//
//        // print all its neighboring vertices
//        printList(dominos.head[i]);
//    }
    return 0;
}
