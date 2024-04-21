#include "../include/read.h"
#include "../include/readtext.h"
#include <stdio.h>
#include <stdlib.h>
#include "../DEBUG/def.h"

text read (char* file)
{
    text txt = {nullptr, nullptr, 0, 0};

    PRINT_DEBUG ("file = %s\n", file);

    if (file != nullptr)
        readtext (&txt, file);

    return txt;
}
