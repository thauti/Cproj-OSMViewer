#include <stdlib.h>
#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>


void debugNode(node* n);
void parsetoabr(xmlNode* node, tree_node* rootN, tree_way* rootW);
int parse(char* filename, tree_node* abrN, tree_way* abrW);