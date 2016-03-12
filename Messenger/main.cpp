#include <QApplication>
#include "chatwindow.h"

int main(int argv, char **argc)
{
    QApplication app(argv, argc);

    ChatWindow win;
    win.show();

    return app.exec();

}
