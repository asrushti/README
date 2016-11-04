project: group_master.c category_master.c main_prog.c main.h files.c files.h item_master.c sales_bill.c inward_bill.c inward.h sales_bill.h project.h
	gcc main.c main_prog.c files.c group_master.c category_master.c item_master.c sales_bill.c inward_bill.c -o project `pkg-config --cflags --libs gtk+-3.0`

