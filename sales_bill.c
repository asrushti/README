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
#include <gdk/gdkkeysyms.h>
#include "main.h"
#include "files.h"

void sales_bill_activate(GtkApplication *app, Window_grid *win_grid){
	GtkWidget *sales_grid;
	GtkWidget *label_title, *btn_create, *btn_view;
	GtkWidget *pad0, *pad1, *pad2, *pad3, *pad4, *pad5, *pad6, *pad7, *pad8, *pad9, *pad10;
	
	/*Remove the previously attached grid and set the grid and current screen.*/
	gtk_container_remove(GTK_CONTAINER(win_grid->window), win_grid->grid);
	sales_grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(win_grid->window), sales_grid);
	win_grid->grid = sales_grid;
	gtk_window_set_title(GTK_WINDOW(win_grid->window), "Bill it OONNNNN");
	win_grid->current_screen = MASTER;
	
	pad0 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(sales_grid), pad0, 0, 0, 6, 1);
	
	pad4 = gtk_label_new("      ");
	gtk_grid_attach(GTK_GRID(sales_grid), pad4, 0, 1, 2, 1);
	
	/*This is the label which displays the title on the page.*/
	label_title = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_title), "<u><b><big>SALES	BILL</big></b></u>\n");
	gtk_grid_attach(GTK_GRID(sales_grid), label_title , 1, 1, 4, 1);
	
	pad5 = gtk_label_new("      ");
	gtk_grid_attach(GTK_GRID(sales_grid), pad5, 5, 1, 1, 1);
	
	pad1 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(sales_grid), pad1, 0, 2, 5, 1);
	
	pad6 = gtk_label_new("      ");
	gtk_grid_attach(GTK_GRID(sales_grid), pad0, 0, 3, 2, 1);
	
	btn_create = gtk_button_new_with_label("CREATE");
	gtk_grid_attach(GTK_GRID(sales_grid), btn_create, 3, 3, 1, 1);
	g_signal_connect(btn_create, "clicked", G_CALLBACK(sales_bill_create), win_grid);
	
	pad7 = gtk_label_new("      ");
	gtk_grid_attach(GTK_GRID(sales_grid), pad7, 4, 3, 1, 1);
	
	pad2 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(sales_grid), pad2, 0, 4, 6, 1);
	
	pad8 = gtk_label_new("      ");
	gtk_grid_attach(GTK_GRID(sales_grid), pad8, 0, 5, 2, 1);
	
	btn_view = gtk_button_new_with_label("VIEW");
	gtk_grid_attach(GTK_GRID(sales_grid), btn_view, 3, 5, 1, 1);
	g_signal_connect(btn_view, "clicked", G_CALLBACK(sales_bill_view), win_grid);
	
	pad9 = gtk_label_new("      ");
	gtk_grid_attach(GTK_GRID(sales_grid), pad9, 4, 5, 1, 1);
		
	pad3 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(sales_grid), pad3, 0, 6, 3, 1);
	
	/*Return to the previous screen when ESC key is pressed*/
	g_signal_connect(win_grid->window, "key_press_event", G_CALLBACK(check_escape), win_grid);
	
	gtk_widget_show_all(win_grid->window);
	return;
}

void sales_bill_create(GtkApplication *app, Window_grid *win_grid){
	GtkWidget *sales_bill_grid;
	GtkWidget *label_sales_title, *label_invoice_no, *txt_invoice_no, *label_sr_no, *label_txt_sr_no, *label_code, *label_item_name, *label_sales_qty, *label_sales_rate, *label_sales_amt, *label_sales_vat, *label_sales_total;
	GtkWidget *btn_sales_create;	
	GtkWidget *pad0, *pad1, *pad2, *pad3, *pad4, *pad5, *pad6, *pad7, *pad8, *pad9, *pad10, *pad11;
	Sales_bill *sales_bill;
	char sr_no_str[3];
	int j, i = 0;

	sales_bill = (Sales_bill *)malloc(sizeof(Sales_bill));
	
	/*Remove the screen that was added to the container previously and add a new grid which contains other components.*/
	gtk_container_remove(GTK_CONTAINER(win_grid->window), win_grid->grid);
	sales_bill_grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(win_grid->window), sales_bill_grid);
	win_grid->grid = sales_bill_grid;
	win_grid->current_screen = SALE_SUB;

	pad0 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(sales_bill_grid), pad0, 0, 0, 13, 1);
	
	/*This is the label which displays the title on the page.*/
	label_sales_title = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_sales_title), "<u><b><big>SALES   BILL</big></b></u>\n");
	gtk_grid_attach(GTK_GRID(sales_bill_grid), label_sales_title , 0, 1, 13, 1);
	
	pad1 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(sales_bill_grid), pad1, 0, 2, 13, 1);
	
	label_invoice_no = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_invoice_no), "<big>Invoice No : </big>");
	gtk_grid_attach(GTK_GRID(sales_bill_grid), label_invoice_no, 0, 3, 1, 1);
	
	sales_bill->txt_invoice_no = gtk_entry_new();
	gtk_grid_attach(GTK_GRID(sales_bill_grid), sales_bill->txt_invoice_no, 1, 3, 1, 1);
	
	pad3 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(sales_bill_grid), pad3, 0, 4, 13, 1);
	
	label_sr_no = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_sr_no), "<big>Sr. No.</big>");
	gtk_grid_attach(GTK_GRID(sales_bill_grid), label_sr_no, 0, 5, 1, 1);
	
	label_code = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_code), "<big>Item Code</big>");
	gtk_grid_attach(GTK_GRID(sales_bill_grid), label_code, 1, 5, 1, 1);
	
	pad5 = gtk_label_new("      ");
	gtk_grid_attach(GTK_GRID(sales_bill_grid), pad5, 2, 5, 1, 1);
	
	label_sales_qty = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_sales_qty), "<big>Qty </big>");
	gtk_grid_attach(GTK_GRID(sales_bill_grid), label_sales_qty, 3, 5, 1, 1);
	
	pad9 = gtk_label_new("        ");
	gtk_grid_attach(GTK_GRID(sales_bill_grid), pad9, 4, 5, 1, 1);
	
	label_item_name = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_item_name), "<big>Name of item </big>");
	gtk_grid_attach(GTK_GRID(sales_bill_grid), label_item_name, 5, 5, 2, 1);
	
	pad6 = gtk_label_new("        ");
	gtk_grid_attach(GTK_GRID(sales_bill_grid), pad6, 7, 5, 1, 1);
		
	label_sales_rate = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_sales_rate), "<big>Rate  </big>");
	gtk_grid_attach(GTK_GRID(sales_bill_grid), label_sales_rate, 8, 5, 1, 1);
	
	pad7 = gtk_label_new("        ");
	gtk_grid_attach(GTK_GRID(sales_bill_grid), pad7, 9, 5, 1, 1);
	
	label_sales_vat = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_sales_vat), "<big>VAT %</big>");
	gtk_grid_attach(GTK_GRID(sales_bill_grid), label_sales_vat, 10, 5, 1, 1);
	
	pad8 = gtk_label_new("        ");
	gtk_grid_attach(GTK_GRID(sales_bill_grid), pad8, 11, 5, 1, 1);
	
	label_sales_amt = gtk_label_new("Empty");
	gtk_label_set_markup(GTK_LABEL(label_sales_amt), "<big>Amount</big>");
	gtk_grid_attach(GTK_GRID(sales_bill_grid), label_sales_amt, 12, 5, 1, 1);
	
	pad10 = gtk_label_new("        ");
	gtk_grid_attach(GTK_GRID(sales_bill_grid), pad10, 13, 5, 1, 1);
	
	pad11 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(sales_bill_grid), pad8, 0, 6, 13, 1);
	
	label_sales_total = gtk_label_new("Empty");
	gtk_label_set_markup(GTK_LABEL(label_sales_total), "<big>Total : </big>");
	gtk_grid_attach(GTK_GRID(sales_bill_grid), label_sales_total, 11, 26, 1, 1);
	
	sales_bill->label_txt_total = gtk_label_new(NULL);
	gtk_label_set_text(GTK_LABEL(sales_bill->label_txt_total), "0");
	gtk_grid_attach(GTK_GRID(sales_bill_grid), sales_bill->label_txt_total, 12, 26, 1, 1);

	j = 7;
	while(i < MAXIMUM){
		
		sales_bill->sales_new[i] = (Sales_new *)malloc(sizeof(Sales_new));
		
		/*Convert the integer type variable to string and set it as the sr.no*/
		sprintf(sr_no_str, "%d", i + 1);
		sales_bill->sales_new[i]->label_txt_sr_no = gtk_label_new(NULL);
		gtk_label_set_text(GTK_LABEL(sales_bill->sales_new[i]->label_txt_sr_no), sr_no_str);
		gtk_grid_attach(GTK_GRID(sales_bill_grid), sales_bill->sales_new[i]->label_txt_sr_no, 0, j, 1, 1);
		
		sales_bill->sales_new[i]->txt_code = gtk_entry_new(); 
		gtk_grid_attach(GTK_GRID(sales_bill_grid), sales_bill->sales_new[i]->txt_code, 1, j, 1, 1);
		
		sales_bill->sales_new[i]->label_txt_item_name = gtk_label_new(NULL);
		sales_bill->sales_new[i]->txt_sales_qty = gtk_entry_new();
		sales_bill->sales_new[i]->label_sales_rate = gtk_label_new(NULL);
		sales_bill->sales_new[i]->label_txt_sales_vat = gtk_label_new(NULL);
		sales_bill->sales_new[i]->label_txt_sales_amt = gtk_label_new(NULL);
		
		gtk_grid_attach(GTK_GRID(sales_bill_grid), sales_bill->sales_new[i]->label_txt_item_name, 5, j, 2, 1);
		gtk_grid_attach(GTK_GRID(sales_bill_grid), sales_bill->sales_new[i]->txt_sales_qty, 3, j, 1, 1);
		gtk_grid_attach(GTK_GRID(sales_bill_grid), sales_bill->sales_new[i]->label_sales_rate, 8, j, 1, 1);
		gtk_grid_attach(GTK_GRID(sales_bill_grid), sales_bill->sales_new[i]->label_txt_sales_vat, 10, j, 1, 1);
		gtk_grid_attach(GTK_GRID(sales_bill_grid), sales_bill->sales_new[i]->label_txt_sales_amt, 12, j, 1, 1);
		
		g_signal_connect(sales_bill->sales_new[i]->txt_sales_qty, "activate", G_CALLBACK(set_sales_bill_values), sales_bill);
		i++;
		j++;

	}	
	
	j++;
	/*Create an instance of a button and add it to the grid.*/
	btn_sales_create = gtk_button_new_with_label("CREATE");
	gtk_grid_attach(GTK_GRID(sales_bill_grid), btn_sales_create, 12, j, 1, 1);
	g_signal_connect(btn_sales_create, "clicked", G_CALLBACK(write_sales_bill), sales_bill);
	
	/*Call a function to return to the main screen when the ESC key is pressed.*/
	g_signal_connect(win_grid->window, "key_press_event", G_CALLBACK(check_escape), win_grid);
	
	/*Make all the components visible.*/
	gtk_widget_show_all(win_grid->window);	
	return;
}

void set_sales_bill_values(GtkWidget *widget, Sales_bill *sales_bill){
	FILE *fp;
	int size_name, size_group, size_cat, size_unit, i = 0;
	long long int code, code1;
	char ch, *group, *category, *name, *unit, vat_str[MAX_STR], amt_str[30], total_str[30], code_str[16], rate_str[12];
	float vat, rate, rate1;
	long int qty;
	double total, amt, vat_amt;
	
	fp = fopen("data/ItemMaster.txt", "r");
	
	while(sales_bill->sales_new[i]->txt_sales_qty != widget)
		i++;
	
	/*If the fields are not null, fetch all the values and perform the necessary computation.*/
	if(gtk_entry_get_text((GtkEntry*) sales_bill->sales_new[i]->txt_code)){
		code1 = atoll(gtk_entry_get_text((GtkEntry *)sales_bill->sales_new[i]->txt_code));
		
		total = atof(gtk_label_get_text((GtkLabel *)sales_bill->label_txt_total));
		qty = atol(gtk_entry_get_text((GtkEntry *)sales_bill->sales_new[i]->txt_sales_qty));
		
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
				gtk_label_set_text(GTK_LABEL(sales_bill->sales_new[i]->label_txt_item_name), name);
				/*Set the vat and rate label*/
				sprintf(vat_str, "%f", vat);
				gtk_label_set_text(GTK_LABEL(sales_bill->sales_new[i]->label_txt_sales_vat), vat_str);
				sprintf(rate_str, "%f", rate);
				gtk_label_set_text(GTK_LABEL(sales_bill->sales_new[i]->label_sales_rate), rate_str);
				/*compute the amount label*/
				qty = atol(gtk_entry_get_text((GtkEntry *)sales_bill->sales_new[i]->txt_sales_qty));
				amt = rate * qty;
				/*Compute the VAT AMOUNT*/
				vat_amt = (amt * vat)/100;
				amt += vat_amt;
				sprintf(amt_str, "%lf", amt);
				gtk_label_set_text(GTK_LABEL(sales_bill->sales_new[i]->label_txt_sales_amt), amt_str);
			
				/*Compute and set the total*/
				total += amt;
				sprintf(total_str, "%lf", total);
				gtk_label_set_text(GTK_LABEL(sales_bill->label_txt_total), total_str);
			
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

void sales_bill_view(GtkWidget *widget, Window_grid *win_grid){
	GtkWidget *view_window, *label_title, *grid, *window;
	GtkWidget *label_invoice_no, *label_name, *label_code, *label_purchase_rate, *label_vat, *label_amt, *label_qty, *label_total;
	Sales_view *sales_view;
	GtkWidget *pad0, *pad1, *pad2, *pad3, *pad4, *pad5, *pad6, *pad7, *pad8, *pad9, *pad10, *pad11, *pad12;
	FILE *fp;
	char ch = 'c';
	int size_iname, size_pname, i, j, k;
	long long int code, invoice_no;
	char *pname, *item_name, invoice_no_str[16], amt_str[16], vat_str[12], rate_str[16], total_str[16], code_str[16], qty_str[12];
	float vat, rate;
	long int qty;
	double amt, total;
	
	sales_view = (Sales_view *)malloc(sizeof(Sales_view));
	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	
	/*Create a scrollable window and add it to the main window*/
	view_window = gtk_scrolled_window_new(NULL, NULL);
	/*Create a grid and add it to the window.*/
	grid = gtk_grid_new();
	
	/*Set the visibility of the scrollbars.*/
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(view_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
	
	/*Add the grid to the scrollable window and add the scrolled window to the main window*/
	gtk_container_remove(GTK_CONTAINER(window), win_grid->grid);
	
	gtk_container_add(GTK_CONTAINER(view_window), grid);
	gtk_container_add(GTK_CONTAINER(window), view_window);
	gtk_widget_show(view_window);
	gtk_window_set_default_size(GTK_WINDOW(window), 1500, 500);
	gtk_window_set_resizable(GTK_WINDOW(window), TRUE);
	
	pad0 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(grid), pad0, 0, 0, 16, 1);
	
	/*Create the title label and add it to the grid*/
	label_title = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_title), "<b><big>Sale Register</big></b>");
	gtk_grid_attach(GTK_GRID(grid), label_title, 0, 1, 16, 1);
	
	pad1 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(grid), pad1, 0, 2, 16, 1);
	
	/*Create the labels and add them to the screen.*/
	label_invoice_no = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_invoice_no), "<b>Invoice No.</b>"); 
	gtk_grid_attach(GTK_GRID(grid), label_invoice_no, 0, 3, 1, 1);
	
	pad2 = gtk_label_new("        ");
	gtk_grid_attach(GTK_GRID(grid), pad2, 1, 3, 1, 1);
	
	label_code = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_code), "<b>Item Code</b>");
	gtk_grid_attach(GTK_GRID(grid), label_code, 2, 3, 1, 1);
	
	pad5 = gtk_label_new("     ");
	gtk_grid_attach(GTK_GRID(grid), pad5, 3, 3, 1, 1);
	
	label_name = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_name), "<b>Item Name</b>");
	gtk_grid_attach(GTK_GRID(grid), label_name, 4, 3, 2, 1);
	
	pad6 = gtk_label_new("     ");
	gtk_grid_attach(GTK_GRID(grid), pad6, 6, 3, 1, 1);
	
	label_qty = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_qty), "<b>Qty </b>");
	gtk_grid_attach(GTK_GRID(grid), label_qty, 7, 3, 1 ,1);
	
	pad7 = gtk_label_new("       ");
	gtk_grid_attach(GTK_GRID(grid), pad7, 8, 3, 1, 1);
	
	label_purchase_rate = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_purchase_rate), "<b>Sale Rate (Rs.)</b>");
	gtk_grid_attach(GTK_GRID(grid), label_purchase_rate, 9, 3, 1 ,1);
	
	pad7 = gtk_label_new("       ");
	gtk_grid_attach(GTK_GRID(grid), pad7, 10, 3, 1, 1);
	
	label_vat = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_vat), "<b>VAT %</b>");
	gtk_grid_attach(GTK_GRID(grid), label_vat, 11, 3, 1, 1);
	
	pad8 = gtk_label_new("        ");
	gtk_grid_attach(GTK_GRID(grid), pad8, 12, 3, 1, 1);
	
	label_amt = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_amt), "<b>Amount (Rs.)</b>");
	gtk_grid_attach(GTK_GRID(grid), label_amt, 13, 3, 1, 1);
	
	pad9 = gtk_label_new("     ");
	gtk_grid_attach(GTK_GRID(grid), pad9, 14, 3, 1, 1);
	
	label_total = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_total), "<b>Bill Total (Rs.)</b>");
	gtk_grid_attach(GTK_GRID(grid), label_total, 15, 3, 1, 1);
	
	pad10 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(grid), pad10, 16, 3, 1, 1);
	
	pad11 = gtk_label_new("      ");
	gtk_grid_attach(GTK_GRID(grid), pad11, 0, 4, 16, 1);
	
	fp = fopen("data/SalesMaster.txt", "r");
	
	i = 0;
	j = 5;
	
	while(fread(&invoice_no, sizeof(long long int), 1, fp)){
	
		sales_view->label_txt_invoice_no = gtk_label_new(NULL);
		sprintf(invoice_no_str, "%lld", invoice_no);
		gtk_label_set_text(GTK_LABEL(sales_view->label_txt_invoice_no), invoice_no_str);
		gtk_grid_attach(GTK_GRID(grid), sales_view->label_txt_invoice_no, 0, j, 1, 1);
		fread(&ch, sizeof(char), 1, fp);
		
		while(fread(&ch, sizeof(char), 1, fp)){
			if(ch == 'c'){
				sales_view->sales_view_sub[i] = (Sales_view_sub *)malloc(sizeof(Sales_view_sub));
				
				fread(&code, sizeof(long long int), 1, fp);
				sprintf(code_str, "%lld", code);
				sales_view->sales_view_sub[i]->label_code = gtk_label_new(NULL);
				gtk_label_set_text(GTK_LABEL(sales_view->sales_view_sub[i]->label_code), code_str);
				gtk_grid_attach(GTK_GRID(grid), sales_view->sales_view_sub[i]->label_code, 2, j, 1, 1);
		
				fread(&ch, sizeof(char), 1, fp);
		
				fread(&size_iname, sizeof(int), 1, fp);
				item_name = (char *)malloc(sizeof(char) * size_iname + 1);
				fread(item_name, sizeof(char), size_iname, fp);
				item_name[size_iname] = '\0';
				sales_view->sales_view_sub[i]->label_name = gtk_label_new(NULL);
				gtk_label_set_text(GTK_LABEL(sales_view->sales_view_sub[i]->label_name), item_name);
				gtk_grid_attach(GTK_GRID(grid), sales_view->sales_view_sub[i]->label_name, 4, j, 2, 1);
		
				fread(&qty, sizeof(long int), 1, fp);
				sprintf(qty_str, "%ld", qty);
				sales_view->sales_view_sub[i]->label_qty = gtk_label_new(NULL);
				gtk_label_set_text(GTK_LABEL(sales_view->sales_view_sub[i]->label_qty), qty_str);
				gtk_grid_attach(GTK_GRID(grid), sales_view->sales_view_sub[i]->label_qty, 7, j, 1, 1);
				fread(&ch, sizeof(char), 1, fp);
		
				fread(&rate, sizeof(float), 1, fp);
				sprintf(rate_str, "%f", rate);
				sales_view->sales_view_sub[i]->label_rate = gtk_label_new(NULL);
				gtk_label_set_text(GTK_LABEL(sales_view->sales_view_sub[i]->label_rate), rate_str);
				gtk_grid_attach(GTK_GRID(grid), sales_view->sales_view_sub[i]->label_rate, 9, j, 1, 1);
				
				fread(&vat, sizeof(float), 1, fp);
				sprintf(vat_str, "%f", vat);
				sales_view->sales_view_sub[i]->label_vat = gtk_label_new(NULL);
				gtk_label_set_text(GTK_LABEL(sales_view->sales_view_sub[i]->label_vat), vat_str);
				gtk_grid_attach(GTK_GRID(grid), sales_view->sales_view_sub[i]->label_vat, 11, j, 1, 1);
				
				fread(&amt, sizeof(double), 1, fp);
				sprintf(amt_str, "%f", amt);
				sales_view->sales_view_sub[i]->label_amt = gtk_label_new(NULL);
				gtk_label_set_text(GTK_LABEL(sales_view->sales_view_sub[i]->label_amt), rate_str);
				gtk_grid_attach(GTK_GRID(grid), sales_view->sales_view_sub[i]->label_amt, 13, j, 1, 1);
				
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
		sales_view->label_txt_total = gtk_label_new(NULL);
		gtk_label_set_text(GTK_LABEL(sales_view->label_txt_total), total_str);
		gtk_grid_attach(GTK_GRID(grid), sales_view->label_txt_total, 15, j - 2, 1, 1);
			
	}
	
	fclose(fp);
	
	/*Call a function to go to the previous screen when ESC key is pressed.*/
	g_signal_connect(win_grid->window, "key_press_event", G_CALLBACK(check_escape), win_grid);
	
	gtk_widget_show_all(view_window);
	gtk_widget_show_all(window);
	return;
}
