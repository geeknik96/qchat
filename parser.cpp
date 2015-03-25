#include "parser.h"
#include <QStack>
#include <qdebug.h>
#include <cstdio>
#include <iostream>

#define DEBUG

float add(float a, float b) {return a + b;}
float sub(float a, float b) {return a - b;}
float mul(float a, float b) {return a * b;}
float div(float a, float b) {return a / b;}

float (* const Parser::opB[])(float, float) = {add, sub, mul, div, powf};
float (* const Parser::opU[])(float) = {sqrtf, fabsf, expf, logf, cosf, sinf, tanf, tanf};
char *const Parser::namesFunc[]= {"+", "-", "*", "/", "^", "sqrt", "abs", "exp", "ln", "cos", "sin", "tan", "tg"};
char *const Parser::namesTypesData[] = { "const", "func|oper", "variable" };

bool isNumber(uchar ch)
{
    return (uchar)('9' - '0') >= (uchar)('9' - ch);
}

bool isLetter(uchar ch)
{
    ch |= 0x20;
    return (uchar)('z' - 'a') >= (uchar)('z' - ch);
}

int Parser::isFunc(const char * str)
{
    for(int i = Sqr; i < sizeof(namesFunc)/sizeof(*namesFunc); ++i)
        if (!strcmp(str, namesFunc[i])) return i;
    return -1;
}

int Parser::isOperator(const char * str)
{
    for(int i = 0; i < Sqr; ++i)
        if (!strcmp(str, namesFunc[i])) return i;
    return -1;
}

Parser::Parser() {

}

Parser::Parser(QString &eq) : data(eq.size()/2)
{

    char *parse = eq.toUtf8().data();
    int len = eq.size();
    char buff[25] = {};
    member mem;
    arg var;
    memset(&mem, 0, sizeof(mem));

    for(int i = 0; i < len; ++i)
    {
        if(parse[i] == ' ') continue;
        else if(isNumber(parse[i])) {
            int start = i;
            do {  i++; }
            while(i < len && (isNumber(parse[i]) || parse[i] == '.'));
            memcpy(buff, parse + start, i - start);
            mem.type = Const;
            mem.val = (float)atof(buff);
            memset(buff, 0, sizeof(buff));
            data.insert(data.end(), 1, &mem);
        }
        else if(isLetter(parse[i])) {
            int start = i, r;
            do {  i++; }
            while(i < len && isLetter(parse[i]));
            memcpy(buff, parse + start, i - start);
            if((r = isFunc(buff)) != -1) {
                mem.type = FuncOrOper;
                mem.val = 0.0f;
                st.push(mem);
            }
            else {
                int len_name = i - start;
                if(len_name > 3) len_name = 3;
                memcpy(var.name, parse + start, len_name);
                var.val = NAN;
                vars.insert(vars.end(), 1, &var);
            }
            memset(buff, 0, sizeof(buff));
            data.insert(data.end(), 1, &mem);

            if ((check = isFunc(mem)) > Pwr)
                  oper.push(check);
            //            //else is variable
        }
    }

//    string parse(eq.toLower().toStdString());
//    int len = eq.size();
//    string temp("");  QStack<int> oper;
//    //prepare to pain! train yard
//    int check;
//    string::iterator start;
//    member buff;
//    for(string::iterator it = parse.begin(); it != parse.end(); it++)
//    {
//        //temp = ""; добавить
//        if(*it == ' ') continue;
//        else if('0' <= *it && *it <= '9')
//        {
//            start = it;
//            do {
//                if(it + 1 == parse.end()) break;
//                else it++;
//            } while (('0' <= *it && *it <= '9' || *it == '.'));
//            temp.append(start, it);
//            buff.type = Const;
//            buff.val = (float)atof(temp.c_str());
//            data.insert(data.end(), buff);
//        }
//        else if('a' <= *it && *it >= 'z')
//        {
//            start = it;
//            do {
//                if(it + 1 == parse.end()) break;
//                else it++;
//            } while (('0' <= *it && *it <= '9' || *it == '.'));
//            temp.append(start, it);
//            buff.type = Const;
//            buff.val = (float)atof(temp.c_str());
//            data.insert(data.end(), buff);

//            if ((check = isFunc(temp)) > Pwr)
//                oper.push(check);
//            //else is variable
//        }
//        else if((check = isOperator(string(it, it + 1))) >= Add)
//        {
//            while(!oper.isEmpty() && oper.top() > check && oper.top() < OpenBR)
//                data.append({oper.pop(), 0.0});
//            oper.push(check);
//        }
//        else if (eq[i] == '(') oper.push(OpenBR);
//        else if (eq[i] == ')') {
//            while(!oper.isEmpty() && oper.top() != OpenBR)
//                data.append({oper.pop(), 0.0});
//            if(!oper.isEmpty()) oper.pop();
//            //else: error
//            if(!oper.isEmpty() && oper.top() > Pwr && oper.top() < OpenBR)
//                data.append({oper.pop(), 0.0});
//        }
//    }
//    while(!oper.isEmpty())
//        data.append({oper.pop(), 0.0});
//#ifdef DEBUG
//    QDebug debug(qDebug().nospace() << "Parse str: ");
//    for (int i = 0; i < data.size(); ++i) {
//        if (data.at(i).type < Const)
//            debug << namesFunc[data.at(i).type] << ' ';
//        else
//            debug << data.at(i).val << ' ';
//    }
//#endif
}

float Parser::calculate()
{
//    QStack<member> calc;
//    for(QList<member>::iterator i = data.begin(); i < data.end(); ++i)
//    {
//        if(i->type <= Pwr) {
//            float num = calc.pop().val;
//            calc.top().val = opB[i->type](calc.top().val, num);
//        }
//        else if(i->type <= Tan)
//            calc.top().val = opU[i->type - Sqr](calc.top().val);
//        else calc.push(*i);
//#ifdef DEBUG
//        QDebug debug(qDebug().nospace());
//        for (int i = 0; i < calc.size(); ++i)
//        {
//            if (calc.at(i).type < Const)
//                debug << namesFunc[calc.at(i).type] << ' ';
//            else
//                debug << calc.at(i).val << ' ';
//        }
//#endif
//    }
//    return calc.pop().val;
}
