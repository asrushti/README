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
 
#ifndef __MAIN__H
#define __MAIN__H
#define MAXIMUM 20
#define MAX_VIEW 1000

#define MAX_ARR 19999
#define KEY_ESC '\033'
#define HOME 1
#define MASTER 2
#define MASTER_SUB 3
#define MASTER_SUB_UPDATE 4
#define INWARD_SUB 5
#define SALE_SUB 6
#define MASTER_SUB_CAT 7
#define MASTER_SUB_GRP 8

typedef struct Window_grid{
	GtkWidget *window, *grid;
	GtkApplication *application;
	int current_screen;
}Window_grid;

typedef struct item_master_display{
	GtkWidget *label_txt_name, *label_txt_code, *label_txt_group, *label_txt_category, *label_txt_vat, *label_txt_unit, *label_txt_sale_rate, *btn_select;
}Item_master_display;

typedef struct Item_master{
	GtkWidget *txt_item_name, *txt_item_code, *txt_item_unit, *txt_item_vat, *txt_sale_rate;
	GtkWidget *combo_item_group, *combo_item_category; 
	GtkWidget *btn_item_submit, *btn_item_update;
}Item_master;

void item_master_activate(GtkApplication *app, Window_grid *win_grid);
void item_master_populate(Item_master *item_master);
void item_master_create(GtkWidget *widget, Item_master *item_master);
Item_master *item_master_add(GtkApplication *app, Window_grid *win_grid);
void item_master_view(GtkApplication *app, Window_grid *win_grid);
void item_master_update(GtkApplication *app, Window_grid *win_grid);
void item_master_display_fetch_data(GtkApplication *app, Item_master_display *master);


GtkWidget *initialize_window(GtkApplication *app);
gboolean check_escape(GtkWidget *widget, GdkEventKey *event, Window_grid *win_grid);
void activate(GtkApplication *app, Window_grid *win_grid);

void g_master_activate(GtkApplication *app, Window_grid *win_grid);
void g_master_create(GtkWidget *widget, GtkWidget *txt_group);
void g_master_add(GtkApplication *app, Window_grid *win_grid);
void view_group(GtkApplication *app, Window_grid *win_grid);

void c_master_activate(GtkApplication *app, Window_grid *win_grid);
void c_master_add(GtkApplication *app, Window_grid *win_grid);
void c_master_create(GtkWidget *widget, GtkWidget *txt_category);
void view_category(GtkApplication *app, Window_grid *win_grid);

void stock_summary_activate(GtkApplication *app, Window_grid *win_grid);

#endif
