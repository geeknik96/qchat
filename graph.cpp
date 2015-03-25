#include "graph.h"
#include <QDebug>

void Graph::setColor(float r, float b, float g)
{
    color[0] = r;
    color[1] = b;
    color[2] = g;
}

void Graph::setDrawMode(Graph::DrawMode mode)
{
    drawMode = mode;
}

Graph::Graph()
{
    drawMode = GL_LINE_STRIP;
    color[0] = color[1] = color[2] = 1.0f;
}


void Graph3D::drawGraph()
{
    glColor3fv(color);
    glVertexPointer(3, GL_FLOAT, 0, g);
    uint size = (vsize - 1)*(usize - 1);
    indeces[0] = 0; indeces[1] = 1;
    indeces[2] = vsize; indeces[3] = vsize + 1;
    if(drawMode != GL_POINTS) {
        for(uint i = 0; i < size; ++i) {
            glDrawElements(drawMode, 4, GL_UNSIGNED_INT, indeces);
            indeces[0] = indeces[1]++;
            indeces[2] = indeces[3]++;
        }
    }
    else glDrawArrays(drawMode, 0, usize*vsize);
}



Graph3D::Graph3D(const QString &XoUV, const QString &YoUV, const QString &ZoUV,
                 const param &pu, const param &pv) : u(pu), v(pv)
{
    if((usize = (u.to - u.from) / u.step) > MAXMEM)
        u.step = (u.to - u.from) / (usize = MAXMEM);

    if((vsize = (v.to - v.from) / v.step) > MAXMEM)
        v.step = (v.to - v.from) / (vsize = MAXMEM);

    qDebug() << "size = " << usize << vsize;

    uint size = usize*vsize;
    g = (coord*)malloc(sizeof(coord)*size);

    float cur_u = u.from;
    float cur_v = v.from;
    for(uint i = vsize, j = 0; i <= size; i += vsize) {
        for(;j < i; j++, cur_v += v.step) {
            g[j].x = cur_u*cos(cur_v);
            g[j].y = cur_u*sin(cur_v);
            g[j].z = cur_u;
        }
        cur_v  = v.from;
        cur_u += u.step;
    }
}

Graph3D::Graph3D(const QString &ZoXY, const param &px, const param &py) :
    u(py), v(px)
{
    if((usize = (u.to - u.from) / u.step) > MAXMEM)
        u.step = (u.to - u.from) / (usize = MAXMEM);

    if((vsize = (v.to - v.from) / v.step) > MAXMEM)
        v.step = (v.to - v.from) / (vsize = MAXMEM);

    uint size = usize*vsize;
    g = (coord*)malloc(sizeof(coord)*size);

    float cur_u = u.from;
    float cur_v = v.from;
    for(uint i = vsize, j = 0; i <= size; i += vsize) {
        for(;j < i; j++, cur_v += v.step) {
            g[j].x = 10*cur_v;
            g[j].y = 10*cur_u;
            g[j].z = cur_u*cur_u + cur_v*cur_v;//parser
        }
        cur_v  = v.from;
        cur_u += u.step;
    }
}


Graph3D::~Graph3D() { free(g); }



