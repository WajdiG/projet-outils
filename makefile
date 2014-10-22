BlackJack: main.o fonction.o
	gcc main.o fonction.o -o BlackJack
	
fonction.o: fonction.c
	gcc -c fonction.c
	
main.o: main.c
	gcc -c main.c
