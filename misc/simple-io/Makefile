CC := gcc

build: prebuild files copy raw std

files:
	touch bar

prebuild:
	@echo "Running Project..."

copy: copy.c
	$(CC) $^ -o $@.out

raw: raw.c
	$(CC) $^ -o $@.out

std: std.c
	$(CC) $^ -o $@.out

clean: *.out
	@rm $^
