#include <stdio.h>
#include <stdlib.h>

#include <libxml/parser.h>
#include <libxml/tree.h>

void print_element_names(xmlNode* node)
{
	xmlNode* curr=NULL;
	for(curr = node;curr;curr=curr->next)
	{
		 if (curr->type == XML_ELEMENT_NODE) {
            printf("node type: Element, name: %s\n", curr->name);
        	printf("ID : %s\n", xmlGetProp(curr, "id"));
        }

        print_element_names(curr->children);
	}
}

int main(int argc, char* argv)
{
	LIBXML_TEST_VERSION
	xmlDocPtr doc;
	xmlNode *root_element;
	doc = xmlReadFile("example/map.osm", NULL, 0);
	if(doc==NULL)
	{
		fprintf(stderr, "Erreur %s\n", "example/map.osm");
		return 1;
	}
	root_element = xmlDocGetRootElement(doc);
	print_element_names(root_element);
	xmlFreeDoc(doc);
	xmlCleanupParser();

	printf("\n Fin \n");
	return 0;
}