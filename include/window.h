#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

gboolean dessiner(GtkWidget* widget, cairo_t *cr, gpointer* data);
void exit_window(GtkWidget* widget, gpointer* data);
void create_window (GtkApplication* app, gpointer user_data);
