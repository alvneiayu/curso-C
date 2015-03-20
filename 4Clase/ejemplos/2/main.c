#include <gtk/gtk.h>

int main (int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *button;
	GtkWidget *label;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	button = gtk_button_new();
	label = gtk_label_new("LABEL");

	gtk_window_set_title((GtkWindow *) window, "WINDOW");
	gtk_container_add ((GtkContainer *) window, button);
	gtk_container_add ((GtkContainer *) button, label);

	gtk_widget_show(window);
	gtk_widget_show(button);
	gtk_widget_show(label);

	gtk_main();
}
