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

void g_master_activate(GtkApplication *app, Window_grid *win_grid){
	GtkWidget *window, *group_master_grid;
	GtkWidget *label_group_master_title, *label_group, *label_padding1, *label_padding2, *label_padding3, *label_padding4;
	GtkWidget *txt_group;
	GtkWidget *btn_create;

	/*Create a grid and keep adding various components to it.*/
	gtk_container_remove(GTK_CONTAINER(win_grid->window), win_grid->grid);
	group_master_grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(win_grid->window), group_master_grid);
	win_grid->grid = group_master_grid;
	
	win_grid->current_screen = MASTER;
	
	label_padding1 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(group_master_grid), label_padding1, 0, 0, 1, 2);
	
	/*This is the label which displays the title on the page.*/
	label_group_master_title = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_group_master_title), "<u><b><big>Group Master</big></b></u>\n");
	gtk_grid_attach(GTK_GRID(group_master_grid), label_group_master_title, 1, 1, 1, 2);
	
	label_padding2 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(group_master_grid), label_padding1, 2, 2, 1, 2);
	
	/*Create the labels and add them to the grid*/
	label_group = gtk_label_new("Group : ");
	gtk_grid_attach(GTK_GRID(group_master_grid), label_group, 1, 3, 1, 1);
	
	/*Create the text fields and add them to the grid*/
	txt_group = gtk_entry_new();
	gtk_grid_attach(GTK_GRID(group_master_grid), txt_group, 2, 3, 1, 1);
	
	label_padding3 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(group_master_grid), label_padding3, 4, 4, 2, 1);
	
	/*Create an instance of a button and add it to the grid.*/
	btn_create = gtk_button_new_with_label("CREATE");
	g_signal_connect(btn_create, "clicked", G_CALLBACK(g_master_create), txt_group);
	gtk_grid_attach(GTK_GRID(group_master_grid), btn_create, 2, 5, 1, 1);
	
	label_padding4 = gtk_label_new(NULL);
	gtk_grid_attach(GTK_GRID(group_master_grid), label_padding4, 6, 6, 2, 1);
	
	
	/*Add a signal to go back to the home screen when the user presses ESC*/
	g_signal_connect(win_grid->window, "key_press_event", G_CALLBACK(check_escape), win_grid);
		
	/*Make all the components visible.*/
	gtk_widget_show_all(win_grid->window);
	
	return;
}

void g_master_create(GtkWidget *widget, GtkWidget *txt_group){
	const gchar *group;
 	group = gtk_entry_get_text((GtkEntry *)txt_group);

 	/*Write the infromation to the appropriate file only if the text field is not empty.*/
 	if(group[0] != '\0')
 		write_g_master_info(group);
	
	/*Clear the data in the text field.*/
 	gtk_entry_set_text((GtkEntry *)txt_group, " ");
 	
	return;
	
}
