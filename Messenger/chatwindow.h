#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QtWidgets>
#include <QUdpSocket>
#include <QHostAddress>
#include <QHostInfo>
#include <settings.h>


struct Message {
    ushort name_len;
    ushort msg_len;
    //char name[name_len];
    //char msg[msg_len];
};

class ChatWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChatWindow(QWidget *parent = 0);

    QList<QHostAddress> HostAddresses;
    //QMap<QHostAddress, short> clients;

    QUdpSocket *Socket;

    QTimer *timer;
    QTextEdit *Chat;
    QPushButton *Send;
    QListWidget *Room;
    QLineEdit *Msg;
    QSettings Setting;
    char *nick;
    int lenNick;
    int PORT, keepAliv;

signals:

public slots:
    void keyPressEvent(QKeyEvent *k);
    void setNick(const char* newNick);
    void clientCheck();
    void openSetting();
    void setChange();
    void send();
    void recieve();
    void keepAlive();

};

#endif // CHATWINDOW_H
