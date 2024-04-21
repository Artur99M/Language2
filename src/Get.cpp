#include "../include/Get.h"
#include "../DEBUG/def.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "../include/tree.h"
#include "../include/TREE_EXP.h"
#include "../include/Diff.h"
#include "../include/SimpleTreeExp.h"

#define require(c) (**s == c) ? *s++ : SyntaxError();
#define notation 10

void SkipSpace (char** s);
Node* Syntax_Error (char** s, const char func[5]);
bool ismathfunc (char** s, const char mathfunc[10]);

#define SyntaxError() Syntax_Error(s, __func__)

Node* GetG (char* str)
{
    PRINT_DEBUG ("\n");
    char* s = str;
    Node* val = nullptr;
    if (val = GetO(&s))
    {
        PRINT_DEBUG ("s = \"%s\"\n", s);
        SkipSpace(&s);
        val->left = GetE(&s);
        SkipSpace(&s);
        PRINT_DEBUG ("*s = %c\n", *s);
    }
    else
    {
        PRINT_DEBUG ("s = \"%s\"\n", s);
        SkipSpace(&s);
        val = GetE(&s);
        SkipSpace(&s);
        PRINT_DEBUG ("*s = %c\n", *s);
    }

    if (*s == '$') s++;
    else return Syntax_Error(&s, __func__);
    return val;
}

Node* GetE (char** s)
{
    PRINT_DEBUG ("\n");
    SkipSpace(s);
    Node* val = GetT (s);
    SkipSpace(s);
    PRINT_DEBUG ("**s = %c\n", **s);

    while (**s == '+' || **s == '-')
    {
        char op = **s;
        (*s)++;
        SkipSpace(s);
        Node* val2 = GetT(s);
        SkipSpace(s);
        if (op == '+') val = CreateNodeOperation (ADD, val, val2);
        else           val = CreateNodeOperation (SUB, val, val2);
    }

    return val;
}

Node* GetT(char** s)
{
    PRINT_DEBUG ("\n");
    SkipSpace(s);
    Node* val = GetL (s);
    SkipSpace(s);
    PRINT_DEBUG ("**s = %c\n", **s);

    while (**s == '*' || **s == '/')
    {
        char op = **s;
        (*s)++;
        SkipSpace(s);
        Node* val2 = GetL(s);
        SkipSpace(s);
        if (op == '*') val = CreateNodeOperation (MUL, val, val2);
        else           val = CreateNodeOperation (DIV, val, val2);
    }

    return val;
}

Node* GetP(char** s)
{
    PRINT_DEBUG ("\n");
    SkipSpace(s);
    PRINT_DEBUG ("**s = %c\n", **s);
    Node* val = 0;
    int sign = 1;
    if (**s == '-')
    {
        (*s)++;
        sign = -1;
    }
    SkipSpace(s);
    if (**s == '(')
    {
        (*s)++;
        val = GetE(s);
        SkipSpace(s);
        PRINT_DEBUG ("**s = %c\n", **s);
        if (**s == ')') (*s)++;
        else return SyntaxError();
    }
    else
    {
        val = GetN(s);
        SkipSpace(s);
        PRINT_DEBUG ("val = %p\n", val);
    }

    if (sign > 0)
        return val;
    else return CreateNodeOperation (SUB, nullptr, val);
}

Node* GetN(char** s)
{
    PRINT_DEBUG ("start\n");
    Node* V = GetV (s);
    if (V != nullptr)
        return V;
    double val = 0;
    SkipSpace(s);
    const char* olds = *s;
    while ('0' <= **s && **s <= '9')
    {
        PRINT_DEBUG ("**s = %c\n", **s);
        val = val * notation + (**s - '0');
        (*s)++;
    }
    PRINT_DEBUG ("val = %lf\n", val);
    if (olds == *s)
        return SyntaxError();
    if (**s == '.' || **s == ',')
    {
        PRINT_DEBUG ("**s = %c\n", **s);
        (*s)++;
        olds = *s;
        int exp10 = 10;
        while ('0' <= **s && **s <= '9')
        {
            PRINT_DEBUG ("**s = %c\n", **s);
            double x = 0;
            x += (**s - '0');
            x /= exp10;
            val += x;
            PRINT_DEBUG ("val = %lf\n", val);
            exp10 *= 10;
            (*s)++;
        }
        if (olds == *s) return SyntaxError();

    }
    PRINT_DEBUG ("val = %lf\n", val);


    return CNN (val);
}

void SkipSpace (char** s)
{
    while (**s == ' ' || **s == '\t')
        (*s)++;
}

Node* Syntax_Error (char** s, const char func[5])
{
    fprintf(stderr, "ERROR: \'%c\' in text in func \'%s\'\n", **s, func);
    return nullptr;
}

Node* GetL (char** s)
{
    PRINT_DEBUG ("start\n");
    SkipSpace(s);
    Node* val = GetM (s);
    SkipSpace(s);
    PRINT_DEBUG ("**s = %c\n", **s);

    if (**s == '^')
    {
        char op = **s;
        (*s)++;
        SkipSpace(s);
        Node* val2 = GetM(s);
        SkipSpace(s);
        val = CreateNodeOperation (EXP, val, val2);
    }

    if (ismathfunc (s, "log"))
    {
        SkipSpace(s);
        Node* val2 = GetM (s);
        val = CreateNodeOperation (LOG, val, val2);
    }

    return val;
}

bool ismathfunc (char** s, const char mathfunc[10])
{
    PRINT_DEBUG ("mathfunc = %s\n", mathfunc);
    char* olds = *s;
    for (int i = 0; i < strlen (mathfunc); i++)
    {
        PRINT_DEBUG ("**s = %c\n", **s);
        if (**s == mathfunc[i])
            (*s)++;
        else {*s = olds; return false; }
    }

    return true;
}

Node* GetM (char** s)
{
    PRINT_DEBUG ("start\n");
    // double val = 0; // GetP (s);
    SkipSpace(s);
    PRINT_DEBUG ("**s = %c\n", **s);
    char* olds = *s;
    for (int i = 0; i < nfuncs; i++)
    {
        if (ismathfunc (s, math_funcs[i].name))
        {
            SkipSpace(s);
            if (**s != '(') return SyntaxError();
            else // (**s == '(')
            {
                (*s)++;
                Node* val = GetE(s);
                SkipSpace(s);
                PRINT_DEBUG ("**s = %c\n", **s);
                if (**s == ')') (*s)++;
                else return SyntaxError();
                return CreateNodeOperation (math_funcs[i].operation, val, nullptr);
            }
        }
        else *s = olds;

    }

    return GetP(s);
}

Node* GetV(char** s)
{
    SkipSpace (s);
    if (isalpha (**s))
    {
        Node* val = CreateNodeVariable (**s, nullptr, nullptr);
        (*s)++;
        return val;
    }
    return nullptr;
}

Node* GetI (char** s)
{
    char* olds = *s;

    PRINT_DEBUG ("start\n");
    Node* val = nullptr;
    if (val = GetV (s))
    {
        PRINT_DEBUG ("I see variable, **s = %c\n", **s);
        SkipSpace (s);
        if (**s == '=')
        {
            PRINT_DEBUG ("I see \'=\', **s = %c\n", **s);
            (*s)++;
            return CreateNodeOperator (EQUAL, nullptr, val);
        }
        else
        {
            TreeDtor (val);
            val = nullptr;
        }
    }

    *s = olds;
    return nullptr;
}

Node* GetO (char** s)
{
    PRINT_DEBUG ("start\n");
    char* olds = *s;
    Node* val = nullptr;
    if (val = GetI(s))
        return val;

    return nullptr;
}
