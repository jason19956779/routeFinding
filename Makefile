CC = gcc
CFLAG = -std=c99

test: route.c
	$(CC) $(CFLAG) route.c -o route
clean:
	@rm -rf route
