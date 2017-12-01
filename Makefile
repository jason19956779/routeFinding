CC := gcc
DBGR := gdb
CFLAG := -std=c99 -g
BUILDDIR := ./
SOURCE := route.c
BIN := route

default: $(SOURCE)
	$(CC) $(CFLAG) $(SOURCE) -o $(BIN)
test: $(BIN)
	$(BUILDDIR)$(BIN)
debug: $(BIN)
	$(DBGR) $(BIN)
clean:
	@rm -rf $(BIN)
