#include "../include/tree.h"
#include "../DEBUG/def.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

TREE_ERROR TreePrint (const Node* Tree)
{
    if (Tree == nullptr)
        return TREE_NULLPTR;

    // PRINT_DEBUG ("TreePrint >>> start\n");
    // PRINT_DEBUG ("TreePrint >>> Tree->value = %s\n", Tree->value);
    printf ("{\ntype = %d ", Tree->type);
    if (Tree->type == NUMBER)
        printf ("\"%lf\"\n", Tree->value.number);
    else if (Tree->type == VARIABLE)
        printf ("\"%c\"\n", Tree->value.variable);
    else if (Tree->type == OPERATION)
        printf ("\"%s\"\n", OPERATIONS[Tree->value.operation - 1].name);

    if (Tree->left != nullptr)
    {
        // PRINT_DEBUG ("TreePrint >>> I go to left\n");
        TreePrint (Tree->left);
    }
    else
    {
        // PRINT_DEBUG ("TreePrint >>> left is void\n");
        puts ("#");
    }
    if (Tree->right != nullptr)
    {
        // PRINT_DEBUG ("TreePrint >>> Tree->right = %p\n", Tree->right);
        // PRINT_DEBUG ("TreePrint >>> I go to right\n");
        TreePrint (Tree->right);
    }
    else
    {
        // PRINT_DEBUG ("TreePrint >>> right is void");
        puts ("#");
    }

    puts ("}");
    // PRINT_DEBUG ("TreePrint >>> I finish\n");

    return TREE_NO_ERROR;
}

void TreeDtor (Node* Tree)
{
    if (Tree == nullptr)
        return;

    PRINT_DEBUG ("TreeDtor >>> &Tree = %p, Tree->value = \"%lf\", Tree->left = %p, Tree->right = %p\n", Tree, Tree->value.number, Tree->left, Tree->right);
    if (Tree->left != nullptr)
        TreeDtor (Tree->left);
    if (Tree->right != nullptr)
        TreeDtor (Tree->right);

    Tree->value.number = 0;
    Tree->left  = nullptr;
    Tree->right = nullptr;
    free (Tree);

    return;
}

TREE_ERROR TREE_FPRINT (Node* Tree, FILE* outfile)
{
    if (Tree == nullptr)
        return TREE_NULLPTR;
    if (outfile == nullptr)
        return TREE_FILE_NULLPTR;

    PRINT_DEBUG ("TREE_FPRINT >>> Tree = %p, Tree->value = \"%lf\"\n", Tree, Tree->value.number);
    fputs ("{\n", outfile);

    if (Tree->type == NUMBER)
        fprintf (outfile, "{\n%lf\n", Tree->value.number);
    else if (Tree->type == VARIABLE)
        fprintf (outfile, "{\n%c\n", Tree->value.variable);
    else if (Tree->type == OPERATION)
        fprintf (outfile, "{\n%s\n", OPERATIONS[Tree->value.operation - 1].name);

    PRINT_DEBUG ("TREE_FPRINT start putc (\'\\n\', outfile)\n");
    putc ('\n', outfile);
    PRINT_DEBUG ("TREE_FPRINT finish putc (\'\\n\', outfile)\n");
    // return TREE_NO_ERROR;

    if (Tree->left != nullptr)
    {
        PRINT_DEBUG ("TREE_FPRINT >>> Start see left: Tree->left = %p\n", Tree->left);
        TREE_FPRINT (Tree->left, outfile);
    }
    else fputs ("#\n", outfile);
    PRINT_DEBUG ("TREE_FPRINT >>> finish see left\n")
    if (Tree->right != nullptr)
    {
        PRINT_DEBUG ("TREE_FPRINT >>> Start see right: Tree->right = %p\n", Tree->right);
        TREE_FPRINT (Tree->right, outfile);
    }
    else fputs ("#\n", outfile);
    PRINT_DEBUG ("TREE_FPRINT >>> finish see right\n");

    fputs ("}\n", outfile);

    return TREE_NO_ERROR;

}
TREE_ERROR TreeFPrint (Node* Tree, char* file)
{
    if (Tree == nullptr || file == nullptr)
        return TREE_NULLPTR;

    PRINT_DEBUG ("TreeFPrint start\n");

    FILE* outfile = fopen (file, "w");
    if (outfile == nullptr)
        return TREE_FILE_NULLPTR;

    TREE_ERROR ERROR = TREE_FPRINT (Tree, outfile);
    // fputs ("\n\n\n\n\n", outfile);
    return ERROR;
}

Node* TreeCopy (const Node* pNode)
{
    if (pNode == nullptr)
        return nullptr;
    PRINT_DEBUG ("TreeCopy >>> start\n");

    Node* CopyNode = (Node*) calloc (1, sizeof (Node));
    PRINT_DEBUG ("TreeCopy >>> CopyNode = %p\n", CopyNode);
    if (CopyNode == nullptr)
        return nullptr;

    CopyNode->type  = pNode->type;
    CopyNode->value.number = pNode->value.number;
    CopyNode->left  = TreeCopy (pNode->left);
    CopyNode->right = TreeCopy (pNode->right);

    PRINT_DEBUG ("TreeCopy >>> pNode    = %p, pNode->value    = %lg, pNode->type    = %d\n", pNode, pNode->value.number, pNode->type);
    PRINT_DEBUG ("TreeCopy >>> CopyNode = %p, CopyNode->value = %lg, CopyNode->type = %d\n", CopyNode, CopyNode->value.number, CopyNode->type);

    return CopyNode;
}

// Node* CreateNode (TYPE type, double val, Node* left, Node* right)
// {
//     elem_t value;
//     value.number = val;
//     Node* pNode = (Node*) calloc (1, sizeof (Node));
//     PRINT_DEBUG ("CreateNode >>> pNode = %p\n", pNode);
//     if (pNode == nullptr)
//         return nullptr;
//     pNode->type  = type;
//     pNode->left  = left;
//     pNode->right = right;
//     PRINT_DEBUG ("CreateNode >>> pNode->type = %d, pNode->left = %p, pNode->right = %p\n", pNode->type, pNode->left, pNode->right);
//
//     switch (pNode->type)
//     {
//         case NUMBER:
//             pNode->value.number    = value.number;
//             PRINT_DEBUG ("CreateNode >>> pNode->value = %lf\n", pNode->value.number);
//             break;
//         case OPERATION:
//             pNode->value.operation = value.operation;
//             PRINT_DEBUG ("CreateNode >>> pNode->value = %d\n", pNode->value.operation);
//             break;
//         case VARIABLE:
//             pNode->value.variable  = value.variable;
//             PRINT_DEBUG ("CreateNode >>> pNode->value = %c\n", pNode->value.variable);
//             break;
//         default:
//             free(pNode);
//             pNode = nullptr;
//     }
//
//     PRINT_DEBUG ("CreateNode >>> return pNode = %p\n", pNode);
//     return pNode;
// }

Node* CreateNodeNumber (double value, Node* left, Node* right)
{
    Node* pNode = (Node*) calloc (1, sizeof (Node));
    PRINT_DEBUG ("CreateNode >>> pNode = %p\n", pNode);
    if (pNode == nullptr)
        return nullptr;
    pNode->type  = NUMBER;
    pNode->left  = left;
    pNode->right = right;
    PRINT_DEBUG ("CreateNode >>> pNode->type = %d, pNode->left = %p, pNode->right = %p\n", pNode->type, pNode->left, pNode->right);
    pNode->value.number = value;
    PRINT_DEBUG ("CreateNode >>> pNode->value = %lg\n", pNode->value.number);
    PRINT_DEBUG ("CreateNode >>> return pNode = %p\n", pNode);
    return pNode;
}

Node* CreateNodeOperation (OP value, Node* left, Node* right)
{
    Node* pNode = (Node*) calloc (1, sizeof (Node));
    PRINT_DEBUG ("CreateNode >>> pNode = %p\n", pNode);
    if (pNode == nullptr)
        return nullptr;
    pNode->type  = OPERATION;
    pNode->left  = left;
    pNode->right = right;
    PRINT_DEBUG ("CreateNode >>> pNode->type = %d, pNode->left = %p, pNode->right = %p\n", pNode->type, pNode->left, pNode->right);
    pNode->value.operation = value;
    PRINT_DEBUG ("CreateNode >>> pNode->value = %d\n", pNode->value.operation);

    PRINT_DEBUG ("CreateNode >>> return pNode = %p\n", pNode);
    return pNode;
}

Node* CreateNodeVariable (char value, Node* left, Node* right)
{
    Node* pNode = (Node*) calloc (1, sizeof (Node));
    PRINT_DEBUG ("CreateNode >>> pNode = %p\n", pNode);
    if (pNode == nullptr)
        return nullptr;
    pNode->type  = VARIABLE;
    pNode->left  = left;
    pNode->right = right;
    PRINT_DEBUG ("CreateNode >>> pNode->type = %d, pNode->left = %p, pNode->right = %p\n", pNode->type, pNode->left, pNode->right);
    pNode->value.variable = value;
    PRINT_DEBUG ("CreateNode >>> pNode->value = %c\n", pNode->value.variable);

    PRINT_DEBUG ("CreateNode >>> return pNode = %p\n", pNode);
    return pNode;
}

Node* CreateNodeOperator (OPERATORS value, Node* left, Node* right)
{
    Node* pNode = (Node*) calloc (1, sizeof (Node));
    PRINT_DEBUG ("CreateNode >>> pNode = %p\n", pNode);
    if (pNode == nullptr)
        return nullptr;
    pNode->type  = OPERATOR;
    pNode->left  = left;
    pNode->right = right;
    PRINT_DEBUG ("CreateNode >>> pNode->type = %d, pNode->left = %p, pNode->right = %p\n", pNode->type, pNode->left, pNode->right);
    pNode->value.loperator = value;
    PRINT_DEBUG ("CreateNode >>> pNode->value = %d\n", pNode->value.operation);

    PRINT_DEBUG ("CreateNode >>> return pNode = %p\n", pNode);
    return pNode;
}
