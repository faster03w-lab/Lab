#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include "graph.h"

class GraphWidget : public QWidget {
    Q_OBJECT

public:
    explicit GraphWidget(QWidget *parent = nullptr);

    void setGraph(Graph *graph);
    void setMapImage(const QString& fileName);
    void setPath(const QVector<QString>& path);
    void clearPath();

signals:
    void vertexDoubleClicked(const QString& name);
    void vertexSelected(const QString& name);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    Graph *graph;
    QImage mapImage;
    QVector<QString> currentPath;

    static const int VERTEX_RADIUS = 14;

    QColor getColorByK(double k) const;
    QString getVertexAt(double x, double y) const;
};

#endif // GRAPHWIDGET_H
