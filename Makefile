OPTS=-Wall -Wextra -Wpedantic -Werror
EXE=xorshift-star

b:
	@echo "BUILDING..."
	@mkdir -p build/
	$(CC) $(OPTS) -o build/$(EXE) main.c

r: b
	@echo "RUNNING..."
	./build/$(EXE)

c:
	@echo "CLEANING..."
	rm -rf build/
