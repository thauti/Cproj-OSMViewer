#include <stdlib.h>
#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>


void debugNode(node* n);
void parsetoabr(xmlNode* nodeX, map* usermap);
int parse(char* filename,map* usermap);