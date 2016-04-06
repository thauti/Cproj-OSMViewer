#include <stdlib.h>
#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>


void debugNode(node* n);
double tomercator_x(double src);
double tomercator_y(double src);
void parsetoabr(xmlNode* nodeX, map* usermap);
int parse(char* filename,map* usermap);