#include <stdio.h>
#include "../include/Get.h"
#include "../include/read.h"
#include "../DEBUG/def.h"
#include "../include/txtdtor.h"
#include "../include/tree.h"
#include "../include/TeX.h"
#include "../include/Diff.h"
#include "../include/SimpleTreeExp.h"
#include "../include/graphviz.h"
#include "../include/mylanguage_to_myasm.h"
#include <stdlib.h>

int main()
{

    text txt = read ("data/file.txt");
    PRINT_DEBUG ("txt.nimlines = %lu\n", txt.numlines);
    Node* x = GetG(txt.line[0].str);
    mylanguage_to_myasm (x);


}
