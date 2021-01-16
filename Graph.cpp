//
// Created by Mario Eberth on 16.01.21.
//

#include "Graph.h"

using namespace std;

Graph::Graph() {

}

std::vector<MyVertex> Graph::getVertices() {
    return vertices;
}

int Graph::getNumberOfVertices() {
    return vertices.size();
}

int Graph::insertVertex(MyVertex v) {
    if (find(vertices.begin(), vertices.end(), v) != vertices.end()) {
        return -1;
    } else {
        vertices.push_back(v);
        return vertices.size() - 1;
    }
}

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

bool Graph::compareEdge(MyVertex v1, MyVertex v2, int weight) {
    for (int i = 0; i < edges.size(); ++i) {
        if (edges.at(i).weight == weight && edges.at(i).in == v1 && edges.at(i).out == v2) {
            return true;
        } else {
            return false;
        }
    }
}

int Graph::getEdgeWeight(MyVertex v1, MyVertex v2) {
    for (int i = 0; i < edges.size(); i++) {
        if (edges.at(i).in == v1 && edges.at(i).out == v2) {
            return edges.at(i).weight;
        }
    }
    return -1;
}


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

