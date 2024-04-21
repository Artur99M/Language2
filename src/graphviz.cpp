#include <stdio.h>
#include "../include/tree.h"
#include "../include/TREE_EXP.h"
#include "../include/graphviz.h"


void Graphviz (Node* pNode, char* file)
{
    FILE* outfile = fopen (file, "w");
    if (outfile == nullptr)
        return;

    fprintf (outfile, "digraph\n{\n");
    fprintf (outfile, "\t\"%p\n", pNode);
    if (pNode->type == NUMBER)
        fprintf (outfile, "%lf\"", pNode->value.number);
    else if (pNode->type == VARIABLE)
        fprintf (outfile, "%c\"", pNode->value.variable);
    else if (pNode->type == OPERATION)
        fprintf (outfile, "%s\"", OPERATIONS[pNode->value.operation - 1].name);
    if (pNode)
        CreateGraph(pNode, outfile);
    fprintf (outfile, "}\n");



}

void CreateGraph(Node* pNode, FILE* outfile)
{
    if (pNode == nullptr) return;
    if (pNode->left)
    {
        fprintf (outfile, "\t\"%p\n", pNode);
        if (pNode->type == NUMBER)
            fprintf (outfile, "%lf\" ->", pNode->value.number);
        else if (pNode->type == VARIABLE)
            fprintf (outfile, "%c\" ->", pNode->value.variable);
        else if (pNode->type == OPERATION)
            fprintf (outfile, "%s\" -> ", OPERATIONS[pNode->value.operation - 1].name);

        fprintf (outfile, "\t\"%p\n", pNode->left);
        if (pNode->left->type == NUMBER)
            fprintf (outfile, "%lf\"\n", pNode->left->value.number);
        else if (pNode->left->type == VARIABLE)
            fprintf (outfile, "%c\"\n", pNode->left->value.variable);
        else if (pNode->left->type == OPERATION)
            fprintf (outfile, "%s\"\n", OPERATIONS[pNode->left->value.operation - 1].name);
        CreateGraph(pNode->left, outfile);
    }
    if (pNode->right)
    {
        fprintf (outfile, "\t\"%p\n", pNode);
        if (pNode->type == NUMBER)
            fprintf (outfile, "%lf\" ->", pNode->value.number);
        else if (pNode->type == VARIABLE)
            fprintf (outfile, "%c\" ->", pNode->value.variable);
        else if (pNode->type == OPERATION)
            fprintf (outfile, "%s\" -> ", OPERATIONS[pNode->value.operation - 1].name);

        fprintf (outfile, "\t\"%p\n", pNode->right);
        if (pNode->right->type == NUMBER)
            fprintf (outfile, "%lf\"\n", pNode->right->value.number);
        else if (pNode->right->type == VARIABLE)
            fprintf (outfile, "%c\"\n", pNode->right->value.variable);
        else if (pNode->right->type == OPERATION)
            fprintf (outfile, "%s\"\n", OPERATIONS[pNode->right->value.operation - 1].name);
        CreateGraph(pNode->right, outfile);
    }
}
