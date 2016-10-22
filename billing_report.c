#include <gtk/gtk.h>
#include "billing.h"
#include "project.h"

/*gdouble billing_spin_clicked (GtkSpinButton *spin_btn, gpointer data){
	

	gdouble amt += gtk_spin_button_get_value(spin_btn);
	
	return amt;

   //GtkWidget *label = user_data;
   //gdouble value = gtk_spin_button_get_value(spinbutton);

   /* %d - Is used when printing integers.
    * Note: Using g_strdup_printf returns a string that must be freed. 
    * (In which is done below)
    *
   //gchar *str = g_strdup_printf ("The number you selected is %lf.", value);
   //gtk_label_set_text (GTK_LABEL (label), str);

   //g_free(str);
}*/


void activate(GtkApplication *app, gpointer data){
	GtkWidget *window, *billing_grid;
	GtkWidget *label_title, *label_date, *label_invoice_no, *label_txt_invoice_no, *label_sr, *label_barcode, *label_description, *label_qty, *label_rate, *label_amt, *label_total, *label_res, *label_text_rate[MAXIMUM], *label_text_amt[MAXIMUM], *label_text_description[MAXIMUM];
	GtkWidget *text_date, *text_sr[MAXIMUM], *text_barcode[MAXIMUM];
	GtkWidget *billing_spin_btn_qty[MAXIMUM]; 
	GtkAdjustment *billing_spin_btn_adjustment[MAXIMUM];
	
	gdouble amt = 0;
	
	int i = 0, j, total = 0;
	
	/*Create the window and set all its attributes.*/
	window = initialize_window(app);
	
	/*Create a grid and keep adding various components to it.*/
	billing_grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(window), billing_grid);
	
	/*This is the label which displays the title on the page.*/
	label_title = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_title), "<u><b><big>Billing Form</big></b></u>\n");
	gtk_grid_attach(GTK_GRID(billing_grid), label_title , 0, 0, 6, 1);
	
	/*This is the label and text field to fetch the date.*/
	label_date = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_date), "<b>Date : </b>\n");
	gtk_widget_set_halign(label_date, GTK_ALIGN_START);
	
	text_date = gtk_entry_new();
	//gtk_entry_set_text(GTK_ENTRY(text_date), "text filed");
//gtk_label_set_markup(GTK_LABEL(label_title), "<b>Date : </b>");
	gtk_grid_attach(GTK_GRID(billing_grid), label_date, 0, 1,  1, 1);		
	gtk_grid_attach(GTK_GRID(billing_grid), text_date, 1, 1, 1, 1);
	
	/*Label and text field to fetch the invoice number.*/
	label_invoice_no = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_invoice_no), "<b>Invoice # : </b>\n");
	gtk_widget_set_halign(label_invoice_no, GTK_ALIGN_START);
	
	label_txt_invoice_no = gtk_label_new("11111");
	gtk_grid_attach(GTK_GRID(billing_grid), label_invoice_no, 4, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(billing_grid), label_txt_invoice_no, 5, 1, 1, 1);
	
	/*Components in the table*/
	label_sr = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_sr), "<b>Sr #  </b>\n");
	label_barcode = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_barcode), "<b>Barcode </b>\n");
	label_description = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_description), "<b> Item Description </b>\n");
	label_qty = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_qty), "<b>   QTY </b>\n");
	label_rate = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_rate), "<b>Rate</b>\n");
	label_amt = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_amt), "<b>Amt</b>\n");
	label_total = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_total), "<b>Total : </b>\n");
	label_res = gtk_label_new(NULL);
	
	//gtk_entry_set_has_frame(GTK_ENTRY(label_sr), TRUE);
	//gtk_label_set_xalign(GTK_LABEL(label_sr), 3.3);
	gtk_grid_attach(GTK_GRID(billing_grid), label_sr, 0, 3, 1, 1);
	gtk_grid_attach(GTK_GRID(billing_grid), label_barcode, 1, 3, 1, 1);
	gtk_grid_attach(GTK_GRID(billing_grid), label_description, 2, 3, 1, 1);
	gtk_grid_attach(GTK_GRID(billing_grid), label_qty, 3, 3, 1, 1);
	gtk_grid_attach(GTK_GRID(billing_grid), label_rate, 4, 3, 1, 1);
	gtk_grid_attach(GTK_GRID(billing_grid), label_amt, 5, 3, 1, 1);
	//gtk_grid_attach(GTK_GRID(billing_grid), label_total, 5, 3, 1, 1);
  	
	j = 4;
	do{
		text_sr[i] = gtk_entry_new();
		text_barcode[i] = gtk_entry_new();
		//text_description[i] = gtk_entry_new();
		//text_qty[i] = gtk_entry_new();
		
		/* Create an adjustment representing an adjustable bounded value */
	  	billing_spin_btn_adjustment[i] = gtk_adjustment_new (0, 0, 1000, 1, 0, 0);
		/* Create a spin button that is to be as wide as possible */
  		billing_spin_btn_qty[i] = gtk_spin_button_new (billing_spin_btn_adjustment[i], 1, 0);
  		gtk_widget_set_hexpand (billing_spin_btn_qty[i], TRUE);
		
		label_text_description[i] = gtk_label_new(NULL);
		label_text_rate[i] = gtk_label_new(NULL);
		label_text_amt[i] = gtk_label_new(NULL);
		
		gtk_label_set_text(GTK_LABEL(label_text_description[i]), "description");		
		
		gtk_grid_attach(GTK_GRID(billing_grid), text_sr[i], 0, j, 1, 1);
		gtk_grid_attach(GTK_GRID(billing_grid), text_barcode[i], 1, j, 1, 1);
		gtk_grid_attach(GTK_GRID(billing_grid), label_text_description[i], 2, j, 1, 1);
		gtk_grid_attach(GTK_GRID(billing_grid), billing_spin_btn_qty[i], 3, j, 1, 1);
		gtk_grid_attach(GTK_GRID(billing_grid), label_text_rate[i], 4, j, 1, 1);
		gtk_grid_attach(GTK_GRID(billing_grid), label_text_amt[i], 5, j, 1, 1);
		
		gtk_label_set_text(GTK_LABEL(label_text_rate[i]), "0.00");
		gtk_label_set_text(GTK_LABEL(label_text_amt[i]), "0.00");

		i++;
		j++;

	}while(i < 20);
	/*i = 0;
      	while(i < 20){
		amt = g_signal_connect (billing_spin_btn_qty[i], "value-changed", G_CALLBACK (billing_spin_clicked), NULL);
		printf("%lf\n", amt);
		i++;	
	}*/
	
	gtk_grid_attach(GTK_GRID(billing_grid), label_total, 4, j, 1, 1);
	gtk_grid_attach(GTK_GRID(billing_grid), label_res, 5, j, 1, 1);
	
	gtk_widget_show_all(window);
}

