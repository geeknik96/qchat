#ifndef GRAPH_H
#define GRAPH_H
#define MAXMEM 512 // 0.5 MByte

#include "parser.h"
#include <QGLWidget>

struct param {
    float step;
    float from;
    float to;
};

struct coord {
    float x;
    float y;
    float z;
};

class Graph
{
protected:
    float color[3]; // rgb
    int drawMode;
public:
    enum DrawMode {POINTS = GL_POINTS, LINES = GL_LINE_STRIP, TRIANGLS = GL_TRIANGLE_STRIP};
    virtual void drawGraph() = 0;
    void setColor(float r, float b, float g);
    void setDrawMode(DrawMode mode);
    Graph();
};

class Graph3D : public Graph
{
    /*if x == NULL || y == NULL - graph parametric else function*/
    coord *g;
   // Parser *X, *Y, *Z;
    param u, v;
    uint usize, vsize;
    uint indeces[4];

public:
    void drawGraph();
    Graph3D(const QString &XoUV, const QString &YoUV, const QString &ZoUV, const param &pu, const param &pv); // pars in constuctor
    Graph3D(const QString &ZoXY, const param &px, const param &py);
    ~Graph3D();
};

#endif // GRAPH_H
