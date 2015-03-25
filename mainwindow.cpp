#include "mainwindow.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    resize(500,700);
    QGroupBox *eq = new QGroupBox("Equation", this);

    QGridLayout *eq_layout = new QGridLayout(this);
    eq_layout->addWidget(new QLabel("X(u, v):", this), 0, 0);
    eq_layout->addWidget(X = new QLineEdit(this), 0, 1);
    eq_layout->addWidget(new QLabel("Y(u, v):"), 1, 0);
    eq_layout->addWidget(Y = new QLineEdit(this), 1, 1);
    eq_layout->addWidget(new QLabel("Z(u, v)", this), 2, 0);
    eq_layout->addWidget(Z = new QLineEdit(this), 2, 1);

    eq->setLayout(eq_layout);
    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addWidget(m_GraphWidget = new GraphWidget, 4);
    layout->addWidget(eq);
    layout->addWidget(new QPushButton("Fire!", this), 100);

    QWidget *w = new QWidget(this);
    w->setLayout(layout);
    w->setFocus();
    setCentralWidget(w);
}

MainWindow::~MainWindow()
{
    delete m_GraphWidget;
}
