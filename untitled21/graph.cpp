#include "graph.h"
#include <QRandomGenerator>
#include <QDebug>
#include <QSet>
#include <QList>

const QVector<double> Graph::trafficCoeffs = {0.8, 1.2, 1.9, 3.3};

Graph::Graph() {
}

void Graph::addVertex(const QString& name, double x, double y) {
    vertices[name] = Vertex(name, x, y);
    if (!adjacencyList.contains(name)) {
        adjacencyList[name] = QVector<Edge>();
    }
}

void Graph::addEdge(const QString& from, const QString& to, double length) {
    if (!vertices.contains(from)) addVertex(from, 0, 0);
    if (!vertices.contains(to)) addVertex(to, 0, 0);

    double initialK = 0.8;
    adjacencyList[from].append(Edge(to, length, initialK));
    adjacencyList[to].append(Edge(from, length, initialK));
}

QVector<Vertex> Graph::getVertices() const {
    QList<Vertex> list = vertices.values();
    return QVector<Vertex>(list.begin(), list.end());
}

QVector<Edge> Graph::getNeighbors(const QString& vertex) const {
    return adjacencyList.value(vertex);
}

QVector<QPair<QString, QString>> Graph::getAllEdges() const {
    QVector<QPair<QString, QString>> edges;
    QSet<QString> visited;

    for (auto it = adjacencyList.constBegin(); it != adjacencyList.constEnd(); ++it) {
        const QString& from = it.key();
        for (const Edge& e : it.value()) {
            QString key1 = from + "-" + e.to;
            QString key2 = e.to + "-" + from;
            if (!visited.contains(key1) && !visited.contains(key2)) {
                edges.append(qMakePair(from, e.to));
                visited.insert(key1);
            }
        }
    }
    return edges;
}

void Graph::simulateTraffic() {
    for (auto it = adjacencyList.begin(); it != adjacencyList.end(); ++it) {
        QVector<Edge>& edges = it.value();
        for (Edge& e : edges) {
            int idx = QRandomGenerator::global()->bounded(trafficCoeffs.size());
            e.k = trafficCoeffs[idx];
        }
    }
    qDebug() << "Загруженность дорог изменена";
}

double Graph::getEdgeK(const QString& from, const QString& to) const {
    const QVector<Edge>& edges = adjacencyList.value(from);
    for (const Edge& e : edges) {
        if (e.to == to) return e.k;
    }
    return 0.8;
}

double Graph::getEdgeLength(const QString& from, const QString& to) const {
    const QVector<Edge>& edges = adjacencyList.value(from);
    for (const Edge& e : edges) {
        if (e.to == to) return e.length;
    }
    return 0;
}

bool Graph::hasVertex(const QString& name) const {
    return vertices.contains(name);
}

void Graph::clear() {
    adjacencyList.clear();
    vertices.clear();
}

QString Graph::getAdjacencyListString() const {
    QString result = "Список смежности:\n";
    for (auto it = adjacencyList.constBegin(); it != adjacencyList.constEnd(); ++it) {
        result += it.key() + " -> ";
        const QVector<Edge>& edges = it.value();
        for (int i = 0; i < edges.size(); i++) {
            result += edges[i].to;
            if (i < edges.size() - 1) result += ", ";
        }
        result += "\n";
    }
    return result;
}

QVector<QString> Graph::findShortestPath(const QString& start, const QString& end) const {
    QVector<QString> emptyPath;

    if (!vertices.contains(start) || !vertices.contains(end)) {
        qWarning() << "Одна из вершин не существует";
        return emptyPath;
    }

    if (start == end) {
        emptyPath.append(start);
        return emptyPath;
    }

    QMap<QString, double> dist;
    QMap<QString, QString> prev;
    QSet<QString> visited;

    for (auto it = vertices.constBegin(); it != vertices.constEnd(); ++it) {
        dist[it.key()] = std::numeric_limits<double>::max();
    }
    dist[start] = 0;

    while (visited.size() < vertices.size()) {
        QString u;
        double minDist = std::numeric_limits<double>::max();

        for (auto it = vertices.constBegin(); it != vertices.constEnd(); ++it) {
            if (!visited.contains(it.key()) && dist[it.key()] < minDist) {
                minDist = dist[it.key()];
                u = it.key();
            }
        }

        if (u.isEmpty() || minDist == std::numeric_limits<double>::max()) {
            break;
        }

        visited.insert(u);
        if (u == end) break;

        const QVector<Edge>& neighbors = adjacencyList.value(u);
        for (const Edge& e : neighbors) {
            if (!visited.contains(e.to)) {
                double newDist = dist[u] + e.weight();
                if (newDist < dist[e.to]) {
                    dist[e.to] = newDist;
                    prev[e.to] = u;
                }
            }
        }
    }

    if (dist[end] == std::numeric_limits<double>::max()) {
        qWarning() << "Путь не найден";
        return emptyPath;
    }

    QVector<QString> path;
    QString current = end;
    while (current != start) {
        path.prepend(current);
        if (!prev.contains(current)) {
            return emptyPath;
        }
        current = prev[current];
    }
    path.prepend(start);

    return path;
}
