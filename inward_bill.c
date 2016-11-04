/*****************************************************************************
 * Copyright (C) Srushti Avinash Chaudhari asrushti19@gmail.com
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
#include <gdk/gdkkeysyms.h>
#include "main.h"
#include "files.h"
#include "inward.h"

void inward_bill_activate(GtkApplication *app, Window_grid *win_grid){
	GtkWidget *inward_grid;
	GtkWidget *label_title, *btn_create, *btn_view;
	GtkWidget *pad0, *pad1, *pad2, *pad3, *pad4, *pad5, *pad6, *pad7, *pad8, *pad9, *pad10;
	
	/*Remove the previously attached grid and set the grid and current screen.*/
	gtk_container_remove(GTK_CONTAINER(win_grid->window), win_grid->grid);
	inward_grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(win_grid->window), inward_grid);
	win_grid->grid = inward_grid;
	gtk_window_set_title(GTK_WINDOW(win_grid->window), "Bill it OONNNNN");
	win_grid->current_screen = MASTER;
	
	pad0 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(inward_grid), pad0, 0, 0, 6, 1);
	
	pad4 = gtk_label_new("      ");
	gtk_grid_attach(GTK_GRID(inward_grid), pad4, 0, 1, 2, 1);
	
	/*This is the label which displays the title on the page.*/
	label_title = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_title), "<u><b><big>INWARD BILL</big></b></u>\n");
	gtk_grid_attach(GTK_GRID(inward_grid), label_title , 1, 1, 4, 1);
	
	pad5 = gtk_label_new("      ");
	gtk_grid_attach(GTK_GRID(inward_grid), pad5, 5, 1, 1, 1);
	
	pad1 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(inward_grid), pad1, 0, 2, 5, 1);
	
	pad6 = gtk_label_new("      ");
	gtk_grid_attach(GTK_GRID(inward_grid), pad0, 0, 3, 2, 1);
	
	btn_create = gtk_button_new_with_label("CREATE");
	gtk_grid_attach(GTK_GRID(inward_grid), btn_create, 3, 3, 1, 1);
	g_signal_connect(btn_create, "clicked", G_CALLBACK(inward_bill_create), win_grid);
	
	pad7 = gtk_label_new("      ");
	gtk_grid_attach(GTK_GRID(inward_grid), pad7, 4, 3, 1, 1);
	
	pad2 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(inward_grid), pad2, 0, 4, 6, 1);
	
	pad8 = gtk_label_new("      ");
	gtk_grid_attach(GTK_GRID(inward_grid), pad8, 0, 5, 2, 1);
	
	btn_view = gtk_button_new_with_label("VIEW");
	gtk_grid_attach(GTK_GRID(inward_grid), btn_view, 3, 5, 1, 1);
	g_signal_connect(btn_view, "clicked", G_CALLBACK(inward_bill_view), win_grid);
	
	
	pad9 = gtk_label_new("      ");
	gtk_grid_attach(GTK_GRID(inward_grid), pad9, 4, 5, 1, 1);
		
	pad3 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(inward_grid), pad3, 0, 6, 3, 1);
	
	/*Return to the previous screen when ESC key is pressed*/
	g_signal_connect(win_grid->window, "key_press_event", G_CALLBACK(check_escape), win_grid);
	
	gtk_widget_show_all(win_grid->window);
	return;
}

void inward_bill_create(GtkWidget *widget, Window_grid *win_grid){
	GtkWidget *inward_bill_grid;
	GtkWidget *label_inward_title, *label_purchase_no, *label_supplier_ino, *label_party_name, *label_code, *label_item_name, *label_inward_qty, *label_inward_rate, *label_inward_amt, *label_inward_vat, *label_inward_total;
	GtkWidget *btn_inward_create;
	GtkWidget *pad0, *pad1, *pad2, *pad3, *pad4, *pad5, *pad6, *pad7, *pad8, *pad9, *pad10;
	Inward_bill *inward_bill;
	
	int j, i = 0;

	inward_bill = (Inward_bill *)malloc(sizeof(Inward_bill));
	
	/*Remove the screen that was added to the container previously and add a new grid which contains other components.*/
	gtk_container_remove(GTK_CONTAINER(win_grid->window), win_grid->grid);
	inward_bill_grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(win_grid->window), inward_bill_grid);
	win_grid->grid = inward_bill_grid;
			
	win_grid->current_screen = INWARD_SUB;
	
	/*Call the view function.*/
	item_master_view(win_grid->application, win_grid);
	
	pad0 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(inward_bill_grid), pad0, 0, 0, 12, 1);
	
	/*This is the label which displays the title on the page.*/
	label_inward_title = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_inward_title), "<u><b><big>INWARD BILL</big></b></u>\n");
	gtk_grid_attach(GTK_GRID(inward_bill_grid), label_inward_title , 0, 1, 12, 1);
	
	pad1 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(inward_bill_grid), pad1, 0, 2, 12, 1);
	
	/*Create instances of all the labels and put them in the grid at their respective places.*/
	label_purchase_no = gtk_label_new(NULL);
	gtk_label_set_markup_with_mnemonic(GTK_LABEL(label_purchase_no), "<big>Purchase No : </big>");
	gtk_grid_attach(GTK_GRID(inward_bill_grid), label_purchase_no, 0, 3, 1, 1);
	
	inward_bill->txt_purchase_no = gtk_entry_new();
	gtk_grid_attach(GTK_GRID(inward_bill_grid), inward_bill->txt_purchase_no, 1, 3, 1, 1);
	
	pad1 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(inward_bill_grid), pad1, 0, 4, 12, 1);
	
	label_supplier_ino = gtk_label_new(NULL);
	gtk_label_set_markup_with_mnemonic(GTK_LABEL(label_supplier_ino), "<big>Supplier Invoice No :</big>");
	gtk_grid_attach(GTK_GRID(inward_bill_grid), label_supplier_ino, 0, 5, 1, 1);
	
	inward_bill->txt_supplier_ino = gtk_entry_new();
	gtk_grid_attach(GTK_GRID(inward_bill_grid), inward_bill->txt_supplier_ino, 1, 5, 1, 1);
	
	pad2 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(inward_bill_grid), pad2, 0, 6, 12, 1);
	
	label_party_name = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_party_name), "<big>Party Name </big>");
	gtk_grid_attach(GTK_GRID(inward_bill_grid), label_party_name, 0, 7, 1, 1);
	
	inward_bill->txt_party_name = gtk_entry_new();
	gtk_grid_attach(GTK_GRID(inward_bill_grid), inward_bill->txt_party_name, 1, 7, 1, 1);
	
	pad3 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(inward_bill_grid), pad3, 0, 8, 12, 1);
	
	label_code = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_code), "<big>Item Code</big>");
	gtk_grid_attach(GTK_GRID(inward_bill_grid), label_code, 0, 9, 1, 1);
	
	label_inward_qty = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_inward_qty), "<big>Qty </big>");
	gtk_grid_attach(GTK_GRID(inward_bill_grid), label_inward_qty, 1, 9, 1, 1);
	
	pad5 = gtk_label_new("        ");
	gtk_grid_attach(GTK_GRID(inward_bill_grid), pad5, 2, 9, 1, 1);
		
	label_inward_rate = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_inward_rate), "<big>Rate  </big>");
	gtk_grid_attach(GTK_GRID(inward_bill_grid), label_inward_rate, 3, 9, 1, 1);
	
	pad6 = gtk_label_new("        ");
	gtk_grid_attach(GTK_GRID(inward_bill_grid), pad6, 4, 9, 1, 1);
	
	label_inward_vat = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_inward_vat), "<big>VAT %</big>");
	gtk_grid_attach(GTK_GRID(inward_bill_grid), label_inward_vat, 5, 9, 1, 1);
	
	pad8 = gtk_label_new("        ");
	gtk_grid_attach(GTK_GRID(inward_bill_grid), pad8, 6, 9, 1, 1);
	
	label_inward_amt = gtk_label_new("Empty");
	gtk_label_set_markup(GTK_LABEL(label_inward_amt), "<big>Amount</big>");
	gtk_grid_attach(GTK_GRID(inward_bill_grid), label_inward_amt, 7, 9, 1, 1);
	
	pad7 = gtk_label_new("        ");
	gtk_grid_attach(GTK_GRID(inward_bill_grid), pad7, 8, 9, 1, 1);
	
	label_item_name = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_item_name), "<big>Name of item </big>");
	gtk_grid_attach(GTK_GRID(inward_bill_grid), label_item_name, 9, 9, 2, 1);
	
	pad4 = gtk_label_new("        ");
	gtk_grid_attach(GTK_GRID(inward_bill_grid), pad4, 11, 9, 1, 1);
	
	pad8 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(inward_bill_grid), pad8, 0, 10, 12, 1);
	
	label_inward_total = gtk_label_new("Empty");
	gtk_label_set_markup(GTK_LABEL(label_inward_total), "<big>Total : </big>");
	gtk_grid_attach(GTK_GRID(inward_bill_grid), label_inward_total, 8, 26, 1, 1);
	
	inward_bill->label_txt_inward_total = gtk_label_new(NULL);
	gtk_label_set_text(GTK_LABEL(inward_bill->label_txt_inward_total), "0");
	gtk_grid_attach(GTK_GRID(inward_bill_grid), inward_bill->label_txt_inward_total, 10, 26, 1, 1);

	j = 11;
	while(i < MAX_INWARD){
		
		inward_bill->inward_new[i] = (Inward_new *)malloc(sizeof(Inward_new));
	
		inward_bill->inward_new[i]->combo_code = gtk_entry_new(); 
		gtk_grid_attach(GTK_GRID(inward_bill_grid), inward_bill->inward_new[i]->combo_code, 0, j, 1, 1);
		
		inward_bill->inward_new[i]->label_txt_item_name = gtk_label_new(NULL);
		inward_bill->inward_new[i]->txt_inward_qty = gtk_entry_new();
		inward_bill->inward_new[i]->txt_inward_rate = gtk_entry_new();
		inward_bill->inward_new[i]->label_txt_inward_vat = gtk_label_new(NULL);
		inward_bill->inward_new[i]->label_txt_inward_amt = gtk_label_new(NULL);
		
		gtk_grid_attach(GTK_GRID(inward_bill_grid), inward_bill->inward_new[i]->label_txt_item_name, 9, j, 2, 1);
		gtk_grid_attach(GTK_GRID(inward_bill_grid), inward_bill->inward_new[i]->txt_inward_qty, 1, j, 1, 1);
		gtk_grid_attach(GTK_GRID(inward_bill_grid), inward_bill->inward_new[i]->txt_inward_rate, 3, j, 1, 1);
		gtk_grid_attach(GTK_GRID(inward_bill_grid), inward_bill->inward_new[i]->label_txt_inward_vat, 5, j, 1, 1);
		gtk_grid_attach(GTK_GRID(inward_bill_grid), inward_bill->inward_new[i]->label_txt_inward_amt, 7, j, 1, 1);
		
		g_signal_connect(inward_bill->inward_new[i]->txt_inward_rate, "activate", G_CALLBACK(set_inward_values), inward_bill);
		i++;
		j++;

	}	
	
	j++;
	/*Create an instance of a button and add it to the grid.*/
	btn_inward_create = gtk_button_new_with_label("CREATE");
	gtk_grid_attach(GTK_GRID(inward_bill_grid), btn_inward_create, 10, j, 1, 1);
	g_signal_connect(btn_inward_create, "clicked", G_CALLBACK(write_inward_bill), inward_bill);
	
	/*Call a function to return to the main screen when the ESC key is pressed.*/
	g_signal_connect(win_grid->window, "key_press_event", G_CALLBACK(check_escape), win_grid);
	
	/*Make all the components visible.*/
	gtk_widget_show_all(win_grid->window);	
	return;
}

void set_inward_values(GtkWidget *widget, Inward_bill *inward_bill){
	FILE *fp;
	int size_name, size_group, size_cat, size_unit, i = 0;
	long long int code, code1;
	char ch, *group, *category, *name, *unit, vat_str[MAX_STR], amt_str[30], total_str[30], code_str[16];
	float vat, rate, rate1;
	long int qty;
	double total, amt, vat_amt;
	
	fp = fopen("ItemMaster.txt", "r");
	/*Simply set the values as  if the file could not be opened.*/
	if(!fp){
		gtk_label_set_text(GTK_LABEL(inward_bill->inward_new[i]->label_txt_item_name), "ERROR : FILE IS MISSING. PUT THE FILE IN PLACE OR RECORD DOES NOT EXIST");
		return;
	}
	
	while(inward_bill->inward_new[i]->txt_inward_rate != widget)
		i++;
	
	/*If the fields are not null, fetch all the values and perform the necessary computation.*/
	if(gtk_entry_get_text((GtkEntry*) inward_bill->inward_new[i]->combo_code)){
		
		code1 = atoll(gtk_entry_get_text((GtkEntry *)inward_bill->inward_new[i]->combo_code));
		
		total = atof(gtk_label_get_text((GtkLabel *)inward_bill->label_txt_inward_total));
		qty = atol(gtk_entry_get_text((GtkEntry *)inward_bill->inward_new[i]->txt_inward_qty));
		
		while(fread(&code, sizeof(long long int), 1, fp)){
		
			fread(&ch, sizeof(char), 1, fp);
		
			fread(&size_group, sizeof(int), 1, fp);
			group = (char *)malloc(sizeof(char) * size_group + 1);
			fread(group, sizeof(char), size_group, fp);
			group[size_group] = '\0';
		
			fread(&size_cat, sizeof(int), 1, fp);
			category = (char *)malloc(sizeof(char) * size_cat + 1);
			fread(category, sizeof(char), size_cat, fp);
			category[size_cat] = '\0';
		
			fread(&size_name, sizeof(int), 1, fp);
			name = (char *)malloc(sizeof(char) * size_name + 1);
			fread(name, sizeof(char), size_name, fp);
			name[size_name] = '\0';
		
			fread(&vat, sizeof(float), 1, fp);
			fread(&rate, sizeof(float), 1, fp);
		
			fread(&size_unit, sizeof(int), 1, fp);
			unit = (char *)malloc(sizeof(char) * size_unit + 1);
			unit[size_unit] = '\0';
			fread(unit, sizeof(char), size_unit, fp);
		
			if(code == code1){
				/*Set the name label*/
				gtk_label_set_text(GTK_LABEL(inward_bill->inward_new[i]->label_txt_item_name), name);
				/*Set the vat label*/
				sprintf(vat_str, "%f", vat);
				gtk_label_set_text(GTK_LABEL(inward_bill->inward_new[i]->label_txt_inward_vat), vat_str);
				/*compute the amount label*/
				qty = atol(gtk_entry_get_text((GtkEntry *)inward_bill->inward_new[i]->txt_inward_qty));
				rate1 = atof(gtk_entry_get_text((GtkEntry *)inward_bill->inward_new[i]->txt_inward_rate));
				amt = rate1 * qty;
				/*Compute the VAT AMOUNT*/
				vat_amt = (amt * vat)/100;
				amt += vat_amt;
				sprintf(amt_str, "%lf", amt);
				gtk_label_set_text(GTK_LABEL(inward_bill->inward_new[i]->label_txt_inward_amt), amt_str);
			
				/*Compute and set the total*/
				total += amt;
				sprintf(total_str, "%lf", total);
				gtk_label_set_text(GTK_LABEL(inward_bill->label_txt_inward_total), total_str);
			
				break;
			}
		
			free(group);
			free(category);
			free(unit);
			free(name);
		
			group = NULL;
			category = NULL;
			unit = NULL;
			name = NULL;
		}
	}
	
	fclose(fp);
	return;
}

void inward_bill_view(GtkWidget *widget, Window_grid *win_grid){
	GtkWidget *view_window, *label_title, *grid, *window;
	GtkWidget *label_purchase_no, *label_supplier_ino, *label_party_name, *label_name, *label_code, *label_purchase_rate, *label_vat, *label_amt, *label_qty, *label_total;
	GtkWidget *pad0, *pad1, *pad2, *pad3, *pad4, *pad5, *pad6, *pad7, *pad8, *pad9, *pad10, *pad11;
	Inward_view *inward_view;
	FILE *fp;
	char ch = 'c';
	int size_iname, size_pname, i, j, k;
	long long int code, purchase_no, supplier_ino;
	char *pname, *item_name, purchase_no_str[16], supplier_ino_str[16], amt_str[16], vat_str[12], rate_str[16], total_str[16], code_str[16], qty_str[12];
	float vat, rate;
	long int qty;
	double amt, total;
	
	inward_view = (Inward_view *)malloc(sizeof(Inward_view));
	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	
	/*Create a scrollable window and add it to the main window*/
	view_window = gtk_scrolled_window_new(NULL, NULL);
	/*Create a grid and add it to the window.*/
	grid = gtk_grid_new();
	
	/*Set the visibility of the scrollbars.*/
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(view_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
	
	/*Add the grid to the scrollable window and add the scrolled window to the main window*/
	gtk_container_add(GTK_CONTAINER(view_window), grid);
	gtk_container_add(GTK_CONTAINER(window), view_window);
	//win_grid->current_screen = INWARD_SUB;
	gtk_widget_show(view_window);
	gtk_window_set_default_size(GTK_WINDOW(window), 1500, 500);
	gtk_window_set_resizable(GTK_WINDOW(window), TRUE);
	
	pad0 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(grid), pad0, 0, 0, 19, 1);
	
	/*Create the title label and add it to the grid*/
	label_title = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_title), "<b><big>Purchase Register</big></b>");
	gtk_grid_attach(GTK_GRID(grid), label_title, 0, 1, 19, 1);
	
	pad1 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(grid), pad1, 0, 2, 19, 1);
	
	/*Create the labels and add them to the screen.*/
	label_purchase_no = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_purchase_no), "<b>Pruchase Bill No.</b>"); 
	gtk_grid_attach(GTK_GRID(grid), label_purchase_no, 0, 3, 1, 1);
	
	pad2 = gtk_label_new("        ");
	gtk_grid_attach(GTK_GRID(grid), pad2, 1, 3, 1, 1);
	
	label_supplier_ino = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_supplier_ino), "<b>Supplier Invioce NO.</b>");
	gtk_grid_attach(GTK_GRID(grid), label_supplier_ino, 2, 3, 1, 1);
	
	pad3 = gtk_label_new("       ");
	gtk_grid_attach(GTK_GRID(grid), pad3, 3, 3, 1, 1);
	
	label_party_name = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_party_name), "<b>Supplier name</b>");
	gtk_grid_attach(GTK_GRID(grid), label_party_name, 4, 3, 1, 1);
	
	pad4 = gtk_label_new("       ");
	gtk_grid_attach(GTK_GRID(grid), pad4, 5, 3, 1, 1);
	
	label_code = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_code), "<b>Item Code</b>");
	gtk_grid_attach(GTK_GRID(grid), label_code, 6, 3, 1, 1);
	
	pad5 = gtk_label_new("     ");
	gtk_grid_attach(GTK_GRID(grid), pad5, 7, 3, 1, 1);
	
	label_name = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_name), "<b>Item Name</b>");
	gtk_grid_attach(GTK_GRID(grid), label_name, 8, 3, 1, 1);
	
	pad6 = gtk_label_new("     ");
	gtk_grid_attach(GTK_GRID(grid), pad6, 9, 3, 1, 1);
	
	label_qty = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_qty), "<b>Qty </b>");
	gtk_grid_attach(GTK_GRID(grid), label_qty, 10, 3, 1 ,1);
	
	pad7 = gtk_label_new("       ");
	gtk_grid_attach(GTK_GRID(grid), pad7, 11, 3, 1, 1);
	
	label_purchase_rate = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_purchase_rate), "<b>Purchase Rate (Rs.)</b>");
	gtk_grid_attach(GTK_GRID(grid), label_purchase_rate, 12, 3, 1 ,1);
	
	pad7 = gtk_label_new("       ");
	gtk_grid_attach(GTK_GRID(grid), pad7, 13, 3, 1, 1);
	
	label_vat = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_vat), "<b>VAT %</b>");
	gtk_grid_attach(GTK_GRID(grid), label_vat, 14, 3, 1, 1);
	
	pad8 = gtk_label_new("        ");
	gtk_grid_attach(GTK_GRID(grid), pad8, 15, 3, 1, 1);
	
	label_amt = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_amt), "<b>Amount (Rs.)</b>");
	gtk_grid_attach(GTK_GRID(grid), label_amt, 16, 3, 1, 1);
	
	pad9 = gtk_label_new("     ");
	gtk_grid_attach(GTK_GRID(grid), pad9, 17, 3, 1, 1);
	
	label_total = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_total), "<b>Bill Total (Rs.)</b>");
	gtk_grid_attach(GTK_GRID(grid), label_total, 18, 3, 1, 1);
	
	pad10 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(grid), pad10, 19, 3, 1, 1);
	
	pad11 = gtk_label_new("      ");
	gtk_grid_attach(GTK_GRID(grid), pad11, 0, 4, 19, 1);
	
	fp = fopen("InwardMaster.txt", "r");
	
	i = 0;
	j = 5;
	
	if(fp){

		while(fread(&purchase_no, sizeof(long long int), 1, fp)){
	
			inward_view->label_txt_purchase_no = gtk_label_new(NULL);
			sprintf(purchase_no_str, "%lld", purchase_no);
			gtk_label_set_text(GTK_LABEL(inward_view->label_txt_purchase_no), purchase_no_str);
			gtk_grid_attach(GTK_GRID(grid), inward_view->label_txt_purchase_no, 0, j, 1, 1);
			fread(&ch, sizeof(char), 1, fp);

			fread(&supplier_ino, sizeof(long long int), 1, fp);
			sprintf(supplier_ino_str, "%lld", supplier_ino);
			inward_view->label_txt_supplier_ino = gtk_label_new(NULL);
			gtk_label_set_text(GTK_LABEL(inward_view->label_txt_supplier_ino), supplier_ino_str);
			gtk_grid_attach(GTK_GRID(grid), inward_view->label_txt_supplier_ino, 2, j, 1, 1);
			fread(&ch, sizeof(char), 1, fp);
		
			fread(&size_pname, sizeof(int), 1, fp);
			pname = (char *)malloc(sizeof(char) * size_pname + 1);
			fread(pname, sizeof(char), size_pname, fp);
			pname[size_pname] = '\0';
			inward_view->label_txt_party_name = gtk_label_new(NULL);
			gtk_label_set_text(GTK_LABEL(inward_view->label_txt_party_name), pname);
			gtk_grid_attach(GTK_GRID(grid), inward_view->label_txt_party_name, 4, j, 1, 1);
		
			while(fread(&ch, sizeof(char), 1, fp)){
				if(ch == 'c'){
					inward_view->inward_view_sub[i] = (Inward_view_sub *)malloc(sizeof(Inward_view_sub));
				
					fread(&code, sizeof(long long int), 1, fp);
					sprintf(code_str, "%lld", code);
					inward_view->inward_view_sub[i]->label_txt_code = gtk_label_new(NULL);
					gtk_label_set_text(GTK_LABEL(inward_view->inward_view_sub[i]->label_txt_code), code_str);
					gtk_grid_attach(GTK_GRID(grid), inward_view->inward_view_sub[i]->label_txt_code, 6, j, 1, 1);
		
					fread(&ch, sizeof(char), 1, fp);
		
					fread(&size_iname, sizeof(int), 1, fp);
					item_name = (char *)malloc(sizeof(char) * size_iname + 1);
					fread(item_name, sizeof(char), size_iname, fp);
					item_name[size_iname] = '\0';
					inward_view->inward_view_sub[i]->label_txt_name = gtk_label_new(NULL);
					gtk_label_set_text(GTK_LABEL(inward_view->inward_view_sub[i]->label_txt_name), item_name);
					gtk_grid_attach(GTK_GRID(grid), inward_view->inward_view_sub[i]->label_txt_name, 8, j, 1, 1);
		
					fread(&qty, sizeof(long int), 1, fp);
					sprintf(qty_str, "%ld", qty);
					inward_view->inward_view_sub[i]->label_txt_qty = gtk_label_new(NULL);
					gtk_label_set_text(GTK_LABEL(inward_view->inward_view_sub[i]->label_txt_qty), qty_str);
					gtk_grid_attach(GTK_GRID(grid), inward_view->inward_view_sub[i]->label_txt_qty, 10, j, 1, 1);
					fread(&ch, sizeof(char), 1, fp);
		
					fread(&rate, sizeof(float), 1, fp);
					sprintf(rate_str, "%f", rate);
					inward_view->inward_view_sub[i]->label_txt_purchase_rate = gtk_label_new(NULL);
					gtk_label_set_text(GTK_LABEL(inward_view->inward_view_sub[i]->label_txt_purchase_rate), rate_str);
					gtk_grid_attach(GTK_GRID(grid), inward_view->inward_view_sub[i]->label_txt_purchase_rate, 12, j, 1, 1);
				
					fread(&vat, sizeof(float), 1, fp);
					sprintf(vat_str, "%f", vat);
					inward_view->inward_view_sub[i]->label_txt_vat = gtk_label_new(NULL);
					gtk_label_set_text(GTK_LABEL(inward_view->inward_view_sub[i]->label_txt_vat), vat_str);
					gtk_grid_attach(GTK_GRID(grid), inward_view->inward_view_sub[i]->label_txt_vat, 14, j, 1, 1);
				
					fread(&amt, sizeof(double), 1, fp);
					sprintf(amt_str, "%f", amt);
					inward_view->inward_view_sub[i]->label_txt_amt = gtk_label_new(NULL);
					gtk_label_set_text(GTK_LABEL(inward_view->inward_view_sub[i]->label_txt_amt), rate_str);
					gtk_grid_attach(GTK_GRID(grid), inward_view->inward_view_sub[i]->label_txt_amt, 16, j, 1, 1);
				
					j++;
				}
			
				else{
					/*Move the file pointer backward 1 byte so that it can read the next purchase bill.*/
					fseek(fp, -sizeof(char), SEEK_CUR);
					break;
				}
			
				i++;
				j++;
			
			}
			fread(&total, sizeof(double), 1, fp);
			sprintf(total_str, "%lf", total);
			inward_view->label_txt_total = gtk_label_new(NULL);
			gtk_label_set_text(GTK_LABEL(inward_view->label_txt_total), total_str);
			gtk_grid_attach(GTK_GRID(grid), inward_view->label_txt_total, 18, j - 2, 1, 1);
		}
	
		fclose(fp);
	}
	
	/*Call a function to go to the previous screen when ESC key is pressed.*/
	g_signal_connect(win_grid->window, "key_press_event", G_CALLBACK(check_escape), win_grid);
	
	gtk_widget_show_all(view_window);
	gtk_widget_show_all(window);
	return;
}

