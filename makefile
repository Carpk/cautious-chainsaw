build: orderManagement.o orderList.o main.h
	gcc main.c orderManagement.o orderList.o -o Project4

orderManagement.o: orderManagement.c orderManagement.h
	gcc -c orderManagement.c

orderList.o: orderList.c orderList.h
	gcc -c orderList.c

clean:
	rm orderManagement.o orderList.o Project4

