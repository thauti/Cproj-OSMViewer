#include <stdlib.h>
#include <stdio.h>

#include "osm.h"


void insertNode(node* no, tree_node* root)
{
	if(no != NULL)
	{
		if(root->n == NULL)
		{
			root->n = no;
			return;
		}
		node* nr = root->n;
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
				insertNode(no, root->n_gauche);
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
				insertNode(no, root->n_droite);
			}
		}
	}
}

node* getNodeById(int64_t id, tree_node* root)
{
	 if(root->n->id == id)
	 {
	 //	printf("-> Trouvé <-\n");
	 	return root->n;
	 }
	 else
	 {
	 	if(id < root->n->id)
	 	{
	 		if(root->n_gauche == NULL){
	 			return NULL;
	 		}
	 		return getNodeById(id, root->n_gauche);
	 	}
	 	if(id > root->n->id)
	 	{
	 		if(root->n_droite == NULL){
	 			return NULL;
	 		}
	 		return getNodeById(id, root->n_droite);
	 	}
	 }
}

void insertWay(way* no, tree_way* root)
{
	if(no != NULL)
	{
		if(root->w == NULL)
		{
			root->w = no;
			return;
		}
		way* nr = root->w;
		if(no->id < nr->id)
		{
			if(root->w_gauche == NULL)
			{
				root->w_gauche = malloc(sizeof(tree_node));
				root->w_gauche->w = no;
				root->w_gauche->w_gauche = NULL;
				root->w_gauche->w_droite = NULL;
			}
			else
			{
				insertWay(no, root->w_gauche);
			}
		}
		else
		{
			if(root->w_droite == NULL)
			{
				root->w_droite = malloc(sizeof(tree_node));
				root->w_droite->w = no;
				root->w_droite->w_gauche = NULL;
				root->w_droite->w_droite = NULL;

			}
			else
			{
				insertWay(no, root->w_droite);
			}
		}
	}
}

way* getWayById(int64_t id, tree_way* root)
{
	 if(root->w->id == id)
	 {
	 	printf("-> Trouvé <-");
	 	return root->w;
	 }
	 else
	 {
	 	if(id < root->w->id)
	 	{
	 		if(root->w_gauche == NULL){
	 			return NULL;
	 		}
	 		return getWayById(id, root->w_gauche);
	 	}
	 	if(id > root->w->id)
	 	{
	 		if(root->w_droite == NULL){
	 			return NULL;
	 		}
	 		return getWayById(id, root->w_droite);
	 	}
	 }
}
