#ifndef GRAPH_H
#define GRAPH_H

#include <QString>
#include <QVector>
#include <QMap>
#include <QPair>
#include <limits>

struct Edge {
    QString to;
    double length;
    double k;

    Edge() : length(0), k(0.8) {}
    Edge(const QString& t, double l, double coeff)
        : to(t), length(l), k(coeff) {}

    double weight() const { return length * k; }
};

struct Vertex {
    QString name;
    double x, y;

    Vertex() : x(0), y(0) {}
    Vertex(const QString& n, double cx, double cy)
        : name(n), x(cx), y(cy) {}
};

class Graph {
public:
    Graph();

    void addVertex(const QString& name, double x, double y);
    void addEdge(const QString& from, const QString& to, double length);

    QVector<Vertex> getVertices() const;
    QVector<Edge> getNeighbors(const QString& vertex) const;
    QVector<QPair<QString, QString>> getAllEdges() const;

    void simulateTraffic();

    double getEdgeK(const QString& from, const QString& to) const;
    double getEdgeLength(const QString& from, const QString& to) const;

    QVector<QString> findShortestPath(const QString& start, const QString& end) const;

    bool hasVertex(const QString& name) const;
    void clear();

    QString getAdjacencyListString() const;

private:
    QMap<QString, QVector<Edge>> adjacencyList;
    QMap<QString, Vertex> vertices;

    static const QVector<double> trafficCoeffs;
};

#endif // GRAPH_H
