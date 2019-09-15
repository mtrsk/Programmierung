CC := gcc
CFLAGS = -Wall
LIBS =

SRC = $(wildcard *.c)
PROGS = $(patsubst %.c,%,$(SRC))

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) -o $@.out $<

clean: *.out
	@rm $^

.PHONY: clean
