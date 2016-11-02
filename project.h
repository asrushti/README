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
 
#ifndef __PROJECT__H
#define __PROJECT__H

typedef struct Window_grid{
	GtkWidget *window, *grid;
	GtkApplication *application;
}Window_grid;

typedef struct Gc_master{
	GtkWidget *txt_gc_master_group;
	GtkWidget *txt_gc_master_category;
}Gc_master;

typedef struct Gc_info{
	const gchar *group, *category;
}Gc_info;

GtkWidget *initialize_window(GtkApplication *app);
void activate(GtkApplication *app, Window_grid *win_grid);

#endif
