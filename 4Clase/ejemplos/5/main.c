#include <gtk/gtk.h>

void funcion1 (GtkButton * boton, gpointer data);
void funcion2 (GtkButton * boton, gpointer data);
void cerrar_window (GtkWidget * widget,gpointer data);


void cerrar_window (GtkWidget * widget,gpointer data)
{
	gtk_widget_destroy((GtkWidget *) data);
}


void funcion1 (GtkButton * boton, gpointer data)
{
	GtkWidget * window1;
	GtkWidget * button1;

	window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	button1 = gtk_button_new_with_label("Cerrar window");

	gtk_window_set_title((GtkWindow *) window1, "Nueva ventana");

	gtk_container_add((GtkContainer *) window1, button1);

	g_signal_connect((GObject *) button1, "clicked",
			 (GCallback) cerrar_window, (gpointer) window1);

	gtk_widget_show_all(window1);
}

void funcion2 (GtkButton * boton, gpointer data)
{
	gtk_main_quit();
}

int main (int argc, char * argv[])
{
	GtkWidget * window;
	GtkWidget * button1;
	GtkWidget * boton2;
	GtkWidget * vbox;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	button1 = gtk_button_new_with_label("Nueva window");
	boton2 = gtk_button_new_with_label("Cerrar aplicacion");
	vbox = gtk_vbox_new(TRUE,5);

	gtk_window_set_title((GtkWindow *) window, "Ejemplo mas completo");

	gtk_box_pack_start((GtkBox *) vbox, button1, TRUE, TRUE, 2);

	gtk_box_pack_start((GtkBox *) vbox, boton2, TRUE, TRUE, 2);

	gtk_container_add((GtkContainer *) window, vbox);

	g_signal_connect((GObject *) button1, "clicked", (GCallback ) funcion1,
			 NULL);


	g_signal_connect((GObject *) boton2, "clicked", (GCallback) funcion2,
			 NULL);

	g_signal_connect((GObject *) window, "delete-event",
			 (GCallback) gtk_main_quit, NULL);

	gtk_widget_show_all(window);

	gtk_main();
	return 0;
}
