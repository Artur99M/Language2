#include "../include/mylanguage_to_myasm.h"
#include <stdio.h>

FILE* outfile_lng  = fopen ("SPU/proga.txt", "w");

void mylanguage_to_myasm (Node* pNode)
{
    if (pNode == nullptr) return;

    // mylanguage_to_myasm (pNode->left);
    switch (pNode->type)
    {
        case OPERATOR:
            switch (pNode->value.loperator)
            {
                case EQUAL:
                    mylanguage_to_myasm (pNode->left);
                    fprintf (outfile_lng, "pop [%d]\n", pNode->right->value.variable - 'a');
                    break;
            }
        case NUMBER:
            fprintf (outfile_lng, "push %lg\n", pNode->value.number);
            break;
        case VARIABLE:
            fprintf (outfile_lng, "push [%d]\n", pNode->value.variable - 'a');
            break;

        case OPERATION:
            mylanguage_to_myasm (pNode->left);
            mylanguage_to_myasm (pNode->right);
            switch (pNode->value.operation)
            {
                case ADD:
                    fprintf (outfile_lng, "add\n");
                case SUB:
                    fprintf (outfile_lng, "sub\n");
                case MUL:
                    fprintf (outfile_lng, "mul\n");
                case DIV:
                    fprintf (outfile_lng, "div\n");
            }

    }
}
