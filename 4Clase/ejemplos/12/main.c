#include "concesionario.h"
#include <gtk/gtk.h>

struct concesionario *con;
int id;

static void algo(GtkButton *widget, gpointer dat)
{
	printf("entra aqui\n");
	gtk_widget_destroy((GtkWidget *)dat);
}

static void show_del_window(GtkButton *widget, gpointer data)
{
	GtkWidget *ventana;
	GtkWidget *boton;
	GtkWidget *caja;
	GtkWidget *combo;
	GList *opciones;
	int i, num_coches;
	const char *matricula;
	char *opcion_label;
	struct coche *c;

	ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	boton = gtk_button_new_with_label("Click me");
	caja = gtk_vbox_new(TRUE, 2);
	combo = gtk_combo_new();

	num_coches = curso_concesionario_attr_get_u32(con,
					   CURSO_CONCESIONARIO_ATTR_NUM_COCHES);

	printf("num_coches %d\n", num_coches);
	opciones = NULL;
	for (i = 0; i < num_coches; i++) {
		c = curso_concesionario_attr_get_coche(con,
						 CURSO_CONCESIONARIO_ATTR_COCHE,
						 i);

		matricula = curso_coche_attr_get_str(c,
						CURSO_COCHE_ATTR_MATRICULA);
		sprintf(opcion_label, "pos %d: %s", i, matricula);
		printf("se crean bien %s\n", opcion_label);
		opciones = g_list_append(opciones, (gpointer *)opcion_label);
	}

	gtk_combo_set_popdown_strings ((GtkCombo *) combo, opciones);

	gtk_box_pack_start ((GtkBox *) caja, combo, TRUE, TRUE, 2);
	gtk_box_pack_start ((GtkBox *) caja, boton, TRUE, TRUE, 2);

	gtk_container_add((GtkContainer *) ventana, caja);

	g_signal_connect((GObject *)ventana, "delete-event",
			 (GCallback)algo, ventana);

	printf("explota\n");
	gtk_widget_show_all(ventana);
	printf("aqui\n");
}

static void add_car(GtkButton *widget, gpointer data)
{
	GtkWidget **entry;
	struct coche *c;
	GtkWidget *entry_ptr_marca;
	GtkWidget *entry_ptr_matricula;
	const gchar *matricula, *marca;

	entry = (GtkWidget **)data;
	entry_ptr_marca = entry[0];
	entry_ptr_matricula = entry[1];

	printf("llega\n");

	marca = gtk_entry_get_text((GtkEntry *)entry_ptr_marca);
	matricula = gtk_entry_get_text((GtkEntry *)entry_ptr_matricula);

	c = curso_coche_alloc();
	if (c == NULL)
		return;

	curso_coche_attr_set_u32(c, CURSO_COCHE_ATTR_ID, id++);
	curso_coche_attr_set_str(c, CURSO_COCHE_ATTR_MATRICULA, matricula);
	curso_coche_attr_set_str(c, CURSO_COCHE_ATTR_MARCA, marca);

	curso_concesionario_attr_set_coche(con, CURSO_CONCESIONARIO_ATTR_COCHE,
					   c);

	printf ("Result: %d , %s, %s\n", id - 1, marca, matricula);
}

static void show_add_window(GtkButton *boton, gpointer data)
{
	GtkWidget *window;
	GtkWidget *button;
	GtkWidget *entry1, *entry2;
	GtkWidget *box;
	GtkWidget **entry;

	entry = calloc(1, 2 * sizeof(GtkWidget));

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	button = gtk_button_new_with_label("Add me");
	box = gtk_vbox_new(TRUE,2);
	entry1 = gtk_entry_new();
	entry2 = gtk_entry_new();

	entry[0] = entry1;
	entry[1] = entry2;

	gtk_box_pack_start ((GtkBox *) box, entry1, TRUE, TRUE, 2);
	gtk_box_pack_start ((GtkBox *) box, entry2, TRUE, TRUE, 2);

	gtk_box_pack_start ((GtkBox *) box, button, TRUE, TRUE, 2);

	gtk_container_add((GtkContainer *) window, box);

	g_signal_connect((GObject *) button, "clicked", (GCallback)add_car,
			 (gpointer) entry);

	g_signal_connect((GObject *)window, "delete-event",
			 (GCallback)algo, window);

	gtk_widget_show_all(window);
}

static void funcion_quit(GtkButton *boton, gpointer data)
{
	curso_concesionario_free(con);
	gtk_main_quit();
}

int main (int argc, char * argv[])
{
	GtkWidget * window;
	GtkWidget * button1;
	GtkWidget * button2;
	GtkWidget * vbox;

	con = curso_concesionario_alloc();
	if (con == NULL)
		return -1;

	curso_concesionario_attr_set_str(con, CURSO_CONCESIONARIO_ATTR_DUENO,
					 "Alvaro");

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	button1 = gtk_button_new_with_label("Añadir Coche");
	button2 = gtk_button_new_with_label("Borrar Coche");
	vbox = gtk_vbox_new(TRUE,5);

	gtk_window_set_title((GtkWindow *) window, "Concesionario");

	gtk_box_pack_start((GtkBox *) vbox, button1, TRUE, TRUE, 2);

	gtk_box_pack_start((GtkBox *) vbox, button2, TRUE, TRUE, 2);

	gtk_container_add((GtkContainer *) window, vbox);

	g_signal_connect((GObject *)button1, "clicked",
			 (GCallback)show_add_window, NULL);


	g_signal_connect((GObject *)button2, "clicked",
			 (GCallback)show_del_window, NULL);

	g_signal_connect((GObject *)window, "delete-event",
			 (GCallback)funcion_quit, NULL);

	gtk_widget_show_all(window);

	gtk_main();
	return 0;
}
