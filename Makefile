all: bit_counter

bit_counter: bit_counter.c
	gcc -o bit_counter bit_counter.c -lpthread

clean:
	rm -f bit_counter