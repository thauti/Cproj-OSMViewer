#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#include "osm.h"
#include "parse.h"

void activate (GtkApplication* app,
          gpointer        user_data)
{
  GtkWidget *window;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);
  gtk_widget_show_all (window);
}
int main(int argc, char* argv)
{
	GtkApplication *app;
	 int status;
	char* filename = "example/map.osm";
	printf("Ouverture de %s \n", filename);

 app = gtk_application_new ("org.gtk.osm", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);

	tree_node* abr = malloc(sizeof(tree_node));
	tree_way* abr3 = malloc(sizeof(tree_way));
	
	if(parse(filename, abr, abr3) != 0)
	{
		fprintf(stderr, "Erreur à l'ouverture de  %s \n", filename);
	}
	printf("# %p <- \n",getNodeById(3257359455, abr));
	printf("# %p <- \n",getWayById(4039117, abr3));
	  status = g_application_run (G_APPLICATION (app), argc, argv);
	  g_object_unref (app);

	return 0;
}
