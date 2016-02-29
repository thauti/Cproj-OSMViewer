#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <cairo.h>

#include "osm.h"

#include "window.h"

void dessiner_abr(GtkWidget* widget, cairo_t *cr, tree_way* t, bound* b)
{

  //  g_print("%f \n", b->minlat);
//    g_print("%f \n", b->minlon);

    cairo_set_source_rgb(cr, 0.9, 0.9, 0.9);
    int i =0;
    if(t->w->visible){
        cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
        for(i=0;i<t->w->nodes_size-1;i++)
        {
                //g_print(" -> %f \n", t->w->nodes[i+1]->lat - b->minlat);
                cairo_line_to(cr, (t->w->nodes[i]->lat - b->minlat)*80000+100, (t->w->nodes[i]->longi - b->minlon)*80000-20);
        }
        if(t->w->nodes[t->w->nodes_size-2] == t->w->nodes[0]){
               // g_print("%d", t->w->type_way);
                cairo_close_path(cr);
                cairo_set_source_rgb(cr,0.88,0.87,0.82);
                cairo_fill(cr);
            }
                cairo_stroke(cr);  
    }
    if(t->w_gauche != NULL)
    {
        dessiner_abr(widget,cr, t->w_gauche,b);
    }
    if(t->w_droite != NULL){
        dessiner_abr(widget,cr, t->w_droite,b);
    }
    
}
gboolean dessiner(GtkWidget* widget, cairo_t *cr, map* map, gpointer data)
{
	guint width, height;
	GdkRGBA color;
    width = gtk_widget_get_allocated_width (widget);
    height = gtk_widget_get_allocated_height (widget);
    //static const double dashed3[] = {1};
   // cairo_set_dash(cr, dashed3, 1, 0);
    dessiner_abr(widget,cr, map->ways, map->bounds);
   /* cairo_set_source_rgb(cr, 0.9, 0.9, 0.9);
    cairo_fill (cr);
	cairo_move_to(cr, 300, 70);  
	cairo_line_to(cr, 500, 70);
	cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
	cairo_stroke(cr);  
  */	return FALSE;
}
void exit_window(GtkWidget* widget, gpointer* data)
{
	gtk_window_close(GTK_WINDOW(data));

}
void create_window(GtkApplication* app, map* user_map, gpointer user_data)
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
 	gtk_widget_set_size_request(draw_area, 800,600);
  	gint height,width;
    gtk_window_get_size(GTK_WINDOW(window), &width, &height);
  	gtk_window_set_title (GTK_WINDOW (window), "OpenStreetMap Renderer");
  	gtk_window_set_default_size (GTK_WINDOW (window), width, height);
  	gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);


 	  g_print("%p \n", user_map->bounds);

    menu_bar = gtk_menu_bar_new();

    filemenu = gtk_menu_new();
    file = gtk_menu_item_new_with_label("Fichier");
    open = gtk_menu_item_new_with_label("Ouvrir");
    quit = gtk_menu_item_new_with_label("Quitter");
    
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), filemenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), open);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), quit);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), file);

 	  g_signal_connect (G_OBJECT (draw_area), "draw",G_CALLBACK (dessiner), user_map);
    g_signal_connect (G_OBJECT (quit),"activate", G_CALLBACK (exit_window),window);
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(box), menu_bar, FALSE, FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), box);
    gtk_container_add(GTK_CONTAINER(box), draw_area);

  	gtk_widget_show_all (window);
}