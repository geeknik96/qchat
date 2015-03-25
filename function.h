#ifndef FUNCTION_H
#define FUNCTION_H

#include <vector>

using namespace std;

struct member {
    int type;
    float val;
};

class Function
{
    vector<member> data;

public:
    Function(const char *);
    ~Function();
};

#endif // FUNCTION_H
