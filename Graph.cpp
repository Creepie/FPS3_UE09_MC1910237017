//
// Created by Mario Eberth on 16.01.21.
//

#include "Graph.h"
#include <iostream>

using namespace std;


/**
 * Erzeugt einen neuen Graphen
 */
Graph::Graph() {

}

/**
 * Gibt einen vector aller eingefuegten Knoten zurueck
 * @return a vector list of current saved Vertex
 */
std::vector<MyVertex> Graph::getVertices() {
    return vertices;
}

/**
 * Gibt die Anzahl der eingefuegten Knoten zurueck
 * @return the size of the vertices
 */
int Graph::getNumberOfVertices() {
    return vertices.size();
}

/**
 * Fuegt neuen Knoten v in den Graphen ein und liefert seinen Index
 * im Knotenvector, oder -1 wenn der Knoten bereits eingefügt ist
 * @param v represent the given MyVertex object
 * @return index of insertedVertex > else -1 if already exist
 */
int Graph::insertVertex(MyVertex v) {
    if (find(vertices.begin(), vertices.end(), v) != vertices.end()) {
        return -1;
    } else {
        vertices.push_back(v);
        return vertices.size() - 1;
    }
}

/**
 * Fuegt eine ungerichtete Kante mit dem Gewicht weight zwischen den
 * Knoten v1 und v2 ein. Die Methode liefert false
 * falls die Kante bereits existiert, sonst true
 * @param v1 represent the first MyVertex object
 * @param v2 represent the second MyVertex object
 * @param weight represent the weight of the edge
 * @return true if inserted, else false
 */
bool Graph::insertEdge(MyVertex v1, MyVertex v2, int weight) {
    if ((find(vertices.begin(), vertices.end(), v1) != vertices.end())) {
        if (find(vertices.begin(), vertices.end(), v2) != vertices.end()) {
            if (!compareEdge(v1, v2, weight)) {
                Edge edge;
                edge.in = v1;
                edge.out = v2;
                edge.weight = weight;
                edges.push_back(edge);
                return true;
            }
        }
    }
    return false;
}

/**
 * this method is to compare if a Edge is the same
 * @param v1 represent the first MyVertex object
 * @param v2 represent the second MyVertex object
 * @param weight is the given weight
 * @return true if already exists, else false
 */
bool Graph::compareEdge(MyVertex v1, MyVertex v2, int weight) {
    for (int i = 0; i < edges.size(); ++i) {
        if (edges.at(i).weight == weight && edges.at(i).in == v1 && edges.at(i).out == v2) {
            return true;
        } else {
            return false;
        }
    }
}

/**
 * this method return the weight of an Edge
 * @param v1 represent the first MyVertex object
 * @param v2 represent the second MyVertex object
 * @return the weight if exists, else -1
 */
int Graph::getEdgeWeight(MyVertex v1, MyVertex v2) {
    for (int i = 0; i < edges.size(); i++) {
        if (edges.at(i).in == v1 && edges.at(i).out == v2) {
            return edges.at(i).weight;
        }
    }
    return -1;
}

/**
 * Liefert eine NxN Adjazenzmatrix für diesen Graphen, wobei N = getNumVertices().
 * Die Matrix enthält die Gewichte der Kanten (>=0).
 * @return a double adjacencyMatrix
 */
std::vector<std::vector<int>> Graph::getAdjacencyMatrix() {
    vector<vector<int>> matrix(vertices.size(), vector<int>(vertices.size(), -1));
    for (int i = 0; i < vertices.size(); ++i) {
        matrix[i][i] = 0;
    }

    for (int i = 0; i < edges.size(); ++i) {
        //get x and y edges
        int x = find(vertices.begin(), vertices.end(), edges.at(i).in) - vertices.begin();
        int y = find(vertices.begin(), vertices.end(), edges.at(i).out) - vertices.begin();

        //update value
        matrix[x][y] = edges.at(i).weight;
        matrix[y][x] = edges.at(i).weight;
    }
    return matrix;
}

/**
 * Liefert einen Vector von Knoten welche adjazent zum Knoten v sind.
 * @param v is the given MyVertex Object
 * @return a vector of adjacentVertices
 */
std::vector<MyVertex> Graph::getAdjacentVertices(MyVertex v) {
    vector<MyVertex> vector;

    for(int i = 0; i < edges.size(); i++){
        if (edges.at(i).in.name == v.name){
            if (find(vector.begin(), vector.end(), edges.at(i).in) == vector.end()){
                vector.push_back(edges.at(i).out);
            }
        } else if (edges.at(i).out.name == v.name){
            if (find(vector.begin(), vector.end(), edges.at(i).out) == vector.end()){
                vector.push_back(edges.at(i).in);
            }
        }
    }
    return vector;
}

/**
 * Liefert true wenn der Graph verbunden ist, sonst false
 * @return true if connected, else false
 */
bool Graph::isConnected() {
    return getNumberOfComponents() == 1;
}

/**
 * Gibt die Anzahl der Komponenten des Graphen zurück
 * @return
 */
int Graph::getNumberOfComponents() {
    return components.size();
}

/**
 * Gibt die Knoten aller Komponenten aus (eine Zeile pro Komponente).
 */
void Graph::printComponents() {
    components.clear();
    dfs();
    for (int i = 0; i < components.size(); ++i) {
        for (int j = 0; j < components.at(i).size(); ++j) {
            cout << components.at(i).at(j);
        }
        cout << endl;
    }
}

/**
 * Liefert true wenn der Graph Zyklen enthält, sonst false.
 * @return if isCyclic, else false
 */
bool Graph::isCyclic() {
    return cyclic;
}

/**
 * this method checks every node in the graph
 */
void Graph::dfs() {
  vector<Color> colors;
  for(auto v : vertices){
      colors.push_back(WHITE);
  }
  int time = 0;
  for (auto v : vertices){
      if (colorOfVertex(v,colors) == WHITE){
          components.push_back(vector<MyVertex>());
          dfsVisit(v, colors, time);
          time = time +1;
      }
  }
}

/**
 * this method is a helping method of dfsVisit
 * @param v is the given MyVertex object
 * @param colors is the vector list of colors
 * @param time is the given loop time
 */
void Graph::dfsVisit(MyVertex v, std::vector<Color> &colors, int time) {
    colors[indexOfVertex(v)] = GRAY;
    components.at(time).push_back(v);
    int visited = 0;

    for (auto adj_vertex : getAdjacentVertices(v)) {
        if (colorOfVertex(adj_vertex,colors) == GRAY){
            visited++;
            if (visited > 1){
                cyclic = true;
            }
        }
        if (colorOfVertex(adj_vertex, colors) == WHITE) {
            dfsVisit(adj_vertex, colors, time);
        }
    }
    colors[indexOfVertex(v)] = BLACK;

}

/**
 * this method return the right color of given Vertex
 * @param v is the given vertex
 * @param colors is the given color vector
 * @return the right color
 */
Color Graph::colorOfVertex(MyVertex v, std::vector<Color> colors) {
    int index = indexOfVertex(v);
    return colors.at(index);
}

/**
 * this method return the index of the given vertex
 * @param v is the given MyVertex object
 * @return the index
 */
int Graph::indexOfVertex(MyVertex v) {
    return find(vertices.begin(), vertices.end(), v) - vertices.begin();
}

