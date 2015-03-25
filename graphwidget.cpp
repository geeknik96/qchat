#include "graphwidget.h"

GraphWidget::GraphWidget() :
    m_angle(0.7f), graphs(),
    axisColor({ 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f})
{
    memset(axisCoord, 0, sizeof(axisCoord));
    QTimer *t = new QTimer(this);
    connect(t, SIGNAL(timeout()), SLOT(updateGL()));
    t->start(20);
}

GraphWidget::~GraphWidget()
{
    for(it = graphs.begin(); it != graphs.end(); it++)
        delete *it;
}

void GraphWidget::initializeGL()
{
    qglClearColor(Qt::black);
    glMatrixMode(GL_PROJECTION);
    glEnableClientState(GL_VERTEX_ARRAY);
}

void GraphWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glRotatef(m_angle,1,0,1);

    glColor3fv(axisColor);
    renderText(m_size,0,0, "X",QFont("Helvetica",10,10));
    glColor3fv(axisColor + 6);
    renderText(0,m_size,0, "Y",QFont("Helvetica",10,10));
    glColor3fv(axisColor + 12);
    renderText(0,0, m_size, "Z",QFont("Helvetica",10,10));

    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, axisColor);
    glVertexPointer(3, GL_FLOAT, 0, axisCoord);
    glDrawArrays(GL_LINES, 0, 6);
    glDisableClientState(GL_COLOR_ARRAY);

    for(it = graphs.begin(); it != graphs.end(); it++)
        (*it)->drawGraph();

    glFlush();
}

void GraphWidget::resizeGL(int w, int h)
{
    glLoadIdentity();
    glViewport(0, 0, w, h);
    m_size = qMin(w / 2, h / 2);
    axisCoord[0] = axisCoord[7]  = axisCoord[14] =  m_size;
    axisCoord[3] = axisCoord[10] = axisCoord[17] = -m_size;
    glOrtho(-m_size, m_size, -m_size, m_size, -m_size, m_size);
}
