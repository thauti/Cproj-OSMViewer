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
void parsetoabr(xmlNode* nodeX, map* usermap)
{
                printf("Erreur 1");

    usermap->nodes = malloc(sizeof(tree_node));
    usermap->ways = malloc(sizeof(tree_way));
    usermap->bounds  = malloc(sizeof(bound));
    
    tree_node* rootN = usermap->nodes;
    tree_way* rootW = usermap->ways;

    xmlNode* curr = nodeX->xmlChildrenNode;
    node* no = malloc(sizeof(node));
    way* wa = malloc(sizeof(way));
    bound* bo = malloc(sizeof(bound));
    curr = curr->next;
    while(curr != NULL)
    {
        if (curr->type == XML_ELEMENT_NODE) {
            if(xmlStrcmp(curr->name, xmlCharStrdup("bounds")) == 0)
            {
                usermap->bounds->minlat = atof((char*)xmlGetProp(curr, xmlCharStrdup("minlat")));
                usermap->bounds->maxlat = atof((char*)xmlGetProp(curr, xmlCharStrdup("maxlat")));
                usermap->bounds->maxlon = atof((char*)xmlGetProp(curr, xmlCharStrdup("maxlon")));
                usermap->bounds->minlon = atof((char*)xmlGetProp(curr, xmlCharStrdup("minlon")));

            }
             if(xmlStrcmp(curr->name,  xmlCharStrdup("node")) == 0){

                no = malloc(sizeof(node));
        		no->id = atoll((char*)xmlGetProp(curr, xmlCharStrdup("id")));
        		no->lat = atof((char*)xmlGetProp(curr, xmlCharStrdup("lat")));
        		no->longi = atof((char*)xmlGetProp(curr, xmlCharStrdup("lon")));
                 printf("Erreur 2");
                if(!xmlStrcmp(xmlGetProp(curr, xmlCharStrdup("visible")), xmlCharStrdup("true")))
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
         	if(xmlStrcmp(curr->name, xmlCharStrdup("way")) == 0){

        		wa = malloc(sizeof(way));
                wa->id = malloc(sizeof(int64_t));
        		wa->id = atoll((char*)xmlGetProp(curr, xmlCharStrdup("id")));
                if(!xmlStrcmp(xmlGetProp(curr, xmlCharStrdup("visible")), xmlCharStrdup("true")))
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
        				if(xmlStrcmp(nd->name, xmlCharStrdup("nd")) ==0)
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
        				if(xmlStrcmp(nd->name, xmlCharStrdup("nd")) == 0)
        				{
    	    				
    	    				wa->nodes[i] = getNodeById(atoll((char*)xmlGetProp(nd, xmlCharStrdup("ref"))),rootN);
	        				
	        				
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
            if(xmlStrcmp(curr->name, "node") == 0){

        		no = malloc(sizeof(node));
        		no->id = atoll(xmlGetProp(curr, "id"));
        		no->lat = atof(xmlGetProp(curr, "lat"));
        		no->longi = atof(xmlGetProp(curr, "lon"));
        		no->visible = 1;

        		//debugNode(no);
        		insertNode(no, rootN);
         	}
         	if(xmlStrcmp(curr->name, "way") == 0){

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

int parse(char* filename, map* usermap)
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
	parsetoabr(root_element,usermap);

	xmlFreeDoc(doc);
	xmlCleanupParser();

	printf("\n Fin \n");
	return 0;
}
