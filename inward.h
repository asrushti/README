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
 
#ifndef __INWARD__H
#define __INWARD__H
#define MAX_INWARD 15

typedef struct Inward_new{
	GtkWidget  *combo_code, *label_txt_item_name, *label_txt_inward_amt, *txt_inward_qty, *txt_inward_rate, *label_txt_inward_vat;
}Inward_new;

typedef struct Inward_bill{
	GtkWidget *txt_purchase_no, *txt_supplier_ino, *txt_party_name, *label_txt_inward_total;
	Inward_new *inward_new[MAX_INWARD];
}Inward_bill;

typedef struct Inward_view_sub{
	GtkWidget *label_txt_name, *label_txt_code, *label_txt_purchase_rate, *label_txt_vat, *label_txt_amt, *label_txt_qty;
}Inward_view_sub;

typedef struct Inward_view{
	GtkWidget *label_txt_purchase_no, *label_txt_supplier_ino, *label_txt_party_name,  *label_txt_total;
	Inward_view_sub *inward_view_sub[MAX_ARR];
}Inward_view;


void inward_bill_activate(GtkApplication *app, Window_grid *win_grid);
void inward_bill_create(GtkWidget *widget, Window_grid *win_grid);
void get_purchase_no(GtkWidget *widget);
void set_inward_values(GtkWidget *widget, Inward_bill *inward_bill);
void inward_bill_view(GtkWidget *widget, Window_grid *win_grid);

#endif
