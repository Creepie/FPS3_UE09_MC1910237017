#include <iostream>
#include "Graph.h"
using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;

    Graph *h = new Graph;
    MyVertex *v1 = new MyVertex("mario");
    MyVertex *v2 = new MyVertex("paul");
    MyVertex *v3 = new MyVertex("Stefan");

    h->insertVertex(*v1);
    h->insertVertex(*v2);
    h->insertVertex(*v3);

    h->insertVertex(*new MyVertex("mario"));

    cout << h->insertEdge(*v1,*v2,2) << endl;
    cout << h->insertEdge(*v1,*v2,2) << endl;
    cout << h->insertEdge(*v1,*v3,3) << endl;

    cout << h->getEdgeWeight(*v1,*v2) << endl;
    cout << h->getEdgeWeight(*v1,*v3) << endl;

    vector<MyVertex> vertices = h->getVertices();
    int numberOfVertices = h->getNumberOfVertices();

    for(int i = 0; i<vertices.size(); i++){
        cout << vertices.at(i) << endl;
    }

    vector<vector<int>> matrix = h->getAdjacencyMatrix();

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
    for (int i = 0; i < res.size(); ++i) {
        cout << res.at(i) << endl;
    }


    cout << endl;

    return 0;
}
