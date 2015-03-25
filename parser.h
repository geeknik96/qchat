#ifndef PARSER_H
#define PARSER_H

#include <QtCore>
#include <cmath>
#include <stack>

using namespace std;

struct member {
    short type;
    float val;
};

struct arg {
    char name[4];
    float val;
};

class Parser
{
    enum Operators { Add, Sub, Mul, Div, Pwr};
    enum Functions { Sqr = Pwr + 1, Abs, Exp, Ln, Cos, Sin, Tg, Tan };
    enum SecialSym { OpenBR = Tan + 1, CloseBR };
    enum TypesData { Const = 100, FuncOrOper, Variable };

    static float (* const opB[])(float, float);
    static float (* const opU[])(float);

    static char *const namesFunc[];
    static char *const namesTypesData[];

    static int isFunc(const char* );
    static int isOperator(const char*);

    vector<member> data;
    vector<arg> vars;
    stack<int> st;

public:
    Parser();
    Parser(QString &eq);
    float calculate();
};


#endif // PARSER_H
