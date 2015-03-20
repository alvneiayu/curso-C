#include <gtk/gtk.h>

int main(int argc, char *argv[])
{
	GtkWidget * window;
	GtkWidget * toggle;
	GtkWidget * label;
	GtkWidget * box;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	toggle = gtk_toggle_button_new();
	label = gtk_label_new("TOGGLE");
	box = gtk_vbox_new(TRUE, 5);

	gtk_container_add((GtkContainer *)toggle, label);
	gtk_box_pack_start((GtkBox *)box, toggle, TRUE, TRUE, 3);
	gtk_container_add((GtkContainer *) window, box);

	gtk_widget_show_all(window);
	gtk_main();

	return 0;
}
