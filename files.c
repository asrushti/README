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
 
#include <stdio.h>
#include <gtk/gtk.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "files.h"

void write_g_master_info(const gchar *group){
	int size_grp;
	FILE *fp;
	char grp[MAX_STR];
	
	/*Open the file to which the data is to be written*/
	fp = fopen("data/GroupMaster.txt", "a+");
	
	strcpy(grp, (char *)group);

	/*Return if the user has not entered any value but pressed space key*/
	if(grp[0] == ' ')
		return;
	size_grp = strlen(grp);
	
	fwrite(&size_grp, sizeof(int), 1, fp);
	fprintf(fp, "%s", grp);
	
	/*Close the file.*/
	fclose(fp);	
	
	return;
}

void write_c_master_info(const gchar *category){
	int size_cat;
	FILE *fp;
	char cat[MAX_STR];
	
	/*Open the file to which the data is to be written*/
	fp = fopen("data/CategoryMaster.txt", "a+");
	
	strcpy(cat, (char *)category);
	/*Return if the user has not entered any value but pressed space key*/
	if(cat[0] == ' ')
		return;
	size_cat = strlen(cat);
	
	fwrite(&size_cat, sizeof(int), 1, fp);
	fprintf(fp, "%s", cat);
	
	/*Close the file.*/
	fclose(fp);
	
	return;	
}

void write_item_master_info(Item_master_info *info){
	int size_name, size_grp, size_cat, size_unit;
	FILE *fp2;
	char name[MAX_STR], grp[MAX_STR], cat[MAX_STR], file_name[MAX_STR], unit[MAX_STR];
	long long int code;
	float vat, sale_rate;
	char padding = 'p';
	
	fp2 = fopen("data/ItemMaster.txt", "a+");
	
	strcpy(name, (char *)info->name);
	strcpy(grp, (char *)info->group);
	strcpy(cat, (char *)info->category);
	strcpy(unit, (char *)info->unit);
	
	/*Evaluate the length of strings so that they can be written before the strings.*/
	size_name = strlen(name);
	size_grp = strlen(grp);
	size_cat = strlen(cat);
	size_unit = strlen(unit);
	
	/*Convert the data from string to their respective types.*/
	code = atoll(info->code);
	vat = atof(info->vat);
	sale_rate = atof(info->sale_rate);
	
	/*Write data to common item master*/
	fwrite(&code, sizeof(long long int), 1, fp2);
	fwrite(&padding, sizeof(char), 1, fp2);
	fwrite(&size_grp, sizeof(int), 1, fp2);
	fprintf(fp2, "%s", grp);
	fwrite(&size_cat, sizeof(int), 1, fp2);
	fprintf(fp2, "%s", cat);
	fwrite(&size_name, sizeof(int), 1, fp2);
	fprintf(fp2, "%s", name);
	fwrite(&vat, sizeof(float), 1, fp2);
	fwrite(&sale_rate, sizeof(float), 1, fp2);
	fwrite(&size_unit, sizeof(int), 1, fp2);
	fprintf(fp2, "%s", unit);
	
	fclose(fp2);
	
	return;
}

void item_master_write_update(GtkWidget *widget, Item_master_update *item_master_update){
	FILE *fp1;
	const gchar *group;
	char group_file[MAX_STR], *group1, *category1, *name1, *unit1, ch;
	float vat, vat1, rate, rate1;
	long long int code, code1;
	int size_name, size_group, size_cat, size_unit;

	/*Fetch the selection from every field*/
	group = gtk_label_get_text((GtkLabel *)item_master_update->label_group2);
	vat = atof(gtk_entry_get_text((GtkEntry *)item_master_update->txt_vat));
	rate = atof(gtk_entry_get_text((GtkEntry *)item_master_update->txt_rate));
	code = atoll(gtk_label_get_text((GtkLabel *)item_master_update->label_code2));
	
	/*Open ItemMaster.txt and the respective group file*/
	fp1 = fopen("data/ItemMaster.txt", "r+w");
	
	g_print("Inside Item Master write update.\n");

	/*Update the record in both the file*/
	
	while(fread(&code1, sizeof(long long int), 1, fp1)){
		
		fread(&ch, sizeof(char), 1, fp1);
		fread(&size_group, sizeof(int), 1, fp1);
		group1 = (char *)malloc(sizeof(char) * size_group + 1);
		fread(group1, sizeof(char), size_group, fp1);
		group1[size_group] = '\0';
		
		fread(&size_cat, sizeof(int), 1, fp1);
		category1 = (char *)malloc(sizeof(char) * size_cat + 1);
		fread(category1, sizeof(char), size_cat, fp1);
		category1[size_cat] = '\0';
		
		fread(&size_name, sizeof(int), 1, fp1);
		name1 = (char *)malloc(sizeof(char) * size_name + 1);
		fread(name1, sizeof(char), size_name, fp1);
		name1[size_name] = '\0';
		
		if(code == code1){
			fwrite(&vat, sizeof(float), 1, fp1);
			fwrite(&rate, sizeof(float), 1, fp1);
		}
		else{
			fread(&vat1, sizeof(float), 1, fp1);
			fread(&rate1, sizeof(float), 1, fp1);
		}
		
		fread(&size_unit, sizeof(int), 1, fp1);
		unit1 = (char *)malloc(sizeof(char) * size_unit + 1);
		fread(unit1, sizeof(char), size_unit, fp1);
		unit1[size_unit] = '\0';
	}
	
	fclose(fp1);
	return;
}

void write_inward_bill(GtkWidget *widget, Inward_bill *inward_bill){
	FILE *fp;
	char ch = 'c';
	int size_iname, size_pname, size_cat, size_unit, i = 0;
	long long int code, code1, purchase_no, supplier_ino;
	char *group, *category, *name, *unit, vat_str[MAX_STR], amt_str[30], total_str[30], code_str[16], party_name[MAX_STR], item_name[MAX_STR];
	float vat, rate, rate1;
	long int qty;
	double total, amt, vat_amt;
	
	fp = fopen("data/InwardMaster.txt", "a+");
	
	if(gtk_entry_get_text((GtkEntry *)inward_bill->txt_purchase_no))
		purchase_no = atoll(gtk_entry_get_text((GtkEntry *)inward_bill->txt_purchase_no));
	if(gtk_entry_get_text((GtkEntry *)inward_bill->txt_supplier_ino))
		supplier_ino = atoll(gtk_entry_get_text((GtkEntry *)inward_bill->txt_supplier_ino));
	if(gtk_entry_get_text((GtkEntry *)inward_bill->txt_party_name))
		strcpy(party_name, gtk_entry_get_text((GtkEntry *)inward_bill->txt_party_name));
	
	/*Write the records to the file.*/
	fwrite(&purchase_no, sizeof(long long int), 1, fp);
	fwrite(&ch, sizeof(char), 1, fp);
		
	fwrite(&supplier_ino, sizeof(long long int), 1, fp);
	fwrite(&ch, sizeof(char), 1, fp);
		
	size_pname = strlen(party_name);
	fwrite(&size_pname, sizeof(int), 1, fp);
	fprintf(fp, "%s", party_name);
	
	/*Traverse all the records that the user has entered.*/
	while(*gtk_entry_get_text((GtkEntry *)inward_bill->inward_new[i]->combo_code) != '\0'){
			code = atoll(gtk_entry_get_text((GtkEntry *)inward_bill->inward_new[i]->combo_code));
		if(gtk_label_get_text(GTK_LABEL(inward_bill->inward_new[i]->label_txt_item_name)))
			strcpy(item_name, gtk_label_get_text(GTK_LABEL(inward_bill->inward_new[i]->label_txt_item_name)));
		if(gtk_entry_get_text((GtkEntry *)inward_bill->inward_new[i]->txt_inward_qty))
			qty = atol(gtk_entry_get_text((GtkEntry *)inward_bill->inward_new[i]->txt_inward_qty));
		if(gtk_entry_get_text((GtkEntry *)inward_bill->inward_new[i]->txt_inward_rate))
			rate = atof(gtk_entry_get_text((GtkEntry *)inward_bill->inward_new[i]->txt_inward_rate));
		if(gtk_label_get_text(GTK_LABEL(inward_bill->inward_new[i]->label_txt_inward_vat)))
			vat = atof(gtk_label_get_text(GTK_LABEL(inward_bill->inward_new[i]->label_txt_inward_vat)));
		if(gtk_label_get_text(GTK_LABEL(inward_bill->inward_new[i]->label_txt_inward_amt)))
			amt = atof(gtk_label_get_text(GTK_LABEL(inward_bill->inward_new[i]->label_txt_inward_amt)));
		fwrite(&ch, sizeof(char), 1, fp);
		fwrite(&code, sizeof(long long int), 1, fp);
		fwrite(&ch, sizeof(char), 1, fp);
		
		size_iname = strlen(item_name);
		fwrite(&size_iname, sizeof(int), 1, fp);
		fprintf(fp, "%s", item_name);
		
		fwrite(&qty, sizeof(long int), 1, fp);
		fwrite(&ch, sizeof(char), 1, fp);
		fwrite(&rate, sizeof(float), 1, fp);
		fwrite(&vat, sizeof(float), 1, fp);
		fwrite(&amt, sizeof(double), 1, fp);
	
		/*Reset the fields*/
		gtk_entry_set_text((GtkEntry *)inward_bill->inward_new[i]->combo_code, " ");
		gtk_label_set_text(GTK_LABEL(inward_bill->inward_new[i]->label_txt_item_name), " ");
		gtk_entry_set_text((GtkEntry *)inward_bill->inward_new[i]->txt_inward_qty, " ");
		gtk_entry_set_text((GtkEntry *)inward_bill->inward_new[i]->txt_inward_rate, " ");
		gtk_label_set_text(GTK_LABEL(inward_bill->inward_new[i]->label_txt_inward_vat), " ");
		gtk_label_set_text(GTK_LABEL(inward_bill->inward_new[i]->label_txt_inward_amt), " ");
		i++;	
	}
	
	if(gtk_label_get_text(GTK_LABEL(inward_bill->label_txt_inward_total))){
		total = atof(gtk_label_get_text(GTK_LABEL(inward_bill->label_txt_inward_total)));
		fwrite(&total, sizeof(double), 1, fp);	
	}
	
	/*Reset all the fields.*/
	gtk_entry_set_text((GtkEntry *)inward_bill->txt_purchase_no, " ");
	gtk_entry_set_text((GtkEntry *)inward_bill->txt_supplier_ino, " ");
	gtk_entry_set_text((GtkEntry *)inward_bill->txt_party_name, " ");
	gtk_label_set_text(GTK_LABEL(inward_bill->label_txt_inward_total), "0");
			
	fclose(fp);
	return;
}

void write_sales_bill(GtkWidget *widget, Sales_bill *sales_bill){
	FILE *fp;
	char ch = 'c';
	int size_iname, size_pname, size_cat, size_unit, i = 0;
	long long int code, code1, invoice_no, supplier_ino;
	char *group, *category, *name, *unit, vat_str[MAX_STR], amt_str[30], total_str[30], code_str[16], party_name[MAX_STR], item_name[MAX_STR];
	float vat, rate, rate1;
	long int qty;
	double total, amt, vat_amt;
	
	fp = fopen("data/SalesMaster.txt", "a+");
	if(gtk_entry_get_text((GtkEntry *)sales_bill->txt_invoice_no)){
		invoice_no = atoll(gtk_entry_get_text((GtkEntry *)sales_bill->txt_invoice_no));
		fwrite(&invoice_no, sizeof(long long int), 1, fp);
		fwrite(&ch, sizeof(char), 1, fp);
	}
	
	/*Traverse all the records that the user has entered.*/
	while(*gtk_entry_get_text((GtkEntry *)sales_bill->sales_new[i]->txt_code) != '\0'){
	
			code = atoll(gtk_entry_get_text((GtkEntry *)sales_bill->sales_new[i]->txt_code));
			
		if(gtk_label_get_text(GTK_LABEL(sales_bill->sales_new[i]->label_txt_item_name)))
			strcpy(item_name, gtk_label_get_text(GTK_LABEL(sales_bill->sales_new[i]->label_txt_item_name)));
			
		if(gtk_entry_get_text((GtkEntry *)sales_bill->sales_new[i]->txt_sales_qty))
			qty = atol(gtk_entry_get_text((GtkEntry *)sales_bill->sales_new[i]->txt_sales_qty));
			
		if(gtk_label_get_text(GTK_LABEL(sales_bill->sales_new[i]->label_sales_rate)))
			rate = atof(gtk_label_get_text(GTK_LABEL(sales_bill->sales_new[i]->label_sales_rate)));
			
		if(gtk_label_get_text(GTK_LABEL(sales_bill->sales_new[i]->label_txt_sales_vat)))
			vat = atof(gtk_label_get_text(GTK_LABEL(sales_bill->sales_new[i]->label_txt_sales_vat)));
			
		if(gtk_label_get_text(GTK_LABEL(sales_bill->sales_new[i]->label_txt_sales_amt)))
			amt = atof(gtk_label_get_text(GTK_LABEL(sales_bill->sales_new[i]->label_txt_sales_amt)));
			
		fwrite(&ch, sizeof(char), 1, fp);
		fwrite(&code, sizeof(long long int), 1, fp);
		fwrite(&ch, sizeof(char), 1, fp);
		
		size_iname = strlen(item_name);
		fwrite(&size_iname, sizeof(int), 1, fp);
		fprintf(fp, "%s", item_name);
		
		fwrite(&qty, sizeof(long int), 1, fp);
		fwrite(&ch, sizeof(char), 1, fp);
		fwrite(&rate, sizeof(float), 1, fp);
		fwrite(&vat, sizeof(float), 1, fp);
		fwrite(&amt, sizeof(double), 1, fp);
	
		/*Reset the fields*/
		gtk_entry_set_text((GtkEntry *)sales_bill->sales_new[i]->txt_code, " ");
		gtk_label_set_text(GTK_LABEL(sales_bill->sales_new[i]->label_txt_item_name), " ");
		gtk_entry_set_text((GtkEntry *)sales_bill->sales_new[i]->txt_sales_qty, " ");
		gtk_label_set_text(GTK_LABEL(sales_bill->sales_new[i]->label_sales_rate), " ");
		gtk_label_set_text(GTK_LABEL(sales_bill->sales_new[i]->label_txt_sales_vat), " ");
		gtk_label_set_text(GTK_LABEL(sales_bill->sales_new[i]->label_txt_sales_amt), " ");
		i++;	
	}
	
	if(gtk_label_get_text(GTK_LABEL(sales_bill->label_txt_total))){
		total = atof(gtk_label_get_text(GTK_LABEL(sales_bill->label_txt_total)));
		fwrite(&total, sizeof(double), 1, fp);	
		gtk_label_set_text(GTK_LABEL(sales_bill->label_txt_total), " ");
	}
	/*Reset invoice no. and total field.*/
	
	gtk_entry_set_text((GtkEntry *)sales_bill->txt_invoice_no, "0");
	fclose(fp);
	return;
}

