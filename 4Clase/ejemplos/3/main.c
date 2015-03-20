#include <gtk/gtk.h>
int main (int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *hbox;
	GtkWidget *button1;
	GtkWidget *button2;
	GtkWidget *button3;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	hbox = gtk_hbox_new(TRUE, 5);
	button1 = gtk_button_new_with_label("BOTON1");
	button2 = gtk_button_new_with_label("BOTON2");
	button3 = gtk_button_new_with_label("BOTON3");

	gtk_box_pack_start((GtkBox *)hbox, button1, TRUE, TRUE, 0);
	gtk_box_pack_start((GtkBox *)hbox, button2, TRUE, TRUE, 0);
	gtk_box_pack_start((GtkBox *)hbox, button3, TRUE, TRUE, 0);

	gtk_container_add((GtkContainer *)window, hbox);

	gtk_widget_show_all(window);
	gtk_main();

	return 0;
}
