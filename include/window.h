#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>



void dessiner_abr(GtkWidget* widget, cairo_t *cr, tree_way* t, bound* b);
gboolean dessiner(GtkWidget* widget, cairo_t *cr, map* map, gpointer data);
void exit_window(GtkWidget* widget, gpointer* data);
void create_window(GtkApplication* app, map* user_map, gpointer user_data);
