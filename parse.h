#include <stdlib.h>
#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>


void debugNode(noeud* n);
void parsetoabr(xmlNode* node, tree_node* root);
int parse(char* filename, tree_node* abr);