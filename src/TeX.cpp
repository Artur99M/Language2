#include "../include/TeX.h"
#include "../include/TREE_EXP.h"
#include "../DEBUG/def.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
const size_t start_size = 100;
FILE* outfile = fopen ("TeX/TeX.tex", "w");

void TEX_PRINT (const Node* pNode)
{
    PRINT_DEBUG ("start\n");
    char* str = node_to_str (pNode);
    PRINT_DEBUG ("I print \"%s\"\n", str);
    fprintf (outfile, "\\[%s\\]\n", str);
    free (str);
}

char* node_to_str (const Node* pNode)
{
    PRINT_DEBUG ("start\n");
    if (pNode == nullptr)
        return nullptr;

    char* str = nullptr;
    char *l = nullptr, *r = nullptr;
    if (pNode->left != nullptr)
        l = node_to_str (pNode->left);
    if (pNode->right != nullptr)
        r = node_to_str (pNode->right);
    switch (pNode->type)
    {
        case VARIABLE:
            PRINT_DEBUG ("I\'m in VARIABLE\n");
            str = (char*) calloc (10, sizeof (char));
            PRINT_DEBUG ("I find memory\n");
            str[0] = pNode->value.variable;
            break;
        case NUMBER:
            PRINT_DEBUG ("I\'m in NUMBER\n");
            str = (char*) calloc (33, sizeof (char));
            sprintf (str, "%lf", pNode->value.number);
            str[20] = '\0';
            break;
        case OPERATION:
            PRINT_DEBUG ("I\'m in OPERATION\n");
            PRINT_DEBUG ("l = %s, r = %s\n", l, r);
            size_t size = 0;
            size_t size_l = 0;
            switch (pNode->value.operation)
            {
                case ADD:
                    PRINT_DEBUG ("I\'m seeing operation ADD\n");
                    size_l = strlen (l);
                    size = size_l + strlen (r) + 5;
                    str = (char*) calloc (size, sizeof (char));
                    strcpy (str, l);
                    PRINT_DEBUG ("1: str = %s\n", str);
                    str[size_l] = '+';
                    PRINT_DEBUG ("2: str = %s\n", str);
                    strncat (str, r, size - 1);
                    PRINT_DEBUG ("3: str = %s\n", str);
                    PRINT_DEBUG ("4: str = %s\n", str);
                    break;
                case SUB:
                    PRINT_DEBUG ("I\'m seeing operation SUB\n");
                    if (l == nullptr)
                    {
                        str = (char*) calloc (strlen (r) + 2, sizeof (char));
                        str[1] = '-';
                        strcat (str, r);
                    }
                    else
                    {
                        size_l = strlen (l);
                        size = size_l + strlen (r) + 2;
                        str = (char*) calloc (strlen (l) + strlen (r) + 2, sizeof (char));
                        strcpy (str, l);
                        str[size_l] = '-';
                        strncat (str, r, size - 1);
                    }
                case MUL:
                    PRINT_DEBUG ("I\'m seeing operation MUL\n");
                    size_l = strlen (l);
                    size = size_l + strlen (r) + 6;
                    str = (char*) calloc (size, sizeof (char));
                    strcpy (str, l);
                    strncat (str, "\\cdot ", size - 1);
                    strncat (str, r, size - 1);
                    break;
                case EXP:
                    PRINT_DEBUG ("I\'m seeing operation EXP\n");
                    size_l = strlen (l);
                    size = size_l + strlen (r) + 10;
                    str = (char*) calloc (size, sizeof (char));
                    strcpy (str, l);
                    strncat (str, "^{", size - 1);
                    strncat (str, r, size - 1);
                    strncat (str, "}", size - 1);
                    break;
                case DIV:
                    PRINT_DEBUG ("I\'m seeing operation DIV\n");
                    size_l = strlen (l);
                    size = size_l + strlen (r) + 10;
                    str = (char*) calloc (size, sizeof (char));
                    strcpy (str, "\\frac{");
                    strncat (str, l, size - 1);
                    strncat (str, "}{", size - 1);
                    strncat (str, r, size - 1);
                    strncat (str, "}", size - 1);
                    break;
                case LOG:
                    PRINT_DEBUG ("I\'m seeing operation LOG\n");
                    size_l = strlen (l);
                    size = size_l + strlen (r) + 19;
                    str = (char*) calloc (size, sizeof (char));
                    strcpy (str, "\\log_{");
                    strncat (str, l, size - 1);
                    strncat (str, "}\\left(", size - 1);
                    strncat (str, r, size - 1);
                    strncat (str, "\\right)", size - 1);
                    break;
                case SIN:
                    PRINT_DEBUG ("I\'m seeing operation SIN\n");
                    size = strlen (l) + 18;
                    str = (char*) calloc (size, sizeof (char));
                    strcat (str, "\\sin\\left(");
                    strncat (str, l, size - 1);
                    strncat (str, "\\right)", size - 1);
                    break;
                case COS:
                    PRINT_DEBUG ("I\'m seeing operation COS\n");
                    size = strlen (l) + 18;
                    str = (char*) calloc (size, sizeof (char));
                    strcpy (str, "\\cos\\left(");
                    strncat (str, l, size - 1);
                    strncat (str, "\\right)", size - 1);
                    break;
                case TG:
                    PRINT_DEBUG ("I\'m seeing operation TG\n");
                    size = strlen (l) + 17;
                    str = (char*) calloc (size, sizeof (char));
                    strcpy (str, "\\tg\\left(");
                    strncat (str, l, size - 1);
                    strncat (str, "\\right)", size - 1);
                    break;
                case CTG:
                    PRINT_DEBUG ("I\'m seeing operation CTG\n");
                    size = strlen (l) + 18;
                    str = (char*) calloc (size, sizeof (char));
                    strcpy (str, "\\ctg\\left(");
                    strncat (str, l, size - 1);
                    strncat (str, "\\right)", size - 1);
                    break;
                case ARCSIN:
                    PRINT_DEBUG ("I\'m seeing operation ARCSIN\n");
                    size = strlen (l) + 21;
                    str = (char*) calloc (size, sizeof (char));
                    strcpy (str, "\\arcsin\\left(");
                    strncat (str, l, size - 1);
                    strncat (str, "\\right)", size - 1);
                    break;
                case ARCCOS:
                    PRINT_DEBUG ("I\'m seeing operation ARCCOS\n");
                    size = strlen (l) + 21;
                    str = (char*) calloc (size, sizeof (char));
                    strcpy (str, "\\arccos\\left(");
                    strncat (str, l, size - 1);
                    strncat (str, "\\right)", size - 1);
                    break;
                case ARCTG:
                    PRINT_DEBUG ("I\'m seeing operation ARTCG\n");
                    size = strlen (l) + 20;
                    str = (char*) calloc (size, sizeof (char));
                    strcpy (str, "\\arctg\\left(");
                    strncat (str, l, size - 1);
                    strncat (str, "\\right)", size - 1);
                    break;
                case ARCCTG:
                    PRINT_DEBUG ("I\'m seeing operation ARCCTG\n");
                    size = strlen (l) + 21;
                    str = (char*) calloc (size, sizeof (char));
                    strcpy (str, "\\arcctg\\left(");
                    strncat (str, l, size - 1);
                    strncat (str, "\\right)", size - 1);
                    break;

            }
    }
    if (l == nullptr) free (l);
    if (r == nullptr) free (r);
    PRINT_DEBUG ("str = %s\n", str)
    return str;
}

const char* start_str[] = {"Нам нужно разобраться с этим:\n", "Теперь разберемся с этим\n","Рассмотрим это выражение\n",
"Кажется, что с этим уравнением мы не справимся\n","Сделаем несколько преобразований и получим это\n"};
const int n_start_strs = 4;
unsigned int qw = 0;
const char* finish_str[] = {"После очевидных преобразований получаем такую производную\n", "У нас получилась эта страшная штука:\n",
"Результатом нашего труда стало это выражение\n", "Итоговое выражение для производной\n"};

void TeX_Diff_Print_Start (const Node* pNode)
{
    if (pNode == nullptr) return;

    fprintf (outfile, "%s", start_str[qw - (qw/n_start_strs)*n_start_strs]);
    qw++;
    TEX_PRINT (pNode);
}

const int n_finish_strs = 4;
unsigned int wq = 0;

void TeX_Diff_Print_Finish (const Node* pNode)
{
    if (pNode == nullptr) return;

    fprintf (outfile, "%s", finish_str[wq - (wq/n_finish_strs)*n_finish_strs]);
    wq++;
    TEX_PRINT (pNode);
}
