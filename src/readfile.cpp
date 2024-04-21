#include "../include/readfile.h"
#include "../DEBUG/def.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

TREE_ERROR TreeRead (Node* pNode, FILE* file);
void type_and_def_init (Node* pNode, char* s);


TREE_ERROR readfile (Node** Tree, char* file)
{
    if (Tree == nullptr) return TREE_NULLPTR;

    // text txt;
    // readtext (&txt, file);
    // PRINT_DEBUG ("readfile >>> txt.numlines = %lu\n", txt.numlines);
    // size_t nline = 0;
    // Node* array = (Node*) calloc (txt.numlines, sizeof (Node));
    // *Tree = array;
    FILE* infile = fopen (file, "r");
    if (infile == nullptr) return TREE_FILE_NULLPTR;
    TREE_ERROR ERROR = TreeRead (*Tree, infile);
    PRINT_DEBUG ("readfile >>> finish\n");

    // txtDtor (&txt);

    return ERROR;
}

TREE_ERROR TreeRead (Node* pNode, FILE* file)
{

    if (pNode == nullptr || file == nullptr)
        return TREE_NULLPTR;

    char c = '\0';
    PRINT_DEBUG ("TreeRead >>> I start sscanf\n");
    PRINT_DEBUG ("TreeRead >>> pNode = %p\n", pNode);
    char s [MAX_STR_SIZE] = "";
    fgets (s, MAX_STR_SIZE, file);
    sscanf (s, "%c", &c);
    PRINT_DEBUG ("TreeRead >>> s = \"%s\"\n", s);
    PRINT_DEBUG ("TreeRead >>> first sscanf: c = %c\n", c);
    // (*nline)++;

    if (c == '{')
    {
        PRINT_DEBUG ("TreeRead >>> func start do it smth\n");
        fgets (s, MAX_STR_SIZE, file);
        type_and_def_init (pNode, s);
        PRINT_DEBUG ("TreeRead >>> s[strlen(s) - 1] = \'[%d]\'\n", s[strlen(s) - 1]);
        // (*nline)++;
        PRINT_DEBUG ("TreeRead >>> find memmory for left\n");
        PRINT_DEBUG ("TreeRead >>> &(pNode->left) = %p\n", &(pNode->left));
        if ((pNode->left = (Node*) calloc (1, sizeof (Node))) == nullptr)
            return TREE_NULLPTR;
        PRINT_DEBUG ("TreeRead >>> start see left\n");
        PRINT_DEBUG ("TreeRead >>> pNode->left = %p\n", pNode->left);
        if (TreeRead (pNode->left, file) == TREE_VOID)
        {
            free (pNode->left);
            pNode->left = nullptr;
        }
        PRINT_DEBUG ("TreeRead >>> finish see left\n");
        PRINT_DEBUG ("TreeRead >>> pNode->left = %p\n", pNode->left);
        PRINT_DEBUG ("TreeRead >>> find memmory for right\n");
        PRINT_DEBUG ("TreeRead >>> &(pNode->right) = %p\n", &(pNode->right));
        if ((pNode->right = (Node*) calloc (1, sizeof (Node))) == nullptr)
            return TREE_NULLPTR;
        PRINT_DEBUG ("TreeRead >>> pNode->right = %p\n", pNode->right);
        PRINT_DEBUG ("TreeRead >>> start see right\n");
        if (TreeRead (pNode->right, file) == TREE_VOID)
        {
            free (pNode->right);
            pNode->right = nullptr;
        }
        PRINT_DEBUG ("TreeRead >>> finish see right\n");
        PRINT_DEBUG ("TreeRead >>> pNode->right = %p\n", pNode->right);
        fgets (s, MAX_STR_SIZE, file);
        sscanf (s, "%c", &c);
        PRINT_DEBUG ("TreeRead >>> third sscanf: c = %c[%d]\n", c, c);
        if (c != '}')
            return TREE_HZ_ERROR;
        // (*nline)++;
        PRINT_DEBUG ("TreeRead >>> finish: pNode = %p, pNode->value = \"%lg\", pNode->left = %p, pNode->right = %p\n", pNode, pNode->value.number, pNode->left, pNode->right);
    }
    else if (c == '#')
    {
        PRINT_DEBUG ("TreeRead >>> free memory\n");
        return TREE_VOID;
    }
    else
    {
        PRINT_DEBUG ("TreeRead >>> Strange ERROR\n");
        return TREE_HZ_ERROR;
    }

    return TREE_NO_ERROR;
}

void type_and_def_init (Node* pNode, char* s)
{
    if (pNode == nullptr || s == nullptr)
        return;

    double x = 0;

    if (sscanf (s, "%lg", &x) == 1)
    {
        pNode->value.number = x;
        pNode->type = NUMBER;
        PRINT_DEBUG ("TreeRead >>> pNode->type = NUMBER, pNode->value.number = %lf\n", pNode->value.number);
        return;
    }

    char str[7] = "";
    sscanf (s, "%s", str);
    for (int i = 1; i <= num_operation; i++)
    {
        if (strcmp (str, OPERATIONS[i].name) == 0)
        {
            pNode->type = OPERATION;
            pNode->value.operation = OPERATIONS[i].value;
            PRINT_DEBUG ("TreeRead >>> pNode->type = OPERATION, pNode->value.operation = %d\n", pNode->value.operation);
            return;
        }
    }
    char c = '0';
    sscanf (s, "%c", &c);
    pNode->type = VARIABLE;
    pNode->value.variable = c;
    PRINT_DEBUG ("TreeRead >>> pNode->type = VARIABLE, pNode->value.variable = \'%c\'\n", pNode->value.variable);

    return;

}
