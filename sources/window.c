#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <cairo.h>
#include "osm.h"

gboolean dessiner(GtkWidget* widget, cairo_t *cr, gpointer data)
{
	guint width, height;
	GdkRGBA color;

  	width = gtk_widget_get_allocated_width (widget);
  	height = gtk_widget_get_allocated_height (widget);
  	cairo_arc (cr,
             width / 2.0, height / 2.0,
             MIN (width, height) / 2.0,
             0, 2 * G_PI);

  	gtk_style_context_get_color (gtk_widget_get_style_context (widget),
                               0,
                               &color);
  	gdk_cairo_set_source_rgba (cr, &color);

  	cairo_fill (cr);
  	return FALSE;
}
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

    GtkWidget* draw_area;

    // Menu-Bar
    //     ->Menu
 	window = gtk_application_window_new (app);
 	draw_area = gtk_drawing_area_new();
 	gtk_widget_set_size_request(draw_area, 640,480);
  	
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

 	g_signal_connect (G_OBJECT (draw_area), "draw",G_CALLBACK (dessiner), NULL);
    g_signal_connect (G_OBJECT (quit),"activate", G_CALLBACK (exit_window),window);
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(box), menu_bar, FALSE, FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), box);
    gtk_container_add(GTK_CONTAINER(box), draw_area);

  	gtk_widget_show_all (window);
}