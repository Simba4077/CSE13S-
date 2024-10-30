CC = clang
CFLAGS = -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic
CFLAGS += -gdwarf-4
LFLAGS = -lm


all: calc graph

graph: graph.o
	$(CC) $^ $(LFLAGS) -o $@


calc: calc.o stack.o mathlib.o operators.o 
	$(CC) $^ $(LFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $<

.PHONY: run_graph
run_graph: graph
	./graph

tests: tests
	bash runner.sh

clean:
	rm -rf calc *.o graph

format:
	clang-format -i -style=file *.[ch]

.PHONY: all clean format

