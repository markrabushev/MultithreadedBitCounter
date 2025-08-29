all: bit_counter

bit_counter: bit_counter.c
	gcc -o bit_counter bit_counter.c -lpthread

clean:
	rm bit_counter