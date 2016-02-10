#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libxml/parser.h>
#include <libxml/tree.h>

#include "osm.h"
#include "parse.h"

void debugNode(noeud* n)
{
	printf("id %li\n", n->id);
	printf("lat %f\n", n->lat);
	printf("long %f\n", n->longi);
	printf("visible %d \n", n->visible);

}
void parsetoabr(xmlNode* node, tree_node* root, tree_way* root2)
{
	xmlNode* curr=NULL;
    noeud* no = malloc(sizeof(noeud));
    way* wa = malloc(sizeof(way));
	for(curr = node;curr;curr=curr->next)
	{
		 if (curr->type == XML_ELEMENT_NODE) {
            if(strcmp(curr->name, "node") == 0){

        		no = malloc(sizeof(noeud));
        		no->id = atoll(xmlGetProp(curr, "id"));
        		no->lat = atof(xmlGetProp(curr, "lat"));
        		no->longi = atof(xmlGetProp(curr, "lon"));
        		no->visible = 1;

        		//debugNode(no);
        		insertNode(no, root);
         	}
         	if(strcmp(curr->name, "way") == 0){

        		wa = malloc(sizeof(way));
        		wa->id = atoll(xmlGetProp(curr, "id"));
        		wa->visible = 1;

        		//debugNode(no);
        		insertWay(wa, root2);
         	}
        }
        parsetoabr(curr->children, root,root2);
	}
}

int parse(char* filename, tree_node* abr, tree_way* abr2)
{
	LIBXML_TEST_VERSION
	xmlDocPtr doc;
	xmlNode *root_element;
	doc = xmlReadFile(filename, NULL, 0);
	if(doc==NULL)
	{
		return 1;
	}
	root_element = xmlDocGetRootElement(doc);
	parsetoabr(root_element, abr, abr2);

	xmlFreeDoc(doc);
	xmlCleanupParser();

	printf("\n Fin \n");
	return 0;
}