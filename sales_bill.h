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
 
#ifndef __SALESBILL__h
#define __SALESBILL__H
#include "main.h"
#include "files.h"

typedef struct Sales_new{
	GtkWidget  *label_txt_sr_no, *txt_code, *label_txt_item_name, *label_txt_sales_amt, *txt_sales_qty, *label_sales_rate, *label_txt_sales_vat;
}Sales_new;

typedef struct Sales_view_sub{
	GtkWidget *label_code, *label_name, *label_qty, *label_vat, *label_rate, *label_amt;
}Sales_view_sub;

typedef struct Sales_bill{
	GtkWidget *txt_invoice_no, *label_txt_total;
	Sales_new *sales_new[MAXIMUM];
}Sales_bill;

typedef struct Sales_view{
	GtkWidget *label_txt_invoice_no, *label_txt_total;
	Sales_view_sub *sales_view_sub[MAX_ARR];
}Sales_view;

void sales_bill_activate(GtkApplication *app, Window_grid *win_grid);
void sales_bill_create(GtkApplication *app, Window_grid *win_grid);
void set_sales_bill_values(GtkWidget *widget, Sales_bill *sales_bill);
void sales_bill_view(GtkWidget *widget, Window_grid *win_grid);

#endif
