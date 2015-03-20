#include <gtk/gtk.h>
#include <stdlib.h>

static void entry_Submit(GtkButton *button, gpointer data)
{
	GtkWidget **entry = (GtkWidget **)data;

	GtkWidget *entry_ptr_a = entry[0];
	GtkWidget *entry_ptr_s = entry[1];
	GtkWidget *entry_ptr_t = entry[2];
	GtkWidget *entry_ptr_v = entry[3];
	GtkWidget *entry_ptr_r = entry[4];

	const gchar *a, *s, *t, *v, *r;

	a = gtk_entry_get_text((GtkEntry *)entry_ptr_a);
	s = gtk_entry_get_text((GtkEntry *)entry_ptr_s);
	t = gtk_entry_get_text((GtkEntry *)entry_ptr_t);
	v = gtk_entry_get_text((GtkEntry *)entry_ptr_v);
	r = gtk_entry_get_text((GtkEntry *)entry_ptr_r);

	printf ("Result: %s , %s, %s, %s, %s\n", a, s, t, v, r);
}

int main (int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *button;
	GtkWidget *entry1, *entry2, *entry3, *entry4, *entry5;
	GtkWidget *box;
	GtkWidget **entry;

	entry = malloc(5 * sizeof(GtkWidget));

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	button = gtk_button_new_with_label("Click me");
	box = gtk_vbox_new(TRUE,2);
	entry1 = gtk_entry_new();
	entry2 = gtk_entry_new();
	entry3 = gtk_entry_new();
	entry4 = gtk_entry_new();
	entry5 = gtk_entry_new();

	entry[0] = entry1;
	entry[1] = entry2;
	entry[2] = entry3;
	entry[3] = entry4;
	entry[4] = entry5;

	gtk_box_pack_start ((GtkBox *) box, entry1, TRUE, TRUE, 2);
	gtk_box_pack_start ((GtkBox *) box, entry2, TRUE, TRUE, 2);
	gtk_box_pack_start ((GtkBox *) box, entry3, TRUE, TRUE, 2);
	gtk_box_pack_start ((GtkBox *) box, entry4, TRUE, TRUE, 2);
	gtk_box_pack_start ((GtkBox *) box, entry5, TRUE, TRUE, 2);

	gtk_box_pack_start ((GtkBox *) box, button, TRUE, TRUE, 2);

	gtk_container_add((GtkContainer *) window, box);

	g_signal_connect((GObject *) button, "clicked", (GCallback)entry_Submit,
			 (gpointer) entry);

	g_signal_connect((GObject *) window, "delete-event",
			 (GCallback) gtk_main_quit, NULL);

	gtk_widget_show_all(window);

	gtk_main();
	return 0;
}
