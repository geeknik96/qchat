#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graphwidget.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    GraphWidget *m_GraphWidget;
    QLineEdit *X,*Y,*Z;

signals:


public slots:



};

#endif // MAINWINDOW_H
