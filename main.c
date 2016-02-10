#include <stdio.h>
#include <stdlib.h>

#include "osm.h"
#include "parse.h"

int main(int argc, char* argv)
{
	char* filename = "example/map.osm";
	printf("Ouverture de %s \n", filename);

	tree_node* abr = malloc(sizeof(tree_node));
	tree_way* abr3 = malloc(sizeof(tree_way));
	
	if(parse(filename, abr, abr3) != 0)
	{
		fprintf(stderr, "Erreur à l'ouverture de  %s \n", filename);
	}

	printf("# %p <- \n",getNodeById(3257359455, abr));
	printf("# %p <- \n",getWayById(4039117, abr3));

	return 0;
}