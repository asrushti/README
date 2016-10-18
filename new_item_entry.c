#include <gtk/gtk.h>

static void activate(GtkApplication *app, gpointer data){
	GtkWidget *window, *item_entry_grid;
	GtkWidget *label_item_title, *label_item_name, *label_item_code, *label_item_group, *label_item_category, *label_item_unit, *label_item_vat, *label_item_closing_qty1, *label_item_closing_qty2, *label_item_closing_rate1, *label_item_closing_rate2;
	GtkWidget *txt_item_name, *txt_item_code, *txt_item_unit, *txt_item_vat;
	GtkWidget *combo_item_group, *combo_item_category; 
	GtkWidget *btn_item_submit;
	
	/*Create and define all the window attributes.*/
	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "ITEM CREATION");
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	
	/*Create the box*/
	item_entry_grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(window), item_entry_grid);
	
	/*This is the label which displays the title on the page.*/
	label_item_title = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_item_title), "<u><b><big>ITEM CREATION</big></b></u>\n");
	gtk_grid_attach(GTK_GRID(item_entry_grid), label_item_title , 0, 0, 2, 1);
	
	/*Create instances of all the labels and put them in the grid at their respective places.*/
	label_item_name = gtk_label_new(NULL);
	gtk_label_set_markup_with_mnemonic(GTK_LABEL(label_item_name), "<big>Item _Name : </big>");
	gtk_widget_set_halign(label_item_name, GTK_ALIGN_START);
	
	label_item_code = gtk_label_new(NULL);
	gtk_label_set_markup_with_mnemonic(GTK_LABEL(label_item_code), "<big>_Item Code : </big>");
	gtk_widget_set_halign(label_item_code, GTK_ALIGN_START);
	
	label_item_group = gtk_label_new(NULL);
	gtk_label_set_markup_with_mnemonic(GTK_LABEL(label_item_group), "<big>_Group : </big>");
	gtk_widget_set_halign(label_item_group, GTK_ALIGN_START);	
	
	label_item_category = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_item_category), "<big>Category : </big>");
	gtk_widget_set_halign(label_item_category, GTK_ALIGN_START);
	
	label_item_unit = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_item_unit), "<big>Unit of Measure : </big>");
	gtk_widget_set_halign(label_item_unit, GTK_ALIGN_START);
		
	label_item_vat = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_item_vat), "<big>VAT % : </big>");
	gtk_widget_set_halign(label_item_vat, GTK_ALIGN_START);
		
	label_item_closing_rate1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_item_closing_rate1), "<big>Closing Rate : </big>");
	gtk_widget_set_halign(label_item_closing_rate1, GTK_ALIGN_START);
	label_item_closing_rate2 = gtk_label_new("Empty");
	gtk_widget_set_halign(label_item_closing_rate2, GTK_ALIGN_START);
	
	label_item_closing_qty1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_item_closing_qty1), "<big>Closing Balance : </big>");
	gtk_widget_set_halign(label_item_closing_qty1, GTK_ALIGN_START);
	label_item_closing_qty2 = gtk_label_new("Empty");
	gtk_widget_set_halign(label_item_closing_qty2, GTK_ALIGN_START);
	
	gtk_grid_attach(GTK_GRID(item_entry_grid), label_item_name, 1, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(item_entry_grid), label_item_code, 1, 4, 1, 1);
	gtk_grid_attach(GTK_GRID(item_entry_grid), label_item_group, 1, 6, 1, 1);
	gtk_grid_attach(GTK_GRID(item_entry_grid), label_item_category, 1, 8, 1, 1);
	gtk_grid_attach(GTK_GRID(item_entry_grid), label_item_unit, 1, 10, 1, 1);
	gtk_grid_attach(GTK_GRID(item_entry_grid), label_item_vat, 1, 12, 1, 1);
	gtk_grid_attach(GTK_GRID(item_entry_grid), label_item_closing_rate1, 1, 14, 1, 1);
	gtk_grid_attach(GTK_GRID(item_entry_grid), label_item_closing_rate2, 2, 14, 1, 1);
	gtk_grid_attach(GTK_GRID(item_entry_grid), label_item_closing_qty1, 1, 16, 1, 1);
	gtk_grid_attach(GTK_GRID(item_entry_grid), label_item_closing_qty2, 2, 16, 1, 1);
	
	/*Create text boxes and add them to the grid.*/
	txt_item_name = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(txt_item_name), 100);
	
	txt_item_code = gtk_entry_new();
	txt_item_unit = gtk_entry_new();
	
	txt_item_vat = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(txt_item_vat), 4);

	gtk_grid_attach(GTK_GRID(item_entry_grid), txt_item_name, 2, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(item_entry_grid), txt_item_code, 2, 4, 1, 1);
	gtk_grid_attach(GTK_GRID(item_entry_grid), txt_item_unit, 2, 10, 1, 1);
	gtk_grid_attach(GTK_GRID(item_entry_grid), txt_item_vat, 2, 12, 1, 1);	
	/*Create the dropdown menues for group and category fields.*/
	combo_item_group = gtk_combo_box_text_new();
	combo_item_category = gtk_combo_box_text_new();
	
	/*Add options to the list.*/
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo_item_group), NULL, "Option 1");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo_item_group), NULL, "Option 2");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo_item_group), NULL, "Option 3");
	
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo_item_category), NULL, "Option 1");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo_item_category), NULL, "Option 2");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo_item_category), NULL, "Option 3");
	
	/*Add the combo box to the grid.*/
	gtk_grid_attach(GTK_GRID(item_entry_grid), combo_item_group, 2, 6, 1, 1);
	gtk_grid_attach(GTK_GRID(item_entry_grid), combo_item_category, 2, 8, 1, 1);
	
	/*Create an instance of a button and add it to the grid.*/
	btn_item_submit = gtk_button_new_with_label("CREATE");
	
	gtk_grid_attach(GTK_GRID(item_entry_grid), btn_item_submit, 2, 18, 1, 1);
	/*Make all the components visible.*/
	gtk_widget_show_all(window);	
} 

int main(int argc, char *argv[]){
GtkApplication *app;
	int status;
	
	app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);
	
	g_signal_connect(app, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	return status;
}
