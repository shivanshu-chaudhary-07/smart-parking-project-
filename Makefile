CC     = gcc
CFLAGS = -std=c11 -Wall -Wextra

parking: src/parking_simple.c
	$(CC) $(CFLAGS) src/parking_simple.c -o parking

test: parking
	sh tests/run_sample.sh

clean:
	rm -f parking parking.exe

.PHONY: test clean
