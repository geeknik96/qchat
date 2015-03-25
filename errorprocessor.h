#ifndef ERRORPROCESSOR_H
#define ERRORPROCESSOR_H

#include <QMessageBox>

class ErrorProcessor
{
public:
    enum Error { NotMemory, NotCorrectData};
    virtual void printError(Error) = 0;
    ErrorProcessor();
    ~ErrorProcessor();
};

class QErrorProcessor : public ErrorProcessor
{
    QMessageBox *msg;
public:
    void printError(Error);
    QErrorProcessor();
    ~QErrorProcessor();
}

#endif // ERRORPROCESSOR_H
