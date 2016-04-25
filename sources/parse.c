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
void addrelation(relationlist* li, relation* r)
{
    if(li->curr == NULL)
    {
        li->curr = r;
    }
    else
    {
        if(li->next != NULL){
            addrelation(li->next, r);
        }
        else{
            li->next = malloc(sizeof(relationlist));
            li->next->curr = NULL;
            li->next->next = NULL;
            addrelation(li->next, r);
        }
    }
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
    usermap->xdecal = 0;
    usermap->ydecal = 0;
    usermap->zoom = 1;
    usermap->relations=malloc(sizeof(relationlist));
    usermap->relations->curr=NULL;
    usermap->relations->next=NULL;
    usermap->opt_rail = 1;
    usermap->render_png = 0;
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
            if(xmlStrcmp(curr->name, xmlCharStrdup("relation")) == 0)
            {
                relation* r = malloc(sizeof(relation));
                xmlNode * wd = curr->xmlChildrenNode;
                int wc = 0;
                while(wd != NULL)
                {
                    if(wd->type == XML_ELEMENT_NODE)
                    {
                        if(xmlStrcmp(wd->name, xmlCharStrdup("member")) == 0)
                        {
                            wc++;
                        }
                    }
                    wd =wd->next;
                }
                r->size = wc;
                r->ways = malloc(sizeof(way*)*wc);
                r->w_type = malloc(sizeof(short*)*wc);
                wd = curr->xmlChildrenNode;
                int tmp = 0;
                while(wd != NULL)
                {
                    if(wd->type == XML_ELEMENT_NODE)
                    {
                        if(xmlStrcmp(wd->name, xmlCharStrdup("member")) == 0)
                        {

                            //r->ways[tmp] = getWayById(atoll((char*)xmlGetProp(wd, xmlCharStrdup("ref"))), usermap->ways);
                            if(!xmlStrcmp(xmlGetProp(wd, xmlCharStrdup("role")), xmlCharStrdup("inner")))
                            {
                                r->w_type[tmp] = 0;
                            }
                            if(!xmlStrcmp(xmlGetProp(wd, xmlCharStrdup("role")), xmlCharStrdup("outer")))
                            {
                                r->w_type[tmp] = 1;
                            }
                        }
                    }
                    wd = wd->next;
                }
                addrelation(usermap->relations, r);
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
                                else if(xmlStrcmp(prop_value,  xmlCharStrdup("tertiary")) == 0)
                                {
                                    wa->type_val = 14;
                                }
                                else if(xmlStrcmp(prop_value,  xmlCharStrdup("motorway")) == 0)
                                {
                                    wa->type_val = 16;
                                }
                                else if(xmlStrcmp(prop_value,  xmlCharStrdup("footway")) == 0)
                                {
                                    wa->type_val = 19;
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
                            if(xmlStrcmp(prop,  xmlCharStrdup("railway")) == 0)
                            {
                                wa->type_way = 7;
                                wa->type_val = 6;
                            }
                            if(xmlStrcmp(prop,  xmlCharStrdup("landuse")) == 0)
                            {
                                wa->type_way = 3;
                                if(xmlStrcmp(prop_value,  xmlCharStrdup("basin")) == 0)
                                {
                                    wa->type_val = 3;
                                }
                                else if(xmlStrcmp(prop_value,  xmlCharStrdup("railway")) == 0 || xmlStrcmp(prop_value,  xmlCharStrdup("construction")) == 0)
                                {
                                    wa->type_val = 6;
                                }
                                else if(xmlStrcmp(prop_value,  xmlCharStrdup("residential")) == 0)
                                {
                                    wa->type_val = 7;

                                }
                                 else if(xmlStrcmp(prop_value,  xmlCharStrdup("grass")) == 0)
                                {
                                    wa->type_val = 13;

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
                                if(xmlStrcmp(prop_value,  xmlCharStrdup("bandstand")) == 0)
                                {
                                    wa->type_val = 18;
                                }
                                if(xmlStrcmp(prop_value,  xmlCharStrdup("marina")) == 0)
                                {
                                    wa->type_val = 20;
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
                             if(strcmp(prop, "natural") == 0)
                            {
                                wa->type_way = 8;
                                if(strcmp(prop_value, "water") == 0)
                                {
                                    wa->type_val = 15;
                                }
                                if(strcmp(prop_value, "wood") == 0)
                                {
                                    wa->type_val = 17;
                                }
                                if(strcmp(prop_value, "tree_row") == 0)
                                {
                                    wa->type_val = 21;
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

}

int parse(char* filename, map* usermap)
{

	LIBXML_TEST_VERSION
	xmlDocPtr doc;
	xmlNode *root_element;
    printf("ouverture de %s\n", filename);
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
