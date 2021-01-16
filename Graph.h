//
// Created by Mario Eberth on 16.01.21.
//

#ifndef FPS3_UE09_MC1910237017_GRAPH_H
#define FPS3_UE09_MC1910237017_GRAPH_H

#include <vector>
#include <algorithm>
#include <limits>
#include <string>
enum Color{WHITE, GRAY, BLACK};
struct MyVertex {
    std::string name;

    MyVertex() {
        this->name = "";
    }

    MyVertex(std::string name) {
        this->name = name;
    }
    inline bool operator==(const MyVertex& rhs) const {
        return name == rhs.name;
    }
    inline bool operator!=(const MyVertex& rhs) const {
        return !(*this == rhs);
    }

    friend std::ostream &operator<<(std::ostream &os, MyVertex &p) {
        std::string text = "Vertext[";
        text.append(p.name);
        text.append("]");
        os << text;
        return os;
    }
};

class Graph {
private:
    struct Edge {
        MyVertex in;
        MyVertex out;
        int weight;
    };

    std::vector<MyVertex> vertices;
    std::vector<Edge> edges;
    std::vector<std::vector<MyVertex>> components;
    bool cyclic = false;

    bool compareEdge(MyVertex v1, MyVertex v2, int weight);
    int dfs();
    void dfsVisit(MyVertex v, std::vector<Color> &colors, int time);
    Color colorOfVertex(MyVertex v, std::vector<Color> colors);
    int indexOfVertex(MyVertex v);




public:
    /* Erzeugt einen neuen Graphen */
    Graph();

    /* Gibt die Anzahl der eingefuegten Knoten zurueck */
    int getNumberOfVertices();

    /* Gibt einen vector aller eingefuegten Knoten zurueck */
    std::vector<MyVertex> getVertices();

    /* Fuegt neuen Knoten v in den Graphen ein und liefert seinen Index
    im Knotenvector, oder -1 wenn der Knoten bereits eingefügt ist */
    int insertVertex(MyVertex v);

    /* Liefert das Gewicht der Kante zwischen Knoten v1 und v2 wenn
    sie existiert, ansonsten -1. */
    int getEdgeWeight(MyVertex v1, MyVertex v2);

    /* Fuegt eine ungerichtete Kante mit dem Gewicht weight zwischen den
    Knoten v1 und v2 ein. Die Methode liefert false
    falls die Kante bereits existiert, sonst true. */
    bool insertEdge(MyVertex v1, MyVertex v2, int weight);

    /* Liefert eine NxN Adjazenzmatrix für diesen Graphen, wobei N =
    getNumVertices().
    Die Matrix enthält die Gewichte der Kanten (>=0). */
    std::vector<std::vector<int>> getAdjacencyMatrix();
    /* Liefert einen Vector von Knoten welche adjazent zum Knoten v
    sind. */
    std::vector<MyVertex> getAdjacentVertices(MyVertex v);

    //Aufgabe 2:

    // Liefert true wenn der Graph verbunden ist, sonst false.
    bool isConnected();

    // Gibt die Anzahl der Komponenten des Graphen zurück.
    int getNumberOfComponents();

    /* Gibt die Knoten aller Komponenten aus (eine Zeile pro
    Komponente). */
    void printComponents();

    // Liefert true wenn der Graph Zyklen enthält, sonst false.
    bool isCyclic();
};

#endif //FPS3_UE09_MC1910237017_GRAPH_H
