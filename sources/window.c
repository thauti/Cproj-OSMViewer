#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <cairo.h>
#include <math.h>
#include "osm.h"
#include "parse.h"
#include "window.h"

#define PI 3.141

#define DEG2RAD(DEG) ((DEG)*((PI)/(180.0)))
#define deg2rad(d) (((d)*M_PI)/180)
#define rad2deg(d) (((d)*180)/M_PI)

void dessiner_abr_route(GtkWidget* widget, cairo_t *cr,map* map, tree_way* t, bound* b, relationlist* r)
{

  //  g_print("%f \n", b->minlat);
//    g_print("%f \n", b->minlon);
    double zoom = 1;
     double xmin =(256/PI)*zoom*(deg2rad(b->minlon)+PI);
     double ymin =(256/PI)*zoom*(PI-log(tan((PI/4) + (deg2rad(b->minlat)/2))));
    int i =0;
    if(t->w->visible){

        static const double def[] = {1.0};
        cairo_set_dash(cr, def,0, 0);
        switch(t->w->type_way)
        {
            case 1:
                cairo_set_line_width(cr, 2);  
                cairo_set_source_rgb(cr,0.72,0.71,0.66);
                break;
            case 2:
                cairo_set_line_width(cr, 4);  
                cairo_set_source_rgb(cr, 0.8, 0.8, 0.8);
                if(t->w->type_val == 9 ||t->w->type_val == 16){
                    cairo_set_line_width(cr, 10);  
                    cairo_set_source_rgb(cr, 0.8, 0.6, 0.6);
                }

                 if(t->w->type_val == 10){
                    cairo_set_line_width(cr, 10);  
                    cairo_set_source_rgb(cr, 0.89, 0.92, 0.49);
                }
                break;
            case 5:
                cairo_set_line_width(cr, 1);  
                cairo_set_source_rgb(cr, 0.6, 0.7, 0.8);
                break;
            default:
                cairo_set_line_width(cr, 1);  
                cairo_set_source_rgb(cr, 0.55, 0.55, 0.55);
                break;
        }
        if(t->w->type_val == 6)
        {
            static const double dashed2[] = {14.0, 6.0};
            cairo_set_dash(cr, dashed2, 2, 0);

            cairo_set_line_width(cr, 2);  
            cairo_set_source_rgb(cr, 0.60, 0.57, 0.56);
        }
        if(t->w->type_val == 19)
        {
            static const double dashed2[] = {10.0, 6.0};
            cairo_set_dash(cr, dashed2, 2, 0);
            cairo_set_line_width(cr, 1);  
            cairo_set_source_rgb(cr, 0.60, 0.20, 0.20);
        }
        if(t->w->type_way == 7)
        {
            if(map->opt_rail == 0)
                cairo_set_line_width(cr, 0);  
            
        }
       
                    double ratio = 800 / (PI*2);
                    double zoom = 1;
                
                    double xratio = (800/(b->maxlon-b->minlon));
                    
        for(i=0;i<t->w->nodes_size-1;i++)
        {
        if(t->w->nodes[t->w->nodes_size-2] != t->w->nodes[0]){
            if(t->w->type_way != 0){
                //g_print(" -> %f \n", t->w->nodes[i+1]->lat - b->minlat);
                if(t->w->visible == 1 ){
                    //cairo_line_to(cr, (t->w->nodes[i]->lat - b->minlat)*80000+100, (t->w->nodes[i]->longi - b->minlon)*80000-20);
                    
                    double x = (256/PI)*zoom*(deg2rad(t->w->nodes[i]->longi)+PI)-xmin;
                    double y = (256/PI)*zoom*(PI-log(tan((PI/4) + (deg2rad(t->w->nodes[i]->lat)/2))))-ymin;
                  
                   //g_print(" Xm : %f \n", x);
                    //g_print(" Ym : %f \n", y);

                    cairo_line_to(cr,(x*xratio+map->xdecal)*map->zoom,(y*xratio+600+map->ydecal)*map->zoom);
                    
                  //   g_print(" Xmx : %f \n", xratio+map->xdecal);
                  //  g_print(" Ymx : %f \n", y);
                }
            }
         }
        }
               
               // g_print("%d", t->w->type_way);
               
            

                cairo_stroke(cr);
    }
    if(t->w_gauche != NULL)
    {
        dessiner_abr_route(widget,cr,map, t->w_gauche,b,r);
    }
    if(t->w_droite != NULL){
        dessiner_abr_route(widget,cr,map, t->w_droite,b,r);
    }
}
////////////////////////////

void dessiner_abr(GtkWidget* widget, cairo_t *cr,map* map, tree_way* t, bound* b, relationlist* r)
{
        double zoom = 1;
        double xmin =(256/PI)*zoom*(deg2rad(b->minlon)+PI);
        double ymin =(256/PI)*zoom*(PI-log(tan((PI/4) + (deg2rad(b->minlat)/2))));
  //  g_print("%f \n", b->minlat);
//    g_print("%f \n", b->minlon);

    int i =0;
    if(t->w->visible){
        switch(t->w->type_way)
        {
            case 1:
                cairo_set_line_width(cr, 2);  
                cairo_set_source_rgb(cr,0.72,0.71,0.66);
                break;
            case 2:
                cairo_set_line_width(cr, 4);  
                cairo_set_source_rgb(cr, 0.8, 0.8, 0.8);
                break;
            case 5:
                cairo_set_line_width(cr, 1);  
                cairo_set_source_rgb(cr, 0.6, 0.7, 0.8);
                break;
            default:
                cairo_set_line_width(cr, 1);  
                cairo_set_source_rgb(cr, 0.55, 0.55, 0.55);
                break;
        }
       
                    double ratio = 800 / (PI*2);
                
                    double xratio = (800/(b->maxlon-b->minlon));
        for(i=0;i<t->w->nodes_size-1;i++)
        {
            if(t->w->nodes[t->w->nodes_size-2] == t->w->nodes[0]){
            if(t->w->type_way != 0){
                //g_print(" -> %f \n", t->w->nodes[i+1]->lat - b->minlat);
                if(t->w->visible == 1 ){
                    //cairo_line_to(cr, (t->w->nodes[i]->lat - b->minlat)*80000+100, (t->w->nodes[i]->longi - b->minlon)*80000-20);
                    

                    double x = (256/PI)*zoom*(deg2rad(t->w->nodes[i]->longi)+PI)-xmin;
                    double y = (256/PI)*zoom*(PI-log(tan((PI/4) + (deg2rad(t->w->nodes[i]->lat)/2))))-ymin;
                  
                   //g_print(" Xm : %f \n", x);
                    //g_print(" Ym : %f \n", y);

                    cairo_line_to(cr,(x*xratio+map->xdecal)*map->zoom,(y*xratio+600+map->ydecal)*map->zoom);
                    
                  //   g_print(" Xmx : %f \n", xratio+map->xdecal);
                  //  g_print(" Ymx : %f \n", y);
                }
            }
         }
        }
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
                        else if(t->w->type_val == 13)
                        {
                            cairo_set_source_rgb(cr,0.73,0.82,0.49);
                        }
                        else if(t->w->type_val == 6)
                        {
                            cairo_set_source_rgb(cr,0.82,0.81,0.76);
                        }
                        else if(t->w->type_val == 7)
                        {
                            cairo_set_source_rgb(cr,0.60,0.60,0.60);
                        }
                        else
                        {
                           cairo_set_source_rgb(cr,0.88,0.87,0.82);
                        }
                        break;
                    case 4:
                        if(t->w->type_val == 5){
                            cairo_set_source_rgb(cr,0.73,0.82,0.49);
                        }
                        else if(t->w->type_val == 18){
                            cairo_set_source_rgb(cr,0.82,0.81,0.76);

                        }
                        else if(t->w->type_val == 20){
                            cairo_set_source_rgb(cr,0.82,0.81,0.76);

                        }else
                        {
                            cairo_set_source_rgb(cr,0.6,0.7,0.8);
                        }
                        break;
                    case 5:
                        cairo_set_source_rgb(cr,0.6,0.7,0.8);
                        break;
                    case 6:
                        cairo_set_source_rgb(cr,0.72,0.71,0.66);
                        break;
                    case 8:
                        if(t->w->type_val == 17){
                            cairo_set_source_rgb(cr,0.73,0.82,0.49);
                        }
                        else if(t->w->type_val == 21){
                            cairo_set_source_rgb(cr,0.73,0.82,0.49);

                        }
                        else{

                            cairo_set_source_rgb(cr,0.6,0.7,0.8);
                        }
                        break;


                }
                if(t->w->type_way != 0 &&(t->w->type_val!=7)&&(t->w->type_way!=6))
                {
                    cairo_fill(cr);
                }

                cairo_stroke(cr);
    }
    if(t->w_gauche != NULL)
    {
        dessiner_abr(widget,cr,map, t->w_gauche,b,r);
    }
    if(t->w_droite != NULL){
        dessiner_abr(widget,cr,map, t->w_droite,b,r);
    }
    relationlist* temp = r;
    int s = 0;
    do
    {
        s=s+1;
           // printf("r");
            temp=temp->next;

    }while(temp!=NULL);
   // printf("%d\n",s);
}
gboolean dessiner(GtkWidget* widget, cairo_t *cr, map* map, gpointer data)
{
    guint width, height;
    GdkRGBA color;
    width = gtk_widget_get_allocated_width (widget);
    height = gtk_widget_get_allocated_height (widget);
    cairo_surface_t* test;
    //static const double dashed3[] = {1};
   // cairo_set_dash(cr, dashed3, 1, 0);
    dessiner_abr(widget,cr,map, map->ways, map->bounds, map->relations);
    dessiner_abr_route(widget,cr,map, map->ways, map->bounds, map->relations);
    if(map->render_png == 1){
    test=cairo_get_target (cr);
    cairo_surface_write_to_png (test,
                           "output.png");
    map->render_png =0;
    }
   /* cairo_set_source_rgb(cr, 0.9, 0.9, 0.9);
    cairo_fill (cr);
    cairo_move_to(cr, 300, 70);  
    cairo_line_to(cr, 500, 70);
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairo_stroke(cr);  
  */    return FALSE;
}
void exit_window(GtkWidget* widget, gpointer* data)
{
    gtk_window_close(GTK_WINDOW(data));

}
gboolean railopt_event(GtkWidget* widget, env* e, gpointer* data)
{
    if( e->usermap->opt_rail)
        e->usermap->opt_rail = 0;
    else   
          e->usermap->opt_rail =1;
    gtk_widget_queue_draw(e->window);
    return FALSE;
}
gboolean export_event(GtkWidget* widget, env* e, gpointer* data)
{
    e->usermap->render_png =1;
    gtk_widget_queue_draw(e->window);
    return FALSE;
}
gboolean moving(GtkWidget* widget, GdkEventKey *event, map* map, gpointer data)
{
 switch (event->keyval)
  {
    case GDK_KEY_Left:
        map->xdecal += 30;
        break;
    case GDK_KEY_Right:
        map->xdecal -= 30;
        break;
    case GDK_KEY_Up:
        map->ydecal += 30;
        break;
    case GDK_KEY_Down:
        map->ydecal -= 30;
        break;
    case GDK_KEY_z:
        map->zoom +=0.5;
        break;
    case GDK_KEY_s:
        map->zoom = map->zoom*0.8;
        break;
    default:
      return FALSE; 
  }
    gtk_widget_queue_draw(widget);
}

void create_window(GtkApplication* app, map* user_map, gpointer user_data)
{
    GtkWidget *window;
    
    GtkWidget *box;

    GtkWidget *file;
    GtkWidget *export;
    GtkWidget *filemenu;
    GtkWidget *option;
    GtkWidget *optionmenu;
    GtkWidget *menu_bar;
    GtkWidget *quit;
    GtkWidget *railopt;
    GtkWidget* draw_area;
    env* e = malloc(sizeof(env));
    // Menu-Bar
    //     ->Menu
    window = gtk_application_window_new (app);
    e->usermap = user_map;
    e->window = window;
    draw_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(draw_area, 800,600);
    gtk_window_set_resizable (GTK_WINDOW(window), FALSE);
    gint height,width;
    gtk_window_get_size(GTK_WINDOW(window), &width, &height);
    gtk_window_set_title (GTK_WINDOW (window), "OpenStreetMap Renderer");
    gtk_window_set_default_size (GTK_WINDOW (window), width, height);
    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);

      g_print("%p \n", user_map->bounds);
    gint decal = 0;
    menu_bar = gtk_menu_bar_new();

    filemenu = gtk_menu_new();
    file = gtk_menu_item_new_with_label("Fichier");

    quit = gtk_menu_item_new_with_label("Quitter");
    export = gtk_menu_item_new_with_label("Exporter en PNG");

    optionmenu = gtk_menu_new();
    option = gtk_menu_item_new_with_label("Options");
    railopt = gtk_check_menu_item_new_with_label("Afficher les rails");
    gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM(railopt), 1);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), filemenu);

    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), export);

    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), quit);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), file);

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(option), optionmenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(optionmenu), railopt);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), option);


    g_signal_connect (G_OBJECT (draw_area), "draw",G_CALLBACK (dessiner), user_map);


    g_signal_connect (G_OBJECT (quit),"activate", G_CALLBACK (exit_window),window);
    g_signal_connect (G_OBJECT (export),"activate", G_CALLBACK (export_event),e);

    g_signal_connect (G_OBJECT (railopt),"activate", G_CALLBACK (railopt_event),e);

    g_signal_connect (G_OBJECT (window), "key_press_event", G_CALLBACK (moving), user_map);

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(box), menu_bar, FALSE, FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), box);
    gtk_container_add(GTK_CONTAINER(box), draw_area);

    gtk_widget_show_all (window);
}