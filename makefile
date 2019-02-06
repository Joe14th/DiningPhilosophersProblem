all: A B C
A: part1.o
	gcc -pthread -o part1 part1.c
B: part2.o 
	gcc -pthread -o part2 part2.c
C: part3.o 
	gcc -pthread -o part3 part3.c

clean:
	rm -f part1 *.o
	rm -f part2 *.o
	rm -f part3 *.o
