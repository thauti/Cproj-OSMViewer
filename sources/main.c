#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>

#include "osm.h"
#include "window.h"
#include "parse.h"


int main(int argc, char** argv)
{
	GtkApplication *app;
	map* usermap = malloc(sizeof(map));
	int status;
	//printf("Ouverture de %s \n", argv[1]);
	//printf("%p", usermap);
	if(argc < 2)
	{
		printf("Erreur : \n Usage : ./bin/osm <Fichier OSM>\n");
		exit(1);
	}
	int t = strlen(argv[1]);
	
	if(argv[1][t-1] != 'm' || argv[1][t-2] != 's'|| argv[1][t-3] != 'o'){
		printf("Erreur : \n Le fichier n'est pas un fichier .osm\n");
		exit(1);
	}
 	app = gtk_application_new ("org.gtk.osm", G_APPLICATION_FLAGS_NONE);
  	g_signal_connect (app, "activate", G_CALLBACK (create_window), usermap);

	//tree_node* abr = malloc(sizeof(tree_node));
	//tree_way* abr3 = malloc(sizeof(tree_way));
	


	if(parse(argv[1], usermap) != 0)
	{
		fprintf(stderr, "Erreur à l'ouverture de  %s \n", argv[1]);
	}
	/*int continuer=1;
    relationlist* temp;
    temp = usermap->relations;
    int s = 0;
    do
    {
     		s=s+1;
            printf("r");
            temp=temp->next;
    }while(temp!=NULL);*/
	//printf("# %p <- \n",getNodeById(3257359455, abr));
	//printf("# %p <- \n",getWayById(4039117, abr3));
	

	status = g_application_run (G_APPLICATION (app), 0, NULL);
	g_object_unref (app);
	g_print("Au revoir ! \n");
	return status;
}
