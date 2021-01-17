#include <iostream>
#include "Graph.h"
using namespace std;

int main() {
    std::cout << "Graph 1" << std::endl;

    Graph *h = new Graph;
    MyVertex *v1 = new MyVertex("mario");
    MyVertex *v2 = new MyVertex("paul");
    MyVertex *v3 = new MyVertex("Stefan");
    MyVertex *v4 = new MyVertex("Selin");
    MyVertex *v5 = new MyVertex("Luki");

    h->insertVertex(*v1);
    h->insertVertex(*v2);
    h->insertVertex(*v3);
    h->insertVertex(*v4);
    h->insertVertex(*v5);


    h->insertVertex(*new MyVertex("mario"));

    //create connected graph
    cout << "insertEdge v1 to v2: " <<h->insertEdge(*v1,*v2,1) << endl;
    cout << "insertEdge v1 to v2 again: " << h->insertEdge(*v1,*v2,1) << endl;
    cout << "insertEdge v1 to v3: " << h->insertEdge(*v1,*v3,3) << endl;
    cout << "insertEdge v3 to v1: " << h->insertEdge(*v3,*v1,4) << endl;
    cout << "insertEdge v4 to v5: " << h->insertEdge(*v4,*v5,5) << endl;

    cout << "getEdgeWeight v1 to v2: " << h->getEdgeWeight(*v1,*v2) << endl;
    cout << "getEdgeWeight v1 to v3: " << h->getEdgeWeight(*v1,*v3) << endl;

    h->dfs();


    vector<MyVertex> vertices = h->getVertices();
    int numberOfVertices = h->getNumberOfVertices();

    cout << endl;
    cout << "<<< vertices list >>>" << endl;
    for(int i = 0; i<vertices.size(); i++){
        cout << vertices.at(i) << endl;
    }

    vector<vector<int>> matrix = h->getAdjacencyMatrix();

    cout << endl;
    cout << "<<< adjacencyMatrix >>>" << endl;
    for (int i = 0; i < h->getNumberOfVertices(); ++i) {
        for (int j = 0; j < h->getNumberOfVertices(); ++j) {
            if (matrix[i][j] == -1){
                cout << " " << matrix[i][j];
            } else {
                cout << "  " << matrix[i][j];
            }
        }
        cout << endl;
    }

    vector<MyVertex> res = h->getAdjacentVertices(*v1);

    cout << endl;
    cout << "AdjacentVertices for v1 (mario)" << endl;
    for (int i = 0; i < res.size(); ++i) {
        cout << res.at(i) << endl;
    }

    cout << endl;
    cout << "<<< print Components >>>" << endl;
    h->printComponents();

    cout << endl;
    cout << "number of Components: " << h->getNumberOfComponents() << endl;
    cout << "is cyclic: " << h->isCyclic() << endl;
    cout << "is connected: " << h->isConnected() << endl;

    cout << endl;
    cout << "<<< Graph 2 >>>" << endl;
    cout << endl;

    Graph *h1 = new Graph;
    MyVertex *v6 = new MyVertex("crazyBoy");
    MyVertex *v7 = new MyVertex("leftBoy");
    MyVertex *v8 = new MyVertex("dude");

    h1->insertVertex(*v6);
    h1->insertVertex(*v7);
    h1->insertVertex(*v8);

    cout << "insertEdge v6 to v7: " <<h1->insertEdge(*v6,*v7,1) << endl;
    cout << "insertEdge v7 to v8: " <<h1->insertEdge(*v7,*v8,2) << endl;

    h1->dfs();

    h1->printComponents();

    cout << "is connected: " << h1->isConnected() << endl;
    cout << "is Cyclic: " << h1->isCyclic() << endl;

    cout << endl;

    return 0;
}
