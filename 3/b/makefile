all: my_digit_cnt

my_digit_cnt:  my_digit_cnt.o
	gcc -g -Wall -o my_digit_cnt my_digit_cnt.o 

my_digit_cnt.o: my_digit_cnt.c
	gcc -g -Wall -c -o my_digit_cnt.o my_digit_cnt.c
	


clean:
	rm -f *.o
 
