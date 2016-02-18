#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#include "window.h"

#include "osm.h"
#include "parse.h"


int main(int argc, char** argv)
{
	GtkApplication *app;
	int status;
	printf("Ouverture de %s \n", argv[1]);

 	app = gtk_application_new ("org.gtk.osm", G_APPLICATION_FLAGS_NONE);
  	g_signal_connect (app, "activate", G_CALLBACK (create_window), NULL);

	tree_node* abr = malloc(sizeof(tree_node));
	tree_way* abr3 = malloc(sizeof(tree_way));
	
	if(parse(argv[1], abr, abr3) != 0)
	{
		fprintf(stderr, "Erreur à l'ouverture de  %s \n", argv[1]);
	}
	//printf("# %p <- \n",getNodeById(3257359455, abr));
	//printf("# %p <- \n",getWayById(4039117, abr3));
	

	status = g_application_run (G_APPLICATION (app), 0, NULL);
	g_object_unref (app);
	g_print("Au revoir ! \n");
	return status;
}
