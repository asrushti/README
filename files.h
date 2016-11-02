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
 
#ifndef __FILES__H
#define __FILES__H
#include "main.h"
#include "inward.h"
#include "sales_bill.h"
#define MAX_STR 150

typedef struct Item_master_info{
	const gchar *name, *code, *unit, *vat, *sale_rate, *group, *category;
}Item_master_info;

typedef struct Item_master_update{
	GtkWidget  *txt_vat, *txt_rate, *label_code2, *label_group2;
}Item_master_update;

void write_g_master_info(const gchar *group);
void write_c_master_info(const gchar *category);
void write_item_master_info(Item_master_info *info);
void item_master_write_update(GtkWidget *widget, Item_master_update *item_master);
void write_inward_bill(GtkWidget *widget, Inward_bill *inward_bill);
void write_sales_bill(GtkWidget *widget, Sales_bill *sales_bill);

#endif
