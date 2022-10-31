all:
	gcc rm.c -o rm
	gcc ls.c -o ls
	gcc mkdir.c -o mkdir
	gcc date.c -o date
	gcc cat.c -o cat
	gcc -lpthread -o shell shell.c
	
