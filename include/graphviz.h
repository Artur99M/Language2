#ifndef GRAPHVIZ_H
#define GRAPHVIZ_H
#include <stdio.h>
#include "tree.h"
void Graphviz (Node* pNode, char* file);
void CreateGraph(Node* pNode, FILE* outfile);
#endif
