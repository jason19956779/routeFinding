CC = gcc
CFLAG = 

test: route.c
	$(CC) $(CFLAG) route.c -o route
clean:
	@rm -rf route
