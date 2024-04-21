#include "../include/Diff.h"
#include "../include/tree.h"
#include "../include/TeX.h"
#include <stdio.h>
#ifndef nullptr
#define nullptr 0x0
#endif
// Node* CreateNodeNumber  (double, Node*, Node*);
// Node* CreaNodeOperation (OP,     Node*, Node*);
// Node* CreaNodeVariable  (char,   Node*, Node*);
#ifndef exp
#define exp 2.718281828f
#endif
#define _D(x) Diff(x)
#define _C(x) TreeCopy(x)
#define _ADD(left, right) CreateNodeOperation(ADD, left, right)
#define _SUB(left, right) CreateNodeOperation(SUB, left, right)
#define _MUL(left, right) CreateNodeOperation(MUL, left, right)
#define _DIV(left, right) CreateNodeOperation(DIV, left, right)
#define _EXP(left, right) CreateNodeOperation(EXP, left, right)
#define _SIN(x) CreateNodeOperation (SIN, x, nullptr)
#define _COS(x) CreateNodeOperation (COS, x, nullptr)
#define _LN(x) CreateNodeOperation ( LOG, CreateNodeNumber(exp, nullptr, nullptr), x)


Node* Diff (const Node* pNode)
{
    if (pNode == nullptr)
        return nullptr;
    TeX_Diff_Print_Start (pNode);

    Node* val = nullptr;

    switch (pNode->type)
    {
        case NUMBER:
            val = CNN (0);
            break;
        case VARIABLE:
            val = CNN (1);
            break;
        case OPERATION:
            switch (pNode->value.operation)
            {
                case ADD:
                    val = _ADD (_D(pNode->left), _D(pNode->right));
                    break;
                    // return CreateNode (OPERATION, ADD, Diff(pNode->left), Diff (pNode->right));
                case SUB:
                    val = _SUB (_D(pNode->left), _D(pNode->right));
                    break;
                    // return CreateNode (OPERATION, SUB, Diff(pNode->left), Diff (pNode->right));
                case MUL:
                    val = _ADD (_MUL (_D(pNode->left), _C(pNode->right)), _MUL (_C(pNode->left), _D(pNode->right)));
                    break;
                case DIV:
                    val = _DIV (_SUB (_MUL (_D(pNode->left), _C(pNode->right)), _MUL (_C(pNode->left), _D(pNode->right))),
                    _EXP(_C(pNode->right), CNN(2)));
                    break;

                case SIN:
                    val = _MUL (_COS (_C(pNode->left)), _D(pNode->left));
                    break;
                case COS:
                    val = _MUL (_SIN (_C(pNode->left)), _D(pNode->left));
                    break;
                case EXP:
                    if (pNode->left->type != NUMBER && pNode->right->type == NUMBER)
                        val = _MUL(_MUL (_C(pNode->right), _EXP(_C(pNode->left), _SUB(_C(pNode->right),
                        CNN (1)))), _D(pNode->left));
                    else if (pNode->left->type == NUMBER && pNode->right->type != NUMBER)
                        val = _MUL (_MUL (_LN (_C(pNode->left)), _C(pNode)), _D(pNode->right));
                    else if (pNode->left->type != NUMBER && pNode->right->type != NUMBER)
                        val = _MUL (_EXP (CNN(exp), _MUL (_C(pNode->left), _LN(pNode->right))), _D (_MUL (_C(pNode->left), _LN(pNode->right))));
                    break;
                case LOG:
                    if (pNode->left->type == NUMBER && pNode->right->type != NUMBER)
                        val = _MUL (_DIV(CNN (1), _MUL(_C(pNode->right), _LN(_C(pNode->left)))), _D(pNode->right));
                    else if (pNode->left->type != NUMBER && pNode->right->type == NUMBER)
                        val = _D(_DIV (CNN (1), CreateNodeOperation(LOG, _C(pNode->right), _C(pNode->left))));
                    else if (pNode->left->type != NUMBER && pNode->right->type != NUMBER)
                        val = _D (_DIV ( _LN (pNode->left), _LN (pNode->right)));
                    break;
                case ARCSIN:
                    val = _MUL (_DIV (CNN(1), _EXP (_ADD (CNN(1), _EXP(_C(pNode->left),
                    CNN(2))), CNN(0.5f))), _D(pNode->left));
                    break;
                case ARCCOS:
                    val = _MUL (_SUB (CNN(0), _DIV (CNN(1), _EXP (_ADD (CNN(1), _EXP(_C(pNode->left),
                    CNN(2))), CNN(0.5f)))), _D(pNode->left));
                    break;
                case ARCTG:
                    val = _MUL(_DIV(CNN(1), _ADD(CNN(1), _EXP(_C(pNode->left), CNN(2)))), _D(pNode->left));
                    break;
                case ARCCTG:
                    val = _MUL(_SUB (CNN(0), _DIV(CNN(1), _ADD(CNN(1), _EXP(_C(pNode->left), CNN(2))))), _D(pNode->left));
                    break;
                case TG:
                    val = _MUL (_DIV (CNN(1), _EXP (_COS (_C(pNode->left)), CNN(2))), _D(pNode->left));
                    break;
                case CTG:
                    val = _MUL (_DIV (CNN(1), _EXP (_SIN (_C(pNode->left)), CNN(2))), _D(pNode->left));


            }
    }

    if (val != nullptr) TeX_Diff_Print_Finish (val);
    return val;
}
