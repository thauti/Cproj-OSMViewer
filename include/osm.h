#include <stdlib.h>
#include <stdio.h>


typedef struct node_s
{
	int64_t id;
	float lat;
	float longi;
	char visible;
}node;

typedef struct way_s
{
	int64_t id;
	node** nodes;
	int nodes_size;
	char type_way;
	char* nom;
	char sensUnique;
	char visible;
}way;

typedef struct tree_way_s
{
	way* w;
	struct tree_way_s* w_gauche;
	struct tree_way_s* w_droite;
}tree_way;

typedef struct tree_node_s{
	node* n;
	struct tree_node_s* n_gauche;
	struct tree_node_s* n_droite;
}tree_node;

void insertNode(node* no, tree_node* root);
node* getNodeById(int64_t id, tree_node* root);
void insertWay(way* no, tree_way* root);
way* getWayById(int64_t id, tree_way* root);