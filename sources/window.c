#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <cairo.h>
#include <math.h>
#include "osm.h"

#include "window.h"

#define PI 3.14159265358979323846
#define DEG2RAD(DEG) ((DEG)*((PI)/(180.0)))

void dessiner_abr(GtkWidget* widget, cairo_t *cr, tree_way* t, bound* b)
{

  //  g_print("%f \n", b->minlat);
//    g_print("%f \n", b->minlon);

    int i =0;
    if(t->w->visible){
        if(t->w->type_way == 1)
        {
            cairo_set_line_width(cr, 2);  

            cairo_set_source_rgb(cr,0.72,0.71,0.66);

        }else if(t->w->type_way == 2){
            cairo_set_line_width(cr, 4);  
            cairo_set_source_rgb(cr, 0.8, 0.8, 0.8);
        }
        else if(t->w->type_way == 5)
        {
            cairo_set_line_width(cr, 1);  
           cairo_set_source_rgb(cr,0.6,0.7,0.8);
        }
        else
        {
            cairo_set_line_width(cr, 1);  
            cairo_set_source_rgb(cr, 0.55, 0.55, 0.55);
        }
        for(i=0;i<t->w->nodes_size-1;i++)
        {
            if(t->w->type_way != 0 && t->w->type_val != 0){
                //g_print(" -> %f \n", t->w->nodes[i+1]->lat - b->minlat);
                if(t->w->visible == 1 ){
                    //cairo_line_to(cr, (t->w->nodes[i]->lat - b->minlat)*80000+100, (t->w->nodes[i]->longi - b->minlon)*80000-20);
                    float ratio = 800 / (PI*2);
                    float zoom = 2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2;
                    float x = 800*((t->w->nodes[i]->longi+180)/360)*zoom;
                    float y = 600/2-log(tan((PI/4)+ DEG2RAD(t->w->nodes[i]->lat)/2))*ratio*zoom;

                    float x_min = 800*((b->minlon+180)/360)*zoom;
                    float y_min = 600/2-log(tan((PI/4)+ DEG2RAD(b->minlat)/2))*ratio*zoom;

                    float x_max = 800*((b->maxlon+180)/360)*zoom;
                    float y_max = 600/2-log(tan((PI/4)+ DEG2RAD(b->maxlat)/2))*ratio*zoom;

                   // g_print(" X : %f \n", x_min);
                    //g_print(" Y : %f \n", y_min);
                    
                   // g_print(" Xm : %f \n", x_max);
                    //g_print(" Ym : %f \n", y_max);

                    cairo_line_to(cr,x-x_min,y-y_min+600);
                }
            }
        }
        if(t->w->nodes[t->w->nodes_size-2] == t->w->nodes[0]){
               // g_print("%d", t->w->type_way);
                cairo_close_path(cr);
                cairo_stroke_preserve(cr);
                switch(t->w->type_way)
                {
                    case 0:
                        cairo_set_source_rgb(cr,0.0,0.0,0.0);
                        break;
                    case 1:
                        cairo_set_source_rgb(cr,0.82,0.81,0.76);
                        break;
                    case 2:
                        cairo_set_source_rgb(cr,0.90,0.88,0.88);
                        break;
                    case 3:
                        if(t->w->type_val == 3){
                            cairo_set_source_rgb(cr,0.6,0.7,0.8);
                        }
                        else if(t->w->type_val == 4)
                        {
                            cairo_set_source_rgb(cr,0.73,0.82,0.49);
                        }
                        else
                        {
                            cairo_set_source_rgb(cr,0.88,0.87,0.82);
  
                        }
                        break;
                    case 4:
                        if(t->w->type_val == 5){
                            cairo_set_source_rgb(cr,0.73,0.82,0.49);
                        }else
                        {
                            cairo_set_source_rgb(cr,0.6,0.7,0.8);
                        }
                        break;
                    case 5:
                        cairo_set_source_rgb(cr,0.6,0.7,0.8);
                        break;
                    case 6:
                        cairo_set_source_rgb(cr,0.6,0.7,0.8);
                        break;
                }
                if(t->w->type_way != 0)
                {
                    cairo_fill(cr);
                }
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
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(box), menu_bar, FALSE, FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), box);
    gtk_container_add(GTK_CONTAINER(box), draw_area);

  	gtk_widget_show_all (window);
}