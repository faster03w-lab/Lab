#include "graphwidget.h"
#include <QDebug>
#include <cmath>

GraphWidget::GraphWidget(QWidget *parent) : QWidget(parent), graph(nullptr) {
    setMinimumSize(600, 400);
    setStyleSheet("background-color: white;");
}

void GraphWidget::setGraph(Graph *g) {
    graph = g;
    update();
}

void GraphWidget::setMapImage(const QString& fileName) {
    mapImage = QImage(fileName);
    if (mapImage.isNull()) {
        qWarning() << "Не удалось загрузить изображение карты:" << fileName;
    }
    update();
}

void GraphWidget::setPath(const QVector<QString>& path) {
    currentPath = path;
    update();
}

void GraphWidget::clearPath() {
    currentPath.clear();
    update();
}

QColor GraphWidget::getColorByK(double k) const {
    if (k <= 1.0)  return QColor(0, 220, 0);     // зелёный
    if (k <= 1.5)  return QColor(255, 140, 0);   // оранжевый
    if (k <= 2.5)  return QColor(230, 0, 0);     // красный
    return QColor(148, 0, 211);                  // фиолетовый
}

QString GraphWidget::getVertexAt(double x, double y) const {
    if (!graph) return QString();

    for (const Vertex& v : graph->getVertices()) {
        double dx = x - v.x;
        double dy = y - v.y;
        if (dx * dx + dy * dy <= VERTEX_RADIUS * VERTEX_RADIUS) {
            return v.name;
        }
    }
    return QString();
}

void GraphWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (!mapImage.isNull()) {
        painter.drawImage(0, 0, mapImage.scaled(size(), Qt::KeepAspectRatio));
    }

    if (!graph) return;


    QVector<QPair<QString, QString>> edges = graph->getAllEdges();
    for (int eIdx = 0; eIdx < edges.size(); eIdx++) {
        const QPair<QString, QString>& edge = edges[eIdx];

        Vertex v1, v2;
        bool found1 = false, found2 = false;

        QVector<Vertex> verts = graph->getVertices();
        for (int vIdx = 0; vIdx < verts.size(); vIdx++) {
            const Vertex& v = verts[vIdx];
            if (v.name == edge.first)  { v1 = v; found1 = true; }
            if (v.name == edge.second) { v2 = v; found2 = true; }
        }

        if (!found1 || !found2) continue;

        double k = graph->getEdgeK(edge.first, edge.second);
        double edgeLength = graph->getEdgeLength(edge.first, edge.second);

        bool inPath = false;
        for (int i = 0; i < currentPath.size() - 1; i++) {
            if ((currentPath[i] == edge.first && currentPath[i+1] == edge.second) ||
                (currentPath[i] == edge.second && currentPath[i+1] == edge.first)) {
                inPath = true;
                break;
            }
        }

        if (inPath) {

            QPen outlinePen(QColor(0, 0, 0), 9);
            outlinePen.setCapStyle(Qt::RoundCap);
            painter.setPen(outlinePen);
            painter.drawLine(QPointF(v1.x, v1.y), QPointF(v2.x, v2.y));

            QPen whitePen(QColor(255, 255, 255), 7);
            whitePen.setCapStyle(Qt::RoundCap);
            painter.setPen(whitePen);
            painter.drawLine(QPointF(v1.x, v1.y), QPointF(v2.x, v2.y));

            QPen pathPen(QColor(255, 215, 0), 5);
            pathPen.setCapStyle(Qt::RoundCap);
            painter.setPen(pathPen);
            painter.drawLine(QPointF(v1.x, v1.y), QPointF(v2.x, v2.y));
        } else {

            QPen outlinePen(QColor(0, 0, 0, 100), 6);
            painter.setPen(outlinePen);
            painter.drawLine(QPointF(v1.x, v1.y), QPointF(v2.x, v2.y));

            QPen pen;
            pen.setColor(getColorByK(k));
            pen.setWidth(4);
            painter.setPen(pen);
            painter.drawLine(QPointF(v1.x, v1.y), QPointF(v2.x, v2.y));
        }


        double midX = (v1.x + v2.x) / 2.0;
        double midY = (v1.y + v2.y) / 2.0;

        double dx = v2.x - v1.x;
        double dy = v2.y - v1.y;
        double segLength = std::sqrt(dx * dx + dy * dy);

        double textX = midX;
        double textY = midY;

        if (segLength > 0) {
            double offset = 16.0;
            double nx = -dy;
            double ny = dx;

            textX += (nx / segLength) * offset;
            textY += (ny / segLength) * offset;
        }

        QString label = QString("%1(%2)").arg(edgeLength).arg(edgeLength * k, 0, 'f', 1);

        QRectF textRect(textX - 25, textY - 10, 50, 20);

        painter.setPen(QColor(255, 255, 255));
        painter.setFont(QFont("Arial", 9, QFont::Bold));
        painter.drawText(textRect, Qt::AlignCenter, label);

        painter.setPen(QColor(0, 0, 0));
        painter.drawText(textRect, Qt::AlignCenter, label);
    }

    QVector<Vertex> verts = graph->getVertices();
    for (int i = 0; i < verts.size(); i++) {
        const Vertex& v = verts[i];
        bool inPath = currentPath.contains(v.name);

        QRectF rect(v.x - VERTEX_RADIUS, v.y - VERTEX_RADIUS,
                    VERTEX_RADIUS * 2.0, VERTEX_RADIUS * 2.0);

        if (inPath) {
            painter.setBrush(QColor(255, 215, 0));
            painter.setPen(QPen(QColor(0, 0, 0), 3));
        } else {
            painter.setBrush(QColor(230, 230, 230));
            painter.setPen(QPen(QColor(50, 50, 50), 2));
        }
        painter.drawEllipse(rect);

        painter.setPen(QColor(0, 0, 0));
        painter.setFont(QFont("Arial", 11, QFont::Bold));
        painter.drawText(rect, Qt::AlignCenter, v.name);
    }
}

void GraphWidget::mouseDoubleClickEvent(QMouseEvent *event) {
    double clickX = event->x();
    double clickY = event->y();

    QString name = getVertexAt(clickX, clickY);
    if (!name.isEmpty()) {
        qDebug() << "Двойной клик на вершине:" << name
                 << "координаты:" << clickX << clickY;
        emit vertexDoubleClicked(name);
        emit vertexSelected(name);
    } else {
        qDebug() << "Клик в пустом месте:" << clickX << clickY;
    }
}
