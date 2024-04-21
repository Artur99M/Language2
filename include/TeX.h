#ifndef TEX_H
#define TEX_H
#include "tree.h"

void TEX_PRINT (const Node*);
char* node_to_str (const Node* pNode);
void TeX_Diff_Print_Start (const Node* pNode);
void TeX_Diff_Print_Finish (const Node* pNode);
#endif
