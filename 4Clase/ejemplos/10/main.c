#include <gtk/gtk.h>

static gboolean funcion_progreso (gpointer data)
{
	gdouble fraccion;

	fraccion = gtk_progress_bar_get_fraction((GtkProgressBar *) data);

	fraccion+= 0.01;

	if (fraccion > 1.0)
		fraccion = 0.0;

	gtk_progress_bar_set_fraction((GtkProgressBar*) data, fraccion);
}

int main (int argc, char * argv[])
{
	GtkWidget * ventana;
	GtkWidget * progreso;

	gtk_init(&argc, &argv);

	ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	progreso = gtk_progress_bar_new();

	gtk_container_add((GtkContainer *) ventana, progreso);

	g_timeout_add(100, funcion_progreso, progreso);

	gtk_widget_show_all(ventana);
	gtk_main();
}
