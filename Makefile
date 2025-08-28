all: bit_counter

bit_counter: bit_counter.c
	gcc -o bit_counter bit_counter.c

clean:
	rm -f bit_counter