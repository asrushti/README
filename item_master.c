/*****************************************************************************
 * Copyright (C) Srushti Avinash Chaudhari
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/
 
#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"
#include "files.h"

void item_master_activate(GtkApplication *app, Window_grid *win_grid){
	GtkWidget *window, *item_master_grid;
	GtkWidget *label_title, *btn_add, *btn_update, *btn_view;
	GtkWidget *pad0, *pad1, *pad2, *pad3, *pad4, *pad5, *pad6, *pad7, *pad8, *pad9, *pad10, *pad11, *pad12, *pad13;
	int i = 0;
	
	/*Remove the previous grid and add a new grid to display a different view.*/
	gtk_container_remove(GTK_CONTAINER(win_grid->window), win_grid->grid);
	item_master_grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(win_grid->window), item_master_grid);
	win_grid->grid = item_master_grid;
	
	/*Set the current screen as the item master screen.*/
	win_grid->current_screen = MASTER;
	
	/*Create the padding labels*/
	pad0 = gtk_label_new("          ");
	gtk_grid_attach(GTK_GRID(item_master_grid), pad0, 0, 0, 3, 1);
	
	/*Create the title label and add it to the screen.*/
	label_title = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_title), "<b><big><u>Item Master</u></big></b>");
	gtk_grid_attach(GTK_GRID(item_master_grid), label_title, 0, 1, 3, 1);
	
	pad1 = gtk_label_new("          ");
	gtk_grid_attach(GTK_GRID(item_master_grid), pad1, 0, 2, 3, 1);
	
	/*Create indiviual buttons and add them to the screen along with padding for better display.*/
	btn_add = gtk_button_new_with_label("Add a new Item");
	pad2 = gtk_label_new("          ");
	gtk_grid_attach(GTK_GRID(item_master_grid), pad2, 0, 3, 1, 1);
	gtk_grid_attach(GTK_GRID(item_master_grid), btn_add, 1, 3, 1, 1);
	pad3 = gtk_label_new("          ");
	gtk_grid_attach(GTK_GRID(item_master_grid), pad3, 2, 3, 1, 1);
	g_signal_connect(btn_add, "clicked", G_CALLBACK(item_master_add), win_grid);
	
	pad4 = gtk_label_new("          ");
	gtk_grid_attach(GTK_GRID(item_master_grid), pad4, 0, 4, 3, 1);
	
	btn_update = gtk_button_new_with_label("Update");
	pad5 = gtk_label_new("          ");
	gtk_grid_attach(GTK_GRID(item_master_grid), pad5, 0, 5, 1, 1);
	gtk_grid_attach(GTK_GRID(item_master_grid), btn_update, 1, 5, 1, 1);
	pad6 = gtk_label_new("          ");
	gtk_grid_attach(GTK_GRID(item_master_grid), pad6, 2, 5, 1, 1);
	g_signal_connect(btn_update, "clicked", G_CALLBACK(item_master_update), win_grid);
	
	pad7 = gtk_label_new("          ");
	gtk_grid_attach(GTK_GRID(item_master_grid), pad7, 0, 6, 3, 1);
	
	btn_view = gtk_button_new_with_label("View");
	pad8 = gtk_label_new("          ");
	gtk_grid_attach(GTK_GRID(item_master_grid), pad8, 0, 7, 1, 1);
	gtk_grid_attach(GTK_GRID(item_master_grid), btn_view, 1, 7, 1, 1);
	pad9 = gtk_label_new("          ");
	gtk_grid_attach(GTK_GRID(item_master_grid), pad9, 2, 7, 1, 1);
	g_signal_connect(btn_view, "clicked", G_CALLBACK(item_master_view), win_grid);
	
	pad10 = gtk_label_new("         ");
	gtk_grid_attach(GTK_GRID(item_master_grid), pad10, 0, 8, 3, 1);
	
	pad13 = gtk_label_new("         ");
	gtk_grid_attach(GTK_GRID(item_master_grid), pad13, 0, 9, 3, 1);
	
	/*Return to the previous screen when ESC key is pressed*/
	g_signal_connect(win_grid->window, "key_press_event", G_CALLBACK(check_escape), win_grid);
	
	/*Make all window components visible*/
	gtk_widget_show_all(win_grid->window);
	return;
}

Item_master *item_master_add(GtkApplication *app, Window_grid *win_grid){
	GtkWidget *window, *item_entry_grid;
	GtkWidget *label_item_title, *label_item_name, *label_item_code, *label_item_group, *label_item_category, *label_item_unit, *label_item_vat, *label_item_closing_qty1, *label_item_closing_qty2, *label_sale_rate, *txt_sale_rate;
	GtkWidget *pad1, *pad2, *pad3, *pad4, *pad5, *pad6, *pad7, *pad8, *pad9, *pad10, *pad11;
	Item_master *item_master;
	
	item_master = (Item_master *)malloc(sizeof(Item_master));

	/*Remove the screen that was added to the container previously.*/
	if(win_grid->grid)
		gtk_container_remove(GTK_CONTAINER(win_grid->window), win_grid->grid);
	item_entry_grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(win_grid->window), item_entry_grid);
	win_grid->grid = item_entry_grid;
	
	pad1 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(item_entry_grid), pad1, 0, 0, 2, 1);
	
	/*This is the label which displays the title on the page.*/
	label_item_title = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_item_title), "<u><b><big>ITEM CREATION</big></b></u>\n");
	gtk_grid_attach(GTK_GRID(item_entry_grid), label_item_title , 0, 1, 2, 1);
	
	pad2 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(item_entry_grid), pad2, 0, 2, 2, 1);
	
	/*Create instances of all the labels and put them in the grid at their respective places.*/
	label_item_name = gtk_label_new(NULL);
	gtk_label_set_markup_with_mnemonic(GTK_LABEL(label_item_name), "<big>Item _Name : </big>");
	gtk_widget_set_halign(label_item_name, GTK_ALIGN_START);
	gtk_grid_attach(GTK_GRID(item_entry_grid), label_item_name, 0, 3, 1, 1);
	
	pad3 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(item_entry_grid), pad3, 0, 4, 2, 1);
	
	label_item_code = gtk_label_new(NULL);
	gtk_label_set_markup_with_mnemonic(GTK_LABEL(label_item_code), "<big>_Item Code : </big>");
	gtk_widget_set_halign(label_item_code, GTK_ALIGN_START);
	gtk_grid_attach(GTK_GRID(item_entry_grid), label_item_code, 0, 5, 1, 1);
	
	pad4 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(item_entry_grid), pad4, 0, 6, 2, 1);
	
	label_item_group = gtk_label_new(NULL);
	gtk_label_set_markup_with_mnemonic(GTK_LABEL(label_item_group), "<big>_Group : </big>");
	gtk_widget_set_halign(label_item_group, GTK_ALIGN_START);
	gtk_grid_attach(GTK_GRID(item_entry_grid), label_item_group, 0, 7, 1, 1);
	
	pad5 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(item_entry_grid), pad5, 0, 8, 2, 1);	
	
	label_item_category = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_item_category), "<big>Category : </big>");
	gtk_widget_set_halign(label_item_category, GTK_ALIGN_START);
	gtk_grid_attach(GTK_GRID(item_entry_grid), label_item_category, 0, 9, 1, 1);
	
	pad6 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(item_entry_grid), pad6, 0, 10, 2, 1);
	
	label_item_unit = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_item_unit), "<big>Unit of Measure : </big>");
	gtk_widget_set_halign(label_item_unit, GTK_ALIGN_START);
	gtk_grid_attach(GTK_GRID(item_entry_grid), label_item_unit, 0, 11, 1, 1);
	
	pad7 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(item_entry_grid), pad7, 0, 12, 2, 1);
		
	label_item_vat = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_item_vat), "<big>VAT % : </big>");
	gtk_widget_set_halign(label_item_vat, GTK_ALIGN_START);
	gtk_grid_attach(GTK_GRID(item_entry_grid), label_item_vat, 0, 13, 1, 1);
	
	pad8 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(item_entry_grid), pad8, 0, 14, 2, 1);
	
	label_sale_rate = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_sale_rate), "<big>Sale Rate : </big>");
	gtk_widget_set_halign(label_sale_rate, GTK_ALIGN_START);
	gtk_grid_attach(GTK_GRID(item_entry_grid), label_sale_rate, 0, 15, 1, 1);
	
	pad9 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(item_entry_grid), pad9, 0, 16, 2, 1);
	
	item_master->txt_sale_rate = gtk_entry_new();
	gtk_grid_attach(GTK_GRID(item_entry_grid), item_master->txt_sale_rate, 1, 15, 1, 1);
	
	
	pad11 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(item_entry_grid), pad11, 0, 20, 2, 1);
	
	/*Create text boxes and add them to the grid.*/
	item_master->txt_item_name = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(item_master->txt_item_name), 100);
	gtk_grid_attach(GTK_GRID(item_entry_grid), item_master->txt_item_name, 1, 3, 1, 1);
	
	item_master->txt_item_code = gtk_entry_new();
	gtk_grid_attach(GTK_GRID(item_entry_grid), item_master->txt_item_code, 1, 5, 1, 1);
	item_master->txt_item_unit = gtk_entry_new();
	gtk_grid_attach(GTK_GRID(item_entry_grid), item_master->txt_item_unit, 1, 11, 1, 1);
	
	item_master->txt_item_vat = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(item_master->txt_item_vat), 4);
	gtk_grid_attach(GTK_GRID(item_entry_grid), item_master->txt_item_vat, 1, 13, 1, 1);	
	
	/*Create the dropdown menues for group and category fields.*/
	item_master->combo_item_group = gtk_combo_box_text_new();
	item_master->combo_item_category = gtk_combo_box_text_new();
	
	/*Add the combo box to the grid.*/
	gtk_grid_attach(GTK_GRID(item_entry_grid), item_master->combo_item_group, 1, 7, 1, 1);
	gtk_grid_attach(GTK_GRID(item_entry_grid), item_master->combo_item_category, 1, 9, 1, 1);
	
	/*Call the function that populates the lists.*/
	item_master_populate(item_master);

	/*If this function has been called from update, then the item_update function will be invoed next.*/
	if(win_grid->current_screen == MASTER_SUB_UPDATE){
		item_master->btn_item_update = gtk_button_new_with_label("UPDATE");
		item_master->btn_item_submit = NULL;
		gtk_grid_attach(GTK_GRID(item_entry_grid), item_master->btn_item_update, 1, 21, 1, 1);
		g_signal_connect(item_master->btn_item_submit, "clicked", G_CALLBACK(item_master_display_fetch_data), item_master);
	}
	else{
		item_master->btn_item_update = NULL;
		item_master->btn_item_submit = gtk_button_new_with_label("CREATE");
		gtk_grid_attach(GTK_GRID(item_entry_grid), item_master->btn_item_submit, 1, 21, 1, 1);
		
		/*Call a function that retrieves the values filled in the report when the submit button is clicked*/
		g_signal_connect(item_master->btn_item_submit, "clicked", G_CALLBACK(item_master_create), item_master);
	}
	
	
	g_signal_connect(win_grid->window, "key_press_event", G_CALLBACK(check_escape), win_grid);
	win_grid->current_screen = MASTER_SUB;
	
	/*Make all the components visible.*/
	gtk_widget_show_all(win_grid->window);	
	
	return item_master;
}

/*A function to populate the group and category dropdowns for the item master.*/
void item_master_populate(Item_master *user_master){
	int i = 0, j = 0, count = 0;
	FILE *fp_grp, *fp_cat;
	int size_grp, size_cat;
	char *group, *category;
	
	fp_grp = fopen("data/GroupMaster.txt", "r");
	fp_cat = fopen("data/CategoryMaster.txt", "r");
	
	/*Read the no of charaters and the read only those no. of characters into variables.*/
	while(fread(&size_grp, sizeof(int), 1, fp_grp)){
		group = (char *)malloc(sizeof(char)*size_grp);
		fread(group, (sizeof(char) * size_grp), 1, fp_grp);
		group[size_grp] = '\0';
		gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(user_master->combo_item_group), NULL, group);
		free(group);
		group = NULL;
	}
	
	/*Populate the category dropdown.*/
	while(fread(&size_cat, sizeof(int), 1, fp_cat)){
		category = (char *)malloc(sizeof(char)*size_cat);
		fread(category, (sizeof(char) * size_cat), 1, fp_cat);
		category[size_cat] = '\0';
		gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(user_master->combo_item_category), NULL, category);
		free(category);
		category = NULL;
	}
	
	fclose(fp_grp);
	fclose(fp_cat);
	return;
}

void item_master_closing_fetch(GtkWidget *widget, Item_master *item_master){
	
}

/*Function that writes to a file when a new item is created.*/
void item_master_create(GtkWidget *widget, Item_master *item_master){
	Item_master_info info;
	
	info.name = gtk_entry_get_text((GtkEntry *)item_master->txt_item_name);
	info.code = gtk_entry_get_text((GtkEntry *)item_master->txt_item_code);
	info.unit = gtk_entry_get_text((GtkEntry *)item_master->txt_item_unit);
	info.vat = gtk_entry_get_text((GtkEntry *)item_master->txt_item_vat);
	info.sale_rate = gtk_entry_get_text((GtkEntry *)item_master->txt_sale_rate);
	info.group = gtk_combo_box_text_get_active_text((GtkComboBoxText *)item_master->combo_item_group);
	info.category = gtk_combo_box_text_get_active_text((GtkComboBoxText *)item_master->combo_item_category);
	
	write_item_master_info(&info);
	
	g_print("%s\n%s\n%s\n%s\n%s\n%s\n", info.name, info.code, info.unit, info.vat, info.group, info.category);
	
	/*Clear the data in all text boxes*/
	gtk_entry_set_text((GtkEntry *)item_master->txt_item_name, " ");
	gtk_entry_set_text((GtkEntry *)item_master->txt_item_code, " ");
	gtk_entry_set_text((GtkEntry *)item_master->txt_item_unit, " ");
	gtk_entry_set_text((GtkEntry *)item_master->txt_item_vat, " ");
	gtk_entry_set_text((GtkEntry *)item_master->txt_sale_rate, " ");

	return;
}


void item_master_view(GtkApplication *app, Window_grid *win_grid){
	GtkWidget *view_window, *window, *label_title, *grid;
	GtkWidget *label_name, *label_code, *label_group, *label_category, *label_unit, *label_sale_rate, *label_vat;
	GtkWidget *pad0, *pad1, *pad2, *pad3, *pad4, *pad5, *pad6, *pad7, *pad8, *pad9, *pad10, *pad11;
	FILE *fp;
	int i = 0, size_group, size_cat, size_name, j, size_unit;
	long long int code;
	float rate, vat;
	char *group, *category, *name, *unit, code_str[16], vat_str[20], rate_str[20], ch;
	Item_master_display *master[MAX_VIEW];
	
	/*Create another window in which all the records will be displayed.*/
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	/*Create a scrollable window and add it to the main window*/
	view_window = gtk_scrolled_window_new(NULL, NULL);
	/*Create a grid and add it to the window.*/
	grid = gtk_grid_new();
	
	/*Set the visibility of the scrollbars.*/
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(view_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
	
	gtk_container_add(GTK_CONTAINER(view_window), grid);
	gtk_container_add(GTK_CONTAINER(window), view_window);
	
	gtk_widget_show(view_window);
	gtk_window_set_default_size(GTK_WINDOW(window), 800, 500);
	
	
	pad0 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(grid), pad0, 0, 0, 12, 1);
	
	/*Create the title label and add it to the grid*/
	label_title = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_title), "<b><big>Item Master</big></b>");
	gtk_grid_attach(GTK_GRID(grid), label_title, 0, 1, 12, 1);
	
	pad1 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(grid), pad1, 0, 2, 12, 1);
	
	/*Create the labels and add them to the screen.*/
	label_code = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_code), "<b>Item Code</b>"); 
	gtk_grid_attach(GTK_GRID(grid), label_code, 0, 3, 1, 1);
	
	pad2 = gtk_label_new("     ");
	gtk_grid_attach(GTK_GRID(grid), pad2, 1, 3, 1, 1);
	
	label_name = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_name), "<b>Item Name</b>");
	gtk_grid_attach(GTK_GRID(grid), label_name, 2, 3, 1, 1);
	
	pad3 = gtk_label_new("     ");
	gtk_grid_attach(GTK_GRID(grid), pad3, 3, 3, 1, 1);
	
	label_group = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_group), "<b>Group</b>");
	gtk_grid_attach(GTK_GRID(grid), label_group, 4, 3, 1, 1);
	
	pad4 = gtk_label_new("     ");
	gtk_grid_attach(GTK_GRID(grid), pad4, 5, 3, 1, 1);
	
	label_category = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_category), "<b>Category</b>");
	gtk_grid_attach(GTK_GRID(grid), label_category, 6, 3, 1, 1);
	
	pad5 = gtk_label_new("     ");
	gtk_grid_attach(GTK_GRID(grid), pad5, 7, 3, 1, 1);
	
	label_unit = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_unit), "<b>Unit of Measure</b>");
	gtk_grid_attach(GTK_GRID(grid), label_unit, 8, 3, 1, 1);
	
	pad6 = gtk_label_new("     ");
	gtk_grid_attach(GTK_GRID(grid), pad6, 9, 3, 1, 1);
	
	label_sale_rate = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_sale_rate), "<b>Sale Rate </b>");
	gtk_grid_attach(GTK_GRID(grid), label_sale_rate, 10, 3, 1 ,1);
	
	pad7 = gtk_label_new("     ");
	gtk_grid_attach(GTK_GRID(grid), pad7, 11, 3, 1, 1);
	
	label_vat = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_vat), "<b>VAT %</b>");
	gtk_grid_attach(GTK_GRID(grid), label_vat, 12, 3, 1, 1);
	
	pad8 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(grid), pad8, 0, 4, 12, 1);
	
	pad9 = gtk_label_new("     ");
	gtk_grid_attach(GTK_GRID(grid), pad9, 13, 3, 1, 1);
		
	fp = fopen("data/ItemMaster.txt", "a+");
	
	j = 5;
	i = 0;
	
	while(fread(&code, sizeof(long long int), 1, fp)){
	
		master[i] = (Item_master_display *)malloc(sizeof(Item_master_display));
		
		master[i]->label_txt_code = gtk_label_new(NULL);
		sprintf(code_str, "%lld", code);
		gtk_label_set_text(GTK_LABEL(master[i]->label_txt_code), code_str);
		gtk_grid_attach(GTK_GRID(grid), master[i]->label_txt_code, 0, j, 1, 1);

		fread(&ch, sizeof(char), 1, fp);
			
		master[i]->label_txt_group = gtk_label_new(NULL);		
		fread(&size_group, sizeof(int), 1, fp);
		group = (char *)malloc(sizeof(char) * size_group + 1);
		fread(group, sizeof(char), size_group, fp);
		group[size_group] = '\0';
		gtk_label_set_text(GTK_LABEL(master[i]->label_txt_group), group);
		gtk_grid_attach(GTK_GRID(grid), master[i]->label_txt_group, 4, j, 1, 1);
		
		master[i]->label_txt_category = gtk_label_new(NULL);
		fread(&size_cat, sizeof(int),1, fp);
		category = (char *)malloc(sizeof(char) * size_cat + 1);
		fread(category, sizeof(char), size_cat, fp);
		category[size_cat] = '\0';
		gtk_label_set_text(GTK_LABEL(master[i]->label_txt_category), category);
		gtk_grid_attach(GTK_GRID(grid), master[i]->label_txt_category, 6, j, 1, 1);
		
		master[i]->label_txt_name = gtk_label_new(NULL);
		fread(&size_name, sizeof(int),1, fp);
		name = (char *)malloc(sizeof(char) * size_name + 1);
		fread(name, sizeof(char), size_name, fp);
		name[size_name] = '\0';
		gtk_label_set_text(GTK_LABEL(master[i]->label_txt_name), name);
		gtk_grid_attach(GTK_GRID(grid), master[i]->label_txt_name, 2, j, 1, 1);
	
		master[i]->label_txt_vat = gtk_label_new(NULL);
		fread(&vat, sizeof(float), 1, fp);
		sprintf(vat_str, "%f", vat);
		gtk_label_set_text(GTK_LABEL(master[i]->label_txt_vat), vat_str);
		gtk_grid_attach(GTK_GRID(grid), master[i]->label_txt_vat, 12, j, 1, 1);

		master[i]->label_txt_sale_rate = gtk_label_new(NULL);		
		fread(&rate, sizeof(float), 1, fp);
		sprintf(rate_str, "%f", rate);
		gtk_label_set_text(GTK_LABEL(master[i]->label_txt_sale_rate), rate_str);
		gtk_grid_attach(GTK_GRID(grid), master[i]->label_txt_sale_rate, 10, j, 1, 1);
		
		master[i]->label_txt_unit = gtk_label_new(NULL);
		fread(&size_unit, sizeof(int), 1, fp);
		unit = (char *)malloc(sizeof(char) * size_unit + 1);
		fread(unit, sizeof(char), size_unit, fp);
		unit[size_unit] = '\0';
		gtk_label_set_text(GTK_LABEL(master[i]->label_txt_unit), unit);
		gtk_grid_attach(GTK_GRID(grid), master[i]->label_txt_unit, 8, j, 1, 1);
		
		/*The view screen is also useful in the update and delete operations.
		 *Therefore, if the current screen is the item master update screen , then the selection buttons will also bo displayed in the grid.
		 */
		 
		
		if(win_grid->current_screen == MASTER_SUB_UPDATE){
			master[i]->btn_select = gtk_button_new_with_label("UPDATE");
			gtk_grid_attach(GTK_GRID(grid), master[i]->btn_select, 14, j, 1, 1);
			g_signal_connect(master[i]->btn_select, "clicked", G_CALLBACK(item_master_display_fetch_data), master[i]);
		}
		
		free(group);
		free(category);
		free(name);
		free(unit);
		
		i++;
		j++;
		
	}
	win_grid->current_screen = MASTER;
	fclose(fp);
	gtk_widget_show_all(view_window);
	gtk_widget_show_all(window);
	return;

}

/*This function is called whenever the user presses update button.*/
void item_master_update(GtkApplication *app, Window_grid *win_grid){
	GtkWidget *update_window, *view_window;
	
	win_grid->current_screen = MASTER_SUB_UPDATE;
	
	view_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	win_grid->window = view_window;
	item_master_view(win_grid->application, win_grid);
	
	return;
}

void item_master_display_fetch_data(GtkApplication *app, Item_master_display *master){
	GtkWidget *update_window, *update_grid, *btn_item_update;
	GtkWidget *label_title, *label_name1, *label_name2, *label_code1, *label_group1, *label_category1, *label_category2, *label_unit1, *label_unit2, *label_vat, *label_rate;
	GtkWidget *pad0, *pad1, *pad2, *pad3, *pad4, *pad5, *pad6, *pad7, *pad8, *pad9;
	float fetch_rate, fetch_vat;
	long long int fetch_code;
	Window_grid *win_grid;
	Item_master_update *item_master_update;
	
	item_master_update = (Item_master_update *)malloc(sizeof(Item_master_update));
	

	win_grid = (Window_grid *)malloc(sizeof(Window_grid));

	g_print("Inside Item Master display fetch data\n");
	
	update_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	update_grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(update_window), update_grid);
	
	win_grid->window = update_window;
	win_grid->grid = update_grid;
	win_grid->application = app;
	win_grid->current_screen = MASTER_SUB_UPDATE;
	
	pad0 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(update_grid), pad0, 0, 0, 2, 1);
	
	label_title = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_title), "<b><big>UPDATE RECORD</big></b>");
	gtk_grid_attach(GTK_GRID(update_grid), label_title, 0, 1, 2, 1);
	
	pad1 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(update_grid), pad1, 0, 2, 2, 1);
	
	label_code1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_code1), "<big>Code : </big>");
	gtk_grid_attach(GTK_GRID(update_grid), label_code1, 0, 3, 1, 1);
	
	item_master_update->label_code2 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(update_grid),item_master_update->label_code2, 1, 3, 1, 1);

	pad2 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(update_grid), pad2,  0, 4, 2, 1);
	
	label_name1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_name1), "<big>Name : </big>");
	gtk_grid_attach(GTK_GRID(update_grid), label_name1, 0, 5, 1, 1);
	
	label_name2 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(update_grid), label_name2, 1, 5, 1, 1);
	
	pad3 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(update_grid), pad3, 0, 6, 2, 1);
	
	label_group1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_group1), "<big>Group : </big>");
	gtk_grid_attach(GTK_GRID(update_grid), label_group1, 0, 7, 1, 1);
	
	item_master_update->label_group2 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(update_grid), item_master_update->label_group2, 1, 7, 1, 1);
	
	pad4 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(update_grid), pad4, 0, 8, 2, 1);
	
	label_category1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_category1), "<big>Category : </big>");
	gtk_grid_attach(GTK_GRID(update_grid), label_category1, 0, 9, 1, 1);
	
	label_category2 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(update_grid), label_category2, 1, 9, 1, 1);
	
	pad5 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(update_grid), pad5, 0, 10, 2, 1);
	
	label_unit1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_unit1), "<big>Unit : </big>");
	gtk_grid_attach(GTK_GRID(update_grid), label_unit1, 0, 11, 1, 1);
	
	label_unit2 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(update_grid), label_unit2, 1, 11, 1, 1);
	
	pad6 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(update_grid), pad6, 0, 12, 2, 1);
	
	label_vat = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_vat), "<big>VAT % : </big>");
	gtk_grid_attach(GTK_GRID(update_grid), label_vat, 0, 13, 1, 1);
	
	item_master_update->txt_vat = gtk_entry_new();
	gtk_grid_attach(GTK_GRID(update_grid), item_master_update->txt_vat, 1, 13, 1, 1);
	
	pad7 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(update_grid), pad7, 0, 14, 2, 1);

	label_rate = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_rate), "<big>MRP (Rs.) : </big>");
	gtk_grid_attach(GTK_GRID(update_grid), label_rate, 0, 15, 1, 1);
	
	item_master_update->txt_rate = gtk_entry_new();
	gtk_grid_attach(GTK_GRID(update_grid), item_master_update->txt_rate, 1, 15, 1, 1);
	
	pad8 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(update_grid), pad6, 0, 16, 2, 1);
	
	gtk_label_set_text((GtkLabel *)label_name2, gtk_label_get_text(GTK_LABEL(master->label_txt_name)));
	gtk_label_set_text((GtkLabel *)label_unit2, gtk_label_get_text(GTK_LABEL(master->label_txt_unit)));
	gtk_entry_set_text((GtkEntry *)item_master_update->txt_vat, gtk_label_get_text(GTK_LABEL(master->label_txt_vat)));
	gtk_entry_set_text((GtkEntry *)item_master_update->txt_rate, gtk_label_get_text(GTK_LABEL(master->label_txt_sale_rate)));
	gtk_label_set_text((GtkLabel *)item_master_update->label_code2, gtk_label_get_text(GTK_LABEL(master->label_txt_code)));
	gtk_label_set_text((GtkLabel *)item_master_update->label_group2, gtk_label_get_text(GTK_LABEL(master->label_txt_group)));
	gtk_label_set_text((GtkLabel *)label_category2, gtk_label_get_text(GTK_LABEL(master->label_txt_category)));
	
	pad9 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(update_grid), pad9, 0, 17, 2, 1);
	
	btn_item_update = gtk_button_new_with_label("UPDATE");
	gtk_grid_attach(GTK_GRID(update_grid), btn_item_update, 1, 18, 1, 1);
	
	g_signal_connect(btn_item_update, "clicked", G_CALLBACK(item_master_write_update), item_master_update);
	gtk_widget_show_all(update_window);
	return;	
}

