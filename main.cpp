#include <iostream>
#include <vector>

using namespace std;

// Data structure to store adjacency list nodes
struct Node {
    int val;
    Node* next;
};

// Data structure to store a graph edge
struct Edge {
    int src, dest;
};

class Graph {
    // Function to allocate a new node for the adjacency list
    Node* getAdjListNode(int dest, Node* head) {
        Node* newNode = new Node;
        newNode->val = dest;

        // point new node to the current head
        newNode->next = head;

        return newNode;
    }
    int N;    // total number of nodes in the graph

public:
    // An array of pointers to Node to represent the
    // adjacency list
    Node **head;

    // Constructor
    Graph(Edge edges[], int n, int N) {
        // allocate memory
        head = new Node*[N]();
        this->N = N;

        // initialize head pointer for all vertices
        for (int i = 0; i < N ; i++) {
            head[i] = nullptr;
        }

        // add edges to the directed graph
        for (int i = 0; i < n; i++) {
            int src = edges[i].src;
            int dest = edges[i].dest;

            // insert at the beginning
            Node* newNode = getAdjListNode(dest, head[src]);

            // point head pointer to the new node
            head[src] = newNode;
        }
    }
    // Destructor
    ~Graph() {
        for (int i = 0; i < N; i++) {
            delete[] head[i];
        }

        delete[] head;
    }
};

//void printList(Node* ptr)
//{
//    while (ptr != nullptr)
//    {
//        cout << " —> " << ptr->val+1 << " ";
//        ptr = ptr->next;
//    }
//    cout << endl;
//}

Graph parseInputs(int Nnodes, int Nedges){
    if (Nnodes < 2 || Nedges < 0){
        cerr << "The number of nodes must be >= 2 and the number of edges must be >= 0" << endl;
        exit(0);
    }
    Edge edges [Nedges] = {};
    for (int i = 0; i<Nedges; i++){
        int n1, n2;
        Edge e{};
        cin >> n1 >> n2;
        e.src = n1-1;
        e.dest = n2-1;
        if ( e.src > Nnodes-1 || e.dest > Nnodes-1 || e.src < 0 || e.dest < 0){
            cerr << "The Node Number is invalid, please provide a number between 1 and " << Nnodes << endl;
            exit(0);
        }
        edges[i] = e;
    }
    return Graph(edges, Nedges, Nnodes);
}

int main() {
    int Nnodes, Nedges;
    cin >> Nnodes >> Nedges;
    Graph dominos = parseInputs(Nnodes, Nedges);


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
