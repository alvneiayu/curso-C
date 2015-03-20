#include <gtk/gtk.h>

int main (int argc, char *argv[])
{
	GtkWidget *ventana;
	GtkWidget *boton;
	GtkWidget *entrada;
	GtkWidget *caja;
	GtkWidget *combo;
	GtkWidget *spinner;
	GtkAdjustment *ajuste;
	GtkWidget *sliderh;
	GtkWidget *sliderv;

	GList *opciones;

	gtk_init(&argc, &argv);

	ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	boton = gtk_button_new_with_label("Click me");
	caja = gtk_vbox_new(TRUE,2);
	entrada = gtk_entry_new();
	combo = gtk_combo_new();
	ajuste = (GtkAdjustment *) gtk_adjustment_new(1.0, -100.0, 100.0, 0.5,
						      10.0, 0.0);

	spinner = gtk_spin_button_new(ajuste, 1, 1);

	sliderh = gtk_hscale_new(ajuste);
	sliderv = gtk_vscale_new(ajuste);

	opciones = NULL;
	opciones = g_list_append(opciones, "Opcion 1");
	opciones = g_list_append(opciones, "Opcion 2");
	opciones = g_list_append(opciones, "Opcion 3");
	opciones = g_list_append(opciones, "Opcion 4");

	gtk_combo_set_popdown_strings ((GtkCombo *) combo, opciones);

	gtk_box_pack_start ((GtkBox *) caja, entrada, TRUE, TRUE, 2);
	gtk_box_pack_start ((GtkBox *) caja, combo, TRUE, TRUE, 2);
	gtk_box_pack_start ((GtkBox *) caja, spinner, TRUE, TRUE, 2);
	gtk_box_pack_start ((GtkBox *) caja, sliderh, TRUE, TRUE, 2);
	gtk_box_pack_start ((GtkBox *) caja, sliderv, TRUE, TRUE, 2);
	gtk_box_pack_start ((GtkBox *) caja, boton, TRUE, TRUE, 2);

	gtk_container_add((GtkContainer *) ventana, caja);

	gtk_widget_show_all(ventana);

	gtk_main();
	return 0;
}
