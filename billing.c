#include <gtk/gtk.h>
#include "project.h"
#include "billing.h"

int main(int argc, char *argv[]){
	GtkApplication *app;
	int status;
	
	app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);
	
	g_signal_connect(app, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	return status;
}
