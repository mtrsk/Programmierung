CC := gcc

build: prebuild files copy

files:
	touch bar

prebuild:
	@echo "Running Project..."

copy: copy.c
	$(CC) $^ -o $@.out

clean: *.out
	@rm $^
