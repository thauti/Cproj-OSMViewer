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

	xmlNode* curr = nodeX->xmlChildrenNode;
	node* no = malloc(sizeof(node));
	way* wa = malloc(sizeof(way));
    bound* bo = malloc(sizeof(bound));
	curr = curr->next;
	while(curr != NULL)
	{
		if (curr->type == XML_ELEMENT_NODE) {
            if(strcmp(curr->name, "bounds") == 0)
            {
                bo->minlat = atof(xmlGetProp(curr, "minlat"));
                bo->maxlat = atof(xmlGetProp(curr, "maxlat"));
                bo->maxlon = atof(xmlGetProp(curr, "maxlon"));
                bo->minlon = atof(xmlGetProp(curr, "minlon"));
            }
			 if(strcmp(curr->name, "node") == 0){

        		no = malloc(sizeof(node));
        		no->id = atoll(xmlGetProp(curr, "id"));
        		no->lat = atof(xmlGetProp(curr, "lat"));
        		no->longi = atof(xmlGetProp(curr, "lon"));
                if(!strcmp(xmlGetProp(curr, "visible"), "true"))
                {
                    no->visible = 1;
                }
                else
                {
                    no->visible = 0;
                }
        		//debugNode(no);
        		insertNode(no, rootN);
         	}
         	if(strcmp(curr->name, "way") == 0){

        		wa = malloc(sizeof(way));
        		wa->id = atoll(xmlGetProp(curr, "id"));
                if(!strcmp(xmlGetProp(curr, "visible"), "true"))
                {
                    wa->visible = 1;
                }
                else
                {
                    wa->visible = 0;
                }
        		insertWay(wa, rootW);

        		xmlNode * nd = curr->xmlChildrenNode;
        		int n_tag = 0;
        		while(nd != NULL)
        		{
        			if (nd->type == XML_ELEMENT_NODE) {
        				//printf("%s \n",  nd->name);
        				if(strcmp(nd->name, "nd") ==0)
        				{
    	    				n_tag++;
	        			}
        			}
        			nd = nd->next;
        		}
        		nd = curr->xmlChildrenNode;
        		wa->nodes = malloc(n_tag);
        		wa->nodes_size = n_tag+1;
        		int i =0;
        		while(nd != NULL)
        		{
        			if (nd->type == XML_ELEMENT_NODE) {
        				if(strcmp(nd->name, "nd") == 0)
        				{
    	    				
    	    				wa->nodes[i] = getNodeById(atoll(xmlGetProp(nd, "ref")),rootN);
	        				
	        				
	        				i++;
	        			}
	        		}
        			nd = nd->next;
        		}
         	}
		}
		curr = curr->next;
	}
/*
	xmlNode* curr=NULL;
    node* no = malloc(sizeof(node));
    way* wa = malloc(sizeof(way));
	for(curr = nodeX;curr;curr=curr->next)
	{
		 if (curr->type == XML_ELEMENT_NODE) {
		 	printf("node type: Element, name: %s\n", curr->name);
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
        		insertWay(wa, rootW);
         	}
        }
    printf("+");
    parsetoabr(curr->xmlChildrenNode, rootN ,rootW);
	}*/
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
