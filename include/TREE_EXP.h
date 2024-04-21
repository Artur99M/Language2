#ifndef TREE_EXP_H
#define TREE_EXP_H

enum OPERATORS
{
    EQUAL = 1,
    IF = 2,
    ELSE = 3,
    ELIF = 4,
    RETURN = 5
};

enum TYPE
{
    OPERATION   = 1,
    NUMBER      = 2,
    VARIABLE    = 3,
    OPERATOR    = 4
};

enum OP
{
    ADD    = 1,
    SUB    = 2,
    MUL    = 3,
    DIV    = 4,
    SIN    = 5,
    COS    = 6,
    TG     = 7,
    CTG    = 8,
    EXP    = 9,
    LOG    = 10,
    ARCSIN = 11,
    ARCCOS = 12,
    ARCTG  = 13,
    ARCCTG = 14
};

union VALUE
{
    double number;
    char variable;
    OPERATORS loperator;
    OP operation;
};

typedef struct operation
{
    char name[7];
    OP value;
} operation;

const int num_operation = 15;
const operation OPERATIONS[] =
    {
    {"+", ADD},
    {"-", SUB},
    {"*", MUL},
    {"/", DIV},
    {"sin", SIN},
    {"cos", COS},
    {"tg", TG},
    {"ctg", CTG},
    {"^", EXP},
    {"log", LOG},
    {"arcsin", ARCSIN},
    {"arccos", ARCCOS},
    {"arctg", ARCTG},
    {"arcctg", ARCCTG}
};

typedef struct str_operators
{
    OPERATORS value;
    char name[7];
} str_operators;

const str_operators STR_OPERATORS[] =
{
    {EQUAL, "="},
    {IF, "if"},
    {ELSE, "else"},
    {ELIF, "elif"},
    {RETURN, "return"}
};

#endif
