#include <gtk/gtk.h>
#include "billing.h"
#define MAXIMUM 20
#define YES 1
#define NO 0

static void on_window_close(GtkWidget *widget, gpointer data){
	gtk_main_quit();
}

/*static void generate_row(GtkWidget *widget, gpointer data, int i, int j){

	GtkWidget *label_text_rate[MAXIMUM], *label_text_amt[MAXIMUM];
	GtkWidget *text_sr[MAXIMUM], *text_barcode[MAXIMUM], *text_description[MAXIMUM], *text_qty[MAXIMUM];
	
	text_sr[i] = gtk_entry_new();
	text_barcode[i] = gtk_entry_new();
	text_description[i] = gtk_entry_new();
	text_qty[i] = gtk_entry_new();
	label_text_rate[i] = gtk_label_new(NULL);
	label_text_amt[i] = gtk_label_new(NULL);
		
	gtk_label_set_text(GTK_LABEL(label_text_rate[i]), "rate");
	gtk_label_set_text(GTK_LABEL(label_text_amt[i]), "abC");
		
	gtk_grid_attach(GTK_GRID(widget), text_sr[i], 0, j, 1, 1);
	gtk_grid_attach(GTK_GRID(widget), text_barcode[i], 1, j, 1, 1);
	gtk_grid_attach(GTK_GRID(widget), text_description[i], 2, j, 1, 1);
	gtk_grid_attach(GTK_GRID(widget), text_qty[i], 3, j, 1, 1);
	gtk_grid_attach(GTK_GRID(widget), label_text_rate[i], 4, j, 1, 1);
	gtk_grid_attach(GTK_GRID(widget), label_text_amt[i], 5, j, 1, 1);

	return;
}*/

static void activate(GtkApplication *app, gpointer data){
	GtkWidget *window, *billing_grid;
	GtkWidget *label_title, *label_date, *label_invoice_no, *label_txt_invoice_no, *label_sr, *label_barcode, *label_description, *label_qty, *label_rate, *label_amt, 			  *label_total, *label_res, *label_text_rate[MAXIMUM], *label_text_amt[MAXIMUM];
	GtkWidget *text_date, *text_sr[MAXIMUM], *text_barcode[MAXIMUM], *text_description[MAXIMUM], *text_qty[MAXIMUM]; 
	
	int flag = YES, i = 0, j;
	
	/*Create the window and set all its attributes.*/
	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "Billing Screen");
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
		
	/*Create a grid and keep adding various components to it.*/
	billing_grid = gtk_grid_new();
	
	gtk_container_add(GTK_CONTAINER(window), billing_grid);
	
	/*This is the label which displays the title on the page.*/
	label_title = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label_title), "<u><b><big>Billing Form</big></b></u>\n");
	//gtk_widget_set_halign(label_title, GTK_ALIGN_CENTER);
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
		text_description[i] = gtk_entry_new();
		text_qty[i] = gtk_entry_new();
		label_text_rate[i] = gtk_label_new(NULL);
		label_text_amt[i] = gtk_label_new(NULL);
			
		gtk_label_set_text(GTK_LABEL(label_text_rate[i]), "abc");
		gtk_label_set_text(GTK_LABEL(label_text_amt[i]), "xyz");	
		
		gtk_grid_attach(GTK_GRID(billing_grid), text_sr[i], 0, j, 1, 1);
		gtk_grid_attach(GTK_GRID(billing_grid), text_barcode[i], 1, j, 1, 1);
		gtk_grid_attach(GTK_GRID(billing_grid), text_description[i], 2, j, 1, 1);
		gtk_grid_attach(GTK_GRID(billing_grid), text_qty[i], 3, j, 1, 1);
		gtk_grid_attach(GTK_GRID(billing_grid), label_text_rate[i], 4, j, 1, 1);
		gtk_grid_attach(GTK_GRID(billing_grid), label_text_amt[i], 5, j, 1, 1);
		
		i++;
		j++;

	}while(i < 20);
	
	gtk_grid_attach(GTK_GRID(billing_grid), label_total, 4, j, 1, 1);
	gtk_grid_attach(GTK_GRID(billing_grid), label_res, 5, j, 1, 1);
	
	gtk_widget_show_all(window);
}


int main(int argc, char *argv[]){
	GtkApplication *app;
	int status;
	
	app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);
	
	g_signal_connect(app, "destroy", G_CALLBACK(on_window_close), NULL);
	return status;
}
