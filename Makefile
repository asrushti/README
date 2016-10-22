billing_report: project.c billing_report.c billing.c
	gcc project.c billing_report.c billing.c -o billing_report $(pkg-config --cflags --libs gtk+-3.0)
	
