#include "errorprocessor.h"


void QErrorProcessor::printError(ErrorProcessor::Error code)
{
    switch (code) {
    case NotMemory:
        msg->setText("Not mem!");
        break;
    case NotCorrectData:
        msg->setText("Not correct data!");
    default:
        msg->setText("Unknow error");
        break;
    }
    msg->show();
}

QErrorProcessor::QErrorProcessor()
{
    msg = new QMessageBox;
}
