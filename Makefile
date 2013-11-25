bookorder: library
	gcc -pthread main.c -L. -l bookorder -o bookorder

library: bookorder.o 
	ar rcs libbookorder.a bookorder.o

bookorder.o:
	gcc -c bookorder.c -o bookorder.o

clean:
	rm *.a
	rm *.o
	rm bookorder
