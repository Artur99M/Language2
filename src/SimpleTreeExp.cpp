#include "../include/SimpleTreeExp.h"
#include "../include/tree.h"
#include "../DEBUG/def.h"
#include "../include/graphviz.h"
#include <stdio.h>
#include <math.h>
int i = 4;

void SimpleChange (Node* pNode, char value);
const double Eps = 1e-9;

#define CONST(pNode) ((pNode->left->type == NUMBER) && (pNode->right->type == NUMBER))
#define CONST1(pNode) (pNode->left->type == NUMBER)
#define ChangeConst(pNode) pNode->type = NUMBER; TreeDtor (pNode->left); if (pNode->right != nullptr) TreeDtor (pNode->right); pNode->left = nullptr; pNode->right = nullptr;
#define pi 3.1415f

bool isZero (double x)
{
    return abs (x) < Eps;
}
bool isOne (double x)
{
    return abs (x - 1) < Eps;
}


bool SimplConst(Node* pNode)
{
    if (pNode == nullptr)
        return true;


    PRINT_DEBUG ("SimplConst >>> pNode->type = %d, pNode->value = ", pNode->type);
    #ifdef DEBUG
    if (pNode->type == NUMBER)
        fprintf (stderr, "%lf\n", pNode->value.number);
    if (pNode->type == VARIABLE)
        fprintf (stderr, "%c\n", pNode->value.variable);
    if (pNode->type == OPERATION)
        fprintf (stderr, "%s\n", OPERATIONS[pNode->value.operation - 1].name);
    #endif

    switch (pNode->type)
    {
        case NUMBER:
            return true;
        case VARIABLE:
            return true;

        case OPERATION:
            PRINT_DEBUG ("SimplConst >>> I\'m in case OPERATION\n");
            PRINT_DEBUG ("CONST(pNode) = %d\n", CONST(pNode));
            PRINT_DEBUG ("CONST1(pNode) = %d, pNode->value.operation = %d\n", CONST1(pNode), pNode->value.operation);
            switch (pNode->value.operation)
            {
                case ADD:
                    if (CONST(pNode))
                    {
                        PRINT_DEBUG ("SimplConst >>> I\'m doing more simple \'+\'\n");
                        pNode->value.number = pNode->left->value.number + pNode->right->value.number;
                        ChangeConst (pNode);
                        return false;
                    }
                    break;
                case SUB:
                    if (CONST(pNode))
                    {
                        PRINT_DEBUG ("SimplConst >>> I\'m doing more simple \'-\'\n");
                        pNode->value.number = pNode->left->value.number - pNode->right->value.number;
                        ChangeConst (pNode);
                        return false;
                    }
                    break;
                case MUL:
                    if (CONST(pNode))
                    {
                        PRINT_DEBUG ("SimplConst >>> I\'m doing more simple \'*\'\n");
                        pNode->value.number = pNode->left->value.number * pNode->right->value.number;
                        ChangeConst (pNode);
                        return false;
                    }
                    break;
                case DIV:
                    if (CONST(pNode))
                    {
                        PRINT_DEBUG ("SimplConst >>> I\'m doing more simple \'\\\'\n");
                        pNode->value.number = pNode->left->value.number / pNode->right->value.number;
                        ChangeConst (pNode);
                        return false;
                    }
                    break;
                case SIN:
                    if (pNode->left->type == NUMBER)
                    {
                        PRINT_DEBUG ("SimplConst >>> I\'m doing more simple \'sin\'\n");
                        pNode->value.number = sin(pNode->left->value.number);
                        ChangeConst (pNode);
                        return false;
                    }
                    break;
                case COS:
                    if (CONST1(pNode))
                    {
                        PRINT_DEBUG ("SimplConst >>> I\'m doing more simple \'cos\'\n");
                        pNode->value.number = cos(pNode->left->value.number);
                        ChangeConst (pNode);
                        return false;
                    }
                    break;
                case TG:
                    if (CONST1(pNode))
                    {
                        PRINT_DEBUG ("SimplConst >>> I\'m doing more simple \'tg\'\n");
                        pNode->value.number = tan(pNode->left->value.number);
                        ChangeConst (pNode);
                        return false;
                    }
                    break;
                case CTG:
                    if (CONST1(pNode))
                    {
                        PRINT_DEBUG ("SimplConst >>> I\'m doing more simple \'ctg\'\n");
                        pNode->value.number = 1 / tan(pNode->left->value.number);
                        ChangeConst (pNode);
                        return false;
                    }
                case EXP:
                    if (CONST(pNode))
                    {
                        PRINT_DEBUG ("SimplConst >>> I\'m doing more simple \'exp\'\n");
                        pNode->value.number = pow(pNode->left->value.number, pNode->left->value.number);
                        ChangeConst (pNode);
                        return false;
                    }
                    break;
                case LOG:
                    if (CONST(pNode))
                    {
                        PRINT_DEBUG ("SimplConst >>> I\'m doing more simple \'log\'\n");
                        pNode->value.number = log (pNode->right->value.number) / log (pNode->left->value.number);
                        ChangeConst (pNode);
                        return false;
                    }
                    break;
                case ARCSIN:
                    if (CONST1(pNode))
                    {
                        PRINT_DEBUG ("SimplConst >>> I\'m doing more simple \'arcsin\'\n");
                        pNode->value.number = asin(pNode->left->value.number);
                        ChangeConst (pNode);
                        return false;
                    }
                    break;
                case ARCCOS:
                    if (CONST1(pNode))
                    {
                        PRINT_DEBUG ("SimplConst >>> I\'m doing more simple \'arccos\'\n");
                        pNode->value.number = acos(pNode->left->value.number);
                        ChangeConst (pNode);
                        return false;
                    }
                    break;
                case ARCTG:
                    if (CONST1(pNode))
                    {
                        PRINT_DEBUG ("SimplConst >>> I\'m doing more simple \'arctg\'\n");
                        pNode->value.number = atan(pNode->left->value.number);
                        ChangeConst (pNode);
                        return false;
                    }
                    break;
                case ARCCTG:
                    if (CONST1(pNode))
                    {
                        PRINT_DEBUG ("SimplConst >>> I\'m doing more simple \'arcctg\'\n");
                        pNode->value.number = pi - atan(pNode->left->value.number);
                        ChangeConst (pNode);
                        return false;
                    }
                    break;
            }
    }

    return (SimplConst (pNode->left) && SimplConst(pNode->right));
}

void SimplTree(Node* pNode)
{
    if (pNode == nullptr)
        return;

    #ifdef DEBUG
    char s[32] = "";
    sprintf (s, "graphviz/Tree%d", i++);
    Graphviz (pNode, s);
    #endif

    while (true)
        if (SimplConst(pNode) && Simpl01(pNode))
            break;
}

void SimpleChange (Node* pNode, char value)
{
    if (pNode == nullptr || (value != 'l' && value != 'r'))
        return;

    PRINT_DEBUG ("SimpleChange >>> run\n");
    PRINT_DEBUG ("SimpleChange >>> start: pNode = %p, pNode->value = \"%lg\", pNode->type = %d, pNode->left = %p, pNode->right = %p\n", pNode, pNode->value.number, pNode->type, pNode->left, pNode->right);

    if (value == 'r')
    {
        TreeDtor (pNode->left);
        Node* oldnode = pNode->right;
        *pNode = *oldnode;
        free (oldnode);
    }
    else
    {
        TreeDtor (pNode->right);
        Node* oldnode = pNode->left;
        *pNode = *oldnode;
        free (oldnode);
    }
    PRINT_DEBUG ("SimpleChange >>> finish: pNode = %p, pNode->value = \"%lg\", pNode->type = %d, pNode->left = %p, pNode->right = %p\n", pNode, pNode->value.number, pNode->type, pNode->left, pNode->right);
}

void ChangeToNum (Node* pNode, double num)
{
    if (pNode == nullptr)
        return;
    PRINT_DEBUG ("ChangeToNum >>> start: pNode = %p, pNode->value = \"%lg\", pNode->type = %d, pNode->left = %p, pNode->right = %p\n", pNode, pNode->value.number, pNode->type, pNode->left, pNode->right);

    TreeDtor (pNode->left);  pNode->left  = nullptr;
    TreeDtor (pNode->right); pNode->right = nullptr;
    pNode->value.number = num;
    pNode->type = NUMBER;

PRINT_DEBUG ("ChangeToNum >>> finish: pNode = %p, pNode->value = \"%lg\", pNode->type = %d, pNode->left = %p, pNode->right = %p\n", pNode, pNode->value.number, pNode->type, pNode->left, pNode->right);
}

bool  Simpl01 (Node* pNode)
{
    if (pNode == nullptr)
        return true;

    if (pNode->type != OPERATION)
        return true;
    bool answer = Simpl01(pNode->left) && Simpl01(pNode->right);

    PRINT_DEBUG ("Simpl01 >>> run: pNode = %p, pNode->value = \"%lg\", pNode->type = %d, pNode->left = %p, pNode->right = %p\n", pNode, pNode->value.number, pNode->type, pNode->left, pNode->right);

    switch (pNode->value.operation)
    {
        case MUL:
            PRINT_DEBUG("Simpl01 >>> MUL\n");
            if (pNode->left->type  == NUMBER && isOne (pNode->left->value.number))
            { SimpleChange (pNode, 'r'); return false; }
            if (pNode->right->type == NUMBER && isOne (pNode->right->value.number))
            { SimpleChange (pNode, 'l'); return false; }

            if (pNode->left->type  == NUMBER && isZero (pNode->left->value.number))
            { ChangeToNum (pNode, 0);    return false; }
            if (pNode->right->type == NUMBER && isZero (pNode->right->value.number))
            { ChangeToNum (pNode, 0);    return false; }
            break;

        case ADD:
            PRINT_DEBUG("Simpl01 >>> ADD\n");
            if (pNode->left->type  == NUMBER && isZero (pNode->left->value.number))
            { SimpleChange (pNode, 'r'); return false; }
            if (pNode->right->type == NUMBER && isZero (pNode->left->value.number))
            { SimpleChange (pNode, 'l'); return false; }
            break;

        case SUB:
            PRINT_DEBUG("Simpl01 >>> SUB\n");
            if (pNode->right->type  == NUMBER && isZero (pNode->left->value.number))
            { SimpleChange (pNode, 'l'); return false; }
            break;

        case DIV:
            PRINT_DEBUG("Simpl01 >>> DIV\n");
            if (pNode->left->type  == NUMBER && isZero (pNode->left->value.number))
            { ChangeToNum (pNode, 0);    return false; }
            break;

        case EXP:
            PRINT_DEBUG("Simpl01 >>> EXP\n");
            if (pNode->left->type  == NUMBER && isOne (pNode->left->value.number))
            { ChangeToNum (pNode, 1);    return false; }
            if (pNode->right->type  == NUMBER && isOne (pNode->right->value.number))
            { SimpleChange (pNode, 'l'); return false; }

            if (pNode->left->type  == NUMBER && isZero (pNode->left->value.number))
            { ChangeToNum (pNode, 0);    return false; }
            if (pNode->right->type == NUMBER && isZero (pNode->right->value.number))
            { ChangeToNum (pNode, 1);    return false; }
            break;
    }

    PRINT_DEBUG ("Simpl01 >>> finish: pNode = %p, pNode->value = \"%lg\", pNode->type = %d, pNode->left = %p, pNode->right = %p\n", pNode, pNode->value.number, pNode->type, pNode->left, pNode->right);

    return answer;
}

// bool SimpleRow (Node* pNode)
// {
//     if (pNode == nullptr)
//         return false;
//
//     bool answer = SimpleRow (pNode->left) && SimpleRow (pNode->right);
//
//     if (pNode->type == OPERATION)
//     {
//         switch (pNode->type)
//         {
//             case ADD:
//             {
//                 if (pNode.)
//             }
//
//         }
//     }
//
//     return answer;
// }
