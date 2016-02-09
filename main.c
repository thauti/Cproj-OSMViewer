#include <stdio.h>
#include <stdlib.h>

#include "osm.h"
#include "parse.h"

int main(int argc, char* argv)
{
	char* filename = "example/map.osm";
	printf("Ouverture de %s \n", filename);

	tree_node* abr = malloc(sizeof(tree_node));
	
	if(parse(filename, abr) != 0)
	{
		fprintf(stderr, "Erreur à l'ouverture de  %s \n", filename);
	}

	printf("# %p <- \n",getNoeudbyId(3257359455, abr));

	return 0;
}