#ifndef GraphWidget_H
#define GraphWidget_H

#include <QtOpenGL>
#include <QGLWidget>
#include "graph.h"


class GraphWidget : public QGLWidget
{
    Q_OBJECT
    float m_size;
    float m_angle;
    float axisCoord[3*6];
    float axisColor[3*6];
    QVector<Graph*>::iterator it;
public:
    explicit GraphWidget();
    ~GraphWidget();
    QVector<Graph*> graphs;

signals:

public slots:
    void initializeGL();
    void paintGL();
    void resizeGL(int, int);
};

#endif // GraphWidget_H
