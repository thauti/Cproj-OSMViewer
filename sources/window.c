#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#include "osm.h"


void exit_window(GtkWidget* widget, gpointer* data)
{
	gtk_window_close(GTK_WINDOW(data));

}
void create_window(GtkApplication* app, gpointer user_data)
{
 	GtkWidget *window;
 	
 	GtkWidget *box;

    GtkWidget *file;
    GtkWidget *filemenu;
    GtkWidget *menu_bar;
    GtkWidget *open;
    GtkWidget *quit;

    // Menu-Bar
    //     ->Menu
 	window = gtk_application_window_new (app);
 	
  	gtk_window_set_title (GTK_WINDOW (window), "OpenStreetMap Renderer");
  	gtk_window_set_default_size (GTK_WINDOW (window), 640, 480);
  	gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);


 	menu_bar = gtk_menu_bar_new();

    filemenu = gtk_menu_new();
    file = gtk_menu_item_new_with_label("Fichier");
    open = gtk_menu_item_new_with_label("Ouvrir");
    quit = gtk_menu_item_new_with_label("Quitter");
    
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), filemenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), open);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), quit);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), file);

    g_signal_connect (G_OBJECT (quit),"activate", G_CALLBACK (exit_window),window);
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(box), menu_bar, FALSE, FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), box);

  	gtk_widget_show_all (window);
}