#include <stdlib.h>
#include <stdio.h>

#include "osm.h"
/*
	Pour tester

int main()
{
	printf("Hello world \n");
	noeud* n = malloc(sizeof(noeud));
	n->id = 3;
	noeud* n1 = malloc(sizeof(noeud));
	n1->id = 5;
	noeud* n2 = malloc(sizeof(noeud));
	n2->id = 2;
	noeud* n3 = malloc(sizeof(noeud));
	n3->id = 1;
	noeud* n4 = malloc(sizeof(noeud));
	n4->id = 8;
	noeud* n5 = malloc(sizeof(noeud));
	n5->id = 0;
	noeud* n6 = malloc(sizeof(noeud));
	n6->id = 4;
	tree_node* root = malloc(sizeof(tree_node));

	insert(n,root);
	insert(n1,root);
	insert(n2,root);
	insert(n3,root);
	insert(n4,root);
	insert(n5,root);
	insert(n6,root);
	printf("%d " , getNoeudbyId(4, root));
	return 0;
}

*/

void insert(noeud* no, tree_node* root)
{
	if(no != NULL)
	{
		if(root->n == NULL)
		{
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
			}
			else
			{
				insert(no, root->n_droite);
			}
		}
	}
}

noeud* getNoeudbyId(int id, tree_node* root)
{
	 noeud* curr_n = root->n;
	 printf("-> %d \n", curr_n->id);
	 if(curr_n->id == id)
	 {
	 	return curr_n;
	 }
	 else
	 {
	 	if(id < curr_n->id)
	 	{
	 		if(root->n_gauche == NULL){
	 			return 0;
	 		}
	 		getNoeudbyId(id, root->n_gauche);
	 	}
	 	if(id > curr_n->id)
	 	{
	 		if(root->n_droite == NULL){
	 			return 0;
	 		}
	 		getNoeudbyId(id, root->n_droite);
	 	}
	 }
}