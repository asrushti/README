#include <gtk/gtk.h>
#include "project.h" 

GtkWidget *initialize_window(GtkApplication *app){
	GtkWidget *window;
	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "Billing Screen");
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);	
	//g_signal_connect (window, "destroy",G_CALLBACK (gtk_main_quit), NULL);
	return window;
}

