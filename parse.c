#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libxml/parser.h>
#include <libxml/tree.h>

#include "osm.h"
#include "parse.h"

void debugNode(node* n)
{
	printf("id %li\n", n->id);
	printf("lat %f\n", n->lat);
	printf("long %f\n", n->longi);
	printf("visible %d \n", n->visible);

}
void parsetoabr(xmlNode* nodeX, tree_node* rootN, tree_way* rootW)
{
	xmlNode* curr=NULL;
    node* no = malloc(sizeof(node));
    way* wa = malloc(sizeof(way));
	for(curr = nodeX;curr;curr=curr->next)
	{
		 if (curr->type == XML_ELEMENT_NODE) {
            if(strcmp(curr->name, "node") == 0){

        		no = malloc(sizeof(node));
        		no->id = atoll(xmlGetProp(curr, "id"));
        		no->lat = atof(xmlGetProp(curr, "lat"));
        		no->longi = atof(xmlGetProp(curr, "lon"));
        		no->visible = 1;

        		//debugNode(no);
        		insertNode(no, rootN);
         	}
         	if(strcmp(curr->name, "way") == 0){

        		wa = malloc(sizeof(way));
        		wa->id = atoll(xmlGetProp(curr, "id"));
        		wa->visible = 1;

        		//debugNode(no);
        		insertWay(wa, rootW);
         	}
        }
        parsetoabr(curr->children, rootN ,rootW);
	}
}

int parse(char* filename, tree_node* abrN, tree_way* abrW)
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
	parsetoabr(root_element, abrN, abrW);

	xmlFreeDoc(doc);
	xmlCleanupParser();

	printf("\n Fin \n");
	return 0;
}