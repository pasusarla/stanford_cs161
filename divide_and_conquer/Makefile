all: fast_multiplication count_inversions

fast_multiplication: fast_multiplication.c
	$(CC) $? -lgmp -Og -o $@

count_inversions: count_inversions.c
	$(CC) $? -Og -o $@

clean:
	rm -f fast_multiplication count_inversions
