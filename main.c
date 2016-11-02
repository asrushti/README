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
#include "inward.h"

GtkWidget *initialize_window(GtkApplication *app){
	GtkWidget *window;
	window = gtk_application_window_new(app);
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	gtk_window_set_title(GTK_WINDOW(window), "Bill it OONNNNN");	
	return window;
}

/*A function that returns the user to the previous screen*/
gboolean check_escape(GtkWidget *widget, GdkEventKey *event, Window_grid *win_grid){
	if (event->keyval == GDK_KEY_Escape) {
		if(win_grid->current_screen == MASTER_SUB){
			item_master_activate(win_grid->application, win_grid);
			return TRUE;
		}
		
		if(win_grid->current_screen == INWARD_SUB){
			inward_bill_activate(win_grid->application, win_grid);
			return TRUE;
		}
		
		if(win_grid->current_screen == SALE_SUB){
			sales_bill_activate(win_grid->application, win_grid);
			return TRUE;
		}
		
		if(win_grid->current_screen == MASTER){
		/*Call the fucntion that creates the main window if the user presses ESC key.*/
			activate(win_grid->application, win_grid);
			return TRUE;
		}
	}
	return FALSE;
}

void activate(GtkApplication *app, Window_grid *win_grid){
	GtkWidget *main_grid;
	GtkWidget *btn_sales_bill, *btn_item_master, *btn_stock_summary, *btn_group_master,*btn_category_master, *btn_inward_bill; 
	GtkWidget *pad1, *pad2, *pad3, *pad4, *pad5, *pad6, *pad7, *pad8, *label_main_title, *pad9, *pad10, *pad11, *pad12, *pad13, *pad14, *pad15, *pad16;
	
	Window_grid *main;
	
	/*Check whether this is the first time that the function is called.*/
	if(!win_grid){
		main = (Window_grid *)malloc(sizeof(Window_grid));
	
		/*Create the main window and initialize it*/
		main->window = initialize_window(app);
		gtk_window_set_title(GTK_WINDOW(main->window), "Bill it ON");
		main->application = app;			
		/*Create a grid to hold all the components*/
		main->grid = gtk_grid_new();
		gtk_container_add(GTK_CONTAINER(main->window), main->grid);
	}
	/*Use previous arguments to restore the home screen*/
	else{
	
		main = win_grid;
		/*Remove the grid which was added previously and add a new grid.*/
		gtk_container_remove(GTK_CONTAINER(main->window), main->grid);
		g_print("Grid removed\n");
		main_grid = gtk_grid_new();
		gtk_container_add(GTK_CONTAINER(main->window), main_grid);
		main->grid = main_grid;
	}
	/*Set the current screen as the home screen.*/
	main->current_screen = HOME;
	
	pad1 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(main->grid), pad1, 0, 1, 3, 1);
	
	label_main_title = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_main_title), "<b><big><u>GATEWAY	OF	'BILL IT OOONNNN'</u></big></b>");
	gtk_grid_attach(GTK_GRID(main->grid), label_main_title, 0, 2, 3, 1);
	
	pad2 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(main->grid), pad2, 0, 3, 3, 1);
	
	pad3 = gtk_label_new("          ");
	gtk_grid_attach(GTK_GRID(main->grid), pad3, 0, 4, 1, 1);
	
	/*Create buttons with appropriate labels and call respective functions at each button click.*/
	btn_group_master = gtk_button_new_with_label("Group Master");
	gtk_grid_attach(GTK_GRID(main->grid), btn_group_master, 1, 4, 1, 1);
	g_signal_connect(btn_group_master, "clicked", G_CALLBACK(g_master_activate), main);
	
	pad4 = gtk_label_new("          ");
	gtk_grid_attach(GTK_GRID(main->grid), pad4, 2, 4, 1, 1);
	
	pad5 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(main->grid), pad5, 0, 5, 3, 1);
	
	pad6 = gtk_label_new("          ");
	gtk_grid_attach(GTK_GRID(main->grid), pad6, 0, 6, 1, 1);
	
	btn_category_master = gtk_button_new_with_label("Category Master");
	gtk_grid_attach(GTK_GRID(main->grid), btn_category_master, 1, 6, 1, 1);
	g_signal_connect(btn_category_master, "clicked", G_CALLBACK(c_master_activate), main);
	
	pad7 = gtk_label_new("          ");
	gtk_grid_attach(GTK_GRID(main->grid), pad7, 2, 6, 1, 1);
	
	pad8 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(main->grid), pad8, 0, 7, 3, 1);
	
	pad9 = gtk_label_new("          ");
	gtk_grid_attach(GTK_GRID(main->grid), pad9, 0, 8, 1, 1);
	
	btn_item_master = gtk_button_new_with_label("Item Master");
	gtk_grid_attach(GTK_GRID(main->grid), btn_item_master, 1, 8, 1, 1);
	g_signal_connect(btn_item_master, "clicked", G_CALLBACK(item_master_activate), main);
	
	pad10 = gtk_label_new("          ");
	gtk_grid_attach(GTK_GRID(main->grid), pad10, 2, 8, 1, 1);
	
	pad11 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(main->grid), pad11, 0, 9, 3, 1);
	
	pad12 = gtk_label_new("          ");
	gtk_grid_attach(GTK_GRID(main->grid), pad12, 0, 10, 1, 1);
	
	btn_inward_bill = gtk_button_new_with_label("Inward Bill");
	gtk_grid_attach(GTK_GRID(main->grid), btn_inward_bill, 1, 10, 1, 1); 
	g_signal_connect(btn_inward_bill, "clicked", G_CALLBACK(inward_bill_activate), main);
	
	pad13 = gtk_label_new("          ");
	gtk_grid_attach(GTK_GRID(main->grid), pad13, 2, 10, 1, 1);
	
	pad14 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(main->grid), pad14, 0, 11, 3, 1);
	
	pad15 = gtk_label_new("          ");
	gtk_grid_attach(GTK_GRID(main->grid), pad15, 0, 12, 1, 1);
	
	btn_sales_bill = gtk_button_new_with_label("Sales Bill");
	gtk_grid_attach(GTK_GRID(main->grid), btn_sales_bill, 1, 12, 1, 1);
	g_signal_connect(btn_sales_bill, "clicked", G_CALLBACK(sales_bill_activate), main);
	
	pad15 = gtk_label_new("          ");
	gtk_grid_attach(GTK_GRID(main->grid), pad15, 2, 12, 1, 1);
	
	pad16 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(main->grid), pad16, 0, 13, 3, 1);
	
	gtk_widget_show_all(main->window);	
}


