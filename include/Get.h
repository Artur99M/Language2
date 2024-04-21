#ifndef GET_H
#define GET_H
#include <math.h>
#include "TREE_EXP.h"
#include "tree.h"

Node* GetG(char*);
Node* GetN(char**);
Node* GetE(char**);
Node* GetT(char**);
Node* GetP(char**);
Node* GetL(char**);
Node* GetM(char**);
Node* GetV(char**);
Node* GetO(char**);
Node* GetI(char**);


struct MATH_FUNC
{
    char name[10];
    double (*func)(double);
    OP operation;

};

const struct MATH_FUNC math_funcs[] =
{
    // { "ln",     log, LN }, //проблема проверки значений, к тому же я не выделил отдльный ENUM
    { "sin",    sin, SIN },
    { "cos",    cos, COS },
    { "tg",     tan, TG },
    // { "ctg", ctan }, нет такой функции
    { "arcsin", asin, ARCSIN }, //проблема проверки значений
    // { "arctg",  atan, ARCTG }
};
const int nfuncs = sizeof (math_funcs) / sizeof (MATH_FUNC);
#endif
