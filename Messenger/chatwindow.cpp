#include "chatwindow.h"

ChatWindow::ChatWindow(QWidget *parent) :
    QMainWindow(parent), nick(0), Setting(QApplication::applicationDirPath() + "/" + QApplication::applicationName() + ".ini", QSettings::IniFormat)
{
    QTimer *forCheck = new QTimer;
    connect(forCheck, SIGNAL(timeout()), SLOT(clientCheck()));
    forCheck->start(2000);
    Setting.setIniCodec("UTF-8");
    PORT = Setting.value("port").toInt();
    keepAliv = Setting.value("setkeepalive").toInt();
    setNick(Setting.value("nick").toByteArray().data());

    setWindowIcon(QIcon(QApplication::applicationDirPath() + "/icon.png"));
    connect(menuBar()->addAction("Settings"), SIGNAL(triggered()), SLOT(openSetting()));

    timer = new QTimer(this);
    HostAddresses = QHostInfo::fromName(QHostInfo::localHostName()).addresses();

    Socket = new QUdpSocket(this);
    Socket->bind(QHostAddress::Any, PORT);

    QHBoxLayout *layout = new QHBoxLayout;
    QVBoxLayout *temp = new QVBoxLayout;

    Chat = new QTextEdit;
        Chat->setReadOnly(1);

    Send = new QPushButton("Send");
    Room = new QListWidget;
    Msg = new QLineEdit;

    temp->addWidget(Chat);
    temp->addWidget(Msg);
    temp->addWidget(Send);

    layout->addLayout(temp);
    layout->addWidget(Room);
    connect(Send, &QPushButton::clicked, this, &ChatWindow::send);
    connect(timer, &QTimer::timeout, this, &ChatWindow::keepAlive);
    connect(Socket, &QUdpSocket::readyRead, this, &ChatWindow::recieve);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    setCentralWidget(widget);
    timer->start(keepAliv);
}

void ChatWindow::keyPressEvent(QKeyEvent *k)
{
    int key_p = k->key();
    if(key_p == Qt::Key_Return ||
       key_p == Qt::Key_Enter) send();
}

void ChatWindow::setNick(const char *newNick)
{
    lenNick = strlen(newNick);
    nick = (char*)memcpy(realloc(nick, lenNick), newNick, lenNick);
}

void ChatWindow::clientCheck()
{

}

void ChatWindow::openSetting()
{
    Settings *set = new Settings(&Setting, this);
    connect(set, SIGNAL(settingChange()), SLOT(setChange()));
    set->show();
}

void ChatWindow::setChange()
{
    Socket->abort();
    PORT = Setting.value("port").toInt();
    keepAliv = Setting.value("setkeepalive").toInt();
    if(!Setting.value("keepAvile").toBool()) timer->stop();
    else timer->start(keepAliv);
    Socket->bind(QHostAddress::Any, PORT);
    setNick(Setting.value("nick").toByteArray().data());
}

void ChatWindow::send()
{
    char *m = Msg->text().toUtf8().data();
    int lenMsg  = strlen(m),
        sizeMsg = sizeof(Message) + lenMsg + lenNick;
    Message *data = (Message*)malloc(sizeMsg);
    data->name_len = lenNick;
    data->msg_len  = lenMsg;

    memcpy((char*)(data + 1), nick, lenNick);
    memcpy((char*)(data + 1) + lenNick, m, lenMsg);

    Socket->writeDatagram((char*)data, sizeMsg, QHostAddress::Broadcast, PORT);

    free(data); Msg->clear();
}

void ChatWindow::recieve()
{
    Message *in = 0; QHostAddress adr;
    while(Socket->hasPendingDatagrams()){
        qint64 sizeMsg = Socket->pendingDatagramSize();
        in = (Message*)realloc(in, sizeMsg);
        Socket->readDatagram((char*)in, sizeMsg, &adr);

        if(!HostAddresses.contains(adr)){
            HostAddresses.append(adr);
            Room->addItem(QByteArray((char*)(in + 1), in->name_len));
            Room->setToolTip(adr.toString());
        }
        if(!in->msg_len) return;

        Chat->setTextColor(Qt::red);
        Chat->append(QString(QByteArray((char*)(in + 1), in->name_len)) + ":");

        Chat->setTextColor(Qt::black);
        Chat->append(QByteArray((char*)in + sizeof(Message) + in->name_len, in->msg_len));
    }
    free(in);
}

void ChatWindow::keepAlive()
{
    int sizeMsg = sizeof(Message) + lenNick;
    Message *data = (Message*)malloc(sizeMsg);
    data->name_len = lenNick;
    data->msg_len  = 0;
    memcpy((char*)(data + 1), nick, lenNick);
    Socket->writeDatagram((char*)data, sizeMsg, QHostAddress::Broadcast, PORT);
    free(data);
}
