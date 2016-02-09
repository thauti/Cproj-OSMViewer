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
void parsetoabr(xmlNode* node, tree_node* root)
{
	xmlNode* curr=NULL;
    noeud* no = malloc(sizeof(noeud));
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
        		insert(no, root);
         	}
        }

        parsetoabr(curr->children, root);
	}
}

int parse(char* filename, tree_node* abr)
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
	parsetoabr(root_element, abr);

	xmlFreeDoc(doc);
	xmlCleanupParser();

	printf("\n Fin \n");
	return 0;
}