#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <glib.h>

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

    usermap->nodes = malloc(sizeof(tree_node));
    usermap->nodes->n_gauche = NULL;
    usermap->nodes->n_droite = NULL;
    usermap->ways = malloc(sizeof(tree_way));
    usermap->ways->w_gauche = NULL;
    usermap->ways->w_droite = NULL;
    usermap->bounds  = malloc(sizeof(bound));
    usermap->hashnode = g_hash_table_new(g_int64_hash, g_int64_equal);
    /*
    tree_node* rootN = usermap->nodes;
    tree_way* rootW = usermap->ways;
    */
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
                if(!xmlStrcmp(xmlGetProp(curr, xmlCharStrdup("visible")), xmlCharStrdup("true")))
                {
                    no->visible = 1;
                }
                else
                {
                    no->visible = 0;
                }
        		//debugNode(no);
        		//insertNode(no, usermap->nodes);
         	    g_hash_table_insert(usermap->hashnode, (gpointer)&no->id,(gpointer)no);
            }
         	if(xmlStrcmp(curr->name, xmlCharStrdup("way")) == 0){

        		wa = malloc(sizeof(way));
        		wa->id = atoll((char*)xmlGetProp(curr, xmlCharStrdup("id")));
                if(!xmlStrcmp(xmlGetProp(curr, xmlCharStrdup("visible")), xmlCharStrdup("true")))
                {
                    wa->visible = 1;
                }
                else
                {
                    wa->visible = 0;
                }
        		insertWay(wa, usermap->ways);

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
                        if(xmlStrcmp(nd->name, xmlCharStrdup("tag"))== 0)
                        {
                            char* prop = (char*)xmlGetProp(nd, xmlCharStrdup("k"));
                            char* prop_value = (char*)xmlGetProp(nd, xmlCharStrdup("v"));
                            if(strcmp(prop, "building") == 0)
                            {
                                wa->type_way = 1;
                                if(strcmp(prop_value, "yes") == 0)
                                {
                                    wa->type_val = 1;
                                }
                                else
                                {
                                    wa->type_val = 0;
                                }

                            }
                            if(xmlStrcmp(prop, xmlCharStrdup("highway")) == 0) // TODO
                            {
                                wa->type_way = 2;
                                if(xmlStrcmp(prop_value, xmlCharStrdup("residential")) == 0)
                                {
                                    wa->type_val = 7;
                                }
                                else if(xmlStrcmp(prop_value,  xmlCharStrdup("unclassified")) == 0)
                                {
                                    wa->type_val = 8;
                                }
                                else if(xmlStrcmp(prop_value,  xmlCharStrdup("primary")) == 0)
                                {
                                    wa->type_val = 9;
                                }
                                else if(xmlStrcmp(prop_value,  xmlCharStrdup("secondary")) == 0)
                                {
                                    wa->type_val = 10;
                                }
                                else if(xmlStrcmp(prop_value,  xmlCharStrdup("pedestrian")) == 0)
                                {
                                    wa->type_val = 11;
                                }
                                else
                                {
                                    wa->type_val = 0;
                                }

                            }
                             if(xmlStrcmp(prop,  xmlCharStrdup("waterway")) == 0) // TODO
                            {
                                wa->type_way = 5;
                                wa->type_val = 99;

                            }
                            if(xmlStrcmp(prop,  xmlCharStrdup("landuse")) == 0)
                            {
                                wa->type_way = 3;
                                if(xmlStrcmp(prop_value,  xmlCharStrdup("basin")) == 0)
                                {
                                    wa->type_val = 3;
                                }
                                else if(xmlStrcmp(prop_value,  xmlCharStrdup("railways")) == 0 || xmlStrcmp(prop_value,  xmlCharStrdup("construction")) == 0)
                                {
                                    wa->type_val = 6;
                                }
                                else if(xmlStrcmp(prop_value,  xmlCharStrdup("residential")) == 0)
                                {
                                    wa->type_val = 7;

                                }
                                else
                                {
                                    wa->type_val = 4;
                                }

                            }
                            if(xmlStrcmp(prop,  xmlCharStrdup("leisure")) == 0)
                            {
                                wa->type_way = 4;
                                if(xmlStrcmp(prop_value,  xmlCharStrdup("park")) == 0)
                                {
                                    wa->type_val = 5;
                                }
                                else
                                {
                                    wa->type_val = 5;
                                }

                            }
                            if(strcmp(prop, "amenity") == 0)
                            {
                                wa->type_way = 6;
                                if(strcmp(prop_value, "fountain") == 0)
                                {
                                    wa->type_val = 12;
                                }
                                else
                                {
                                    wa->type_val = 0;
                                }

                            }
                        }
        			}
        			nd = nd->next;
        		}
        		nd = curr->xmlChildrenNode;
                wa->nodes = malloc(sizeof(tree_node*)*n_tag);
        		wa->nodes_size = n_tag+1;
        		int i =0;
        		while(nd != NULL)
        		{
        			if (nd->type == XML_ELEMENT_NODE) {
        				if(xmlStrcmp(nd->name, xmlCharStrdup("nd")) == 0)
        				{
    	    				
	        				//wa->nodes[i] = getNodeById(atoll(xmlCharStrdup(xmlGetProp(nd, xmlCharStrdup("ref")))),usermap->nodes);
                            int64_t *id = malloc(sizeof(int64_t));
                            *id =  atoll(xmlCharStrdup(xmlGetProp(nd, xmlCharStrdup("ref"))));
                            wa->nodes[i] = g_hash_table_lookup(usermap->hashnode, (gpointer) id);
	        				
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
