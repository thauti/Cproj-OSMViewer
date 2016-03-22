#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
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
	char type_way; // 0: inconnue 1: Building 2: Route/highway 3: Landuse(Jardin) 4: Leisure 5:waterway 6:Amenity
	char type_val; 
	// 0:Inconnu 1:yes 2:no 3:bassin(landuse) 4:grass/garden 5:park 6:railways 7:residential 8:unclassified 9:primary 10:secondary
	//11: pedestrian 12: fountain
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

typedef struct bound_s
{
	float minlat;
	float minlon;
	float maxlat;
	float maxlon;
}bound;

typedef struct map_s
{
	GHashTable*  hashnode;
	tree_node* nodes;
	tree_way* ways;
	bound* bounds;
}map;

typedef struct way_nodraw_s
{
	int64_t way;
	struct way_nodraw_s* next;
}ways_nodraw;

typedef struct relation_s
{
	short type; // 0 : MultiPolygon
	way* ways;
	short* w_type;
	int size;
}relation;

typedef struct relationlist_s
{
	struct relation_s* curr;
	struct relationlist_s* next;
}relationlist;

void insertNode(node* no, tree_node* root);
node* getNodeById(int64_t id, tree_node* root);
void insertWay(way* no, tree_way* root);
way* getWayById(int64_t id, tree_way* root);
void addListRelation(relation* r, relationlist* rl);