#include <stdlib.h>
#include <stdio.h>


typedef struct noeud_s
{
	int id;
	float lat;
	float longi;
	int visible;
}noeud;

typedef struct tree_node_s{
	noeud* n;
	struct tree_node_s* n_gauche;
	struct tree_node_s* n_droite;
}tree_node;

void insert(noeud* no, tree_node* root);
noeud* getNoeudbyId(int id, tree_node* root);