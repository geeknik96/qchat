#ifndef SETTINGS_H
#define SETTINGS_H

//#include <QMainWindow>
#include <QtWidgets>

class Settings : public QMainWindow
{
    Q_OBJECT
public:
    explicit Settings(QSettings *s, QWidget *parent = 0);
    QLineEdit *nick;
    QSpinBox *port, *setKeepAvile;
    QCheckBox *keepAvile;
    QSettings *set;

signals:
    void settingChange();

public slots:
    void writeSettings();
    void writeAndClose();

};

#endif // SETTINGS_H
