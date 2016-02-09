#include <stdlib.h>
#include <stdio.h>

#include "osm.h"


void insert(noeud* no, tree_node* root)
{
	if(no != NULL)
	{
		if(root->n == NULL)
		{
		//	printf("%d \n", no->id );
			root->n = no;
			return;
		}
		noeud* nr = root->n;
		if(no->id < nr->id)
		{
			if(root->n_gauche == NULL)
			{
				root->n_gauche = malloc(sizeof(tree_node));
				root->n_gauche->n = no;
				root->n_gauche->n_gauche = NULL;
				root->n_gauche->n_droite = NULL;
			}
			else
			{
				insert(no, root->n_gauche);
			}
		}
		else
		{
			if(root->n_droite == NULL)
			{
				root->n_droite = malloc(sizeof(tree_node));
				root->n_droite->n = no;
				root->n_droite->n_gauche = NULL;
				root->n_droite->n_droite = NULL;

			}
			else
			{
				insert(no, root->n_droite);
			}
		}
	}
}

noeud* getNoeudbyId(int64_t id, tree_node* root)
{
	 if(root->n->id == id)
	 {
	 	printf("-> Trouvé <-");
	 	return root->n;
	 }
	 else
	 {
	 	if(id < root->n->id)
	 	{
	 		if(root->n_gauche == NULL){
	 			return NULL;
	 		}
	 		return getNoeudbyId(id, root->n_gauche);
	 	}
	 	if(id > root->n->id)
	 	{
	 		if(root->n_droite == NULL){
	 			return NULL;
	 		}
	 		return getNoeudbyId(id, root->n_droite);
	 	}
	 }
}