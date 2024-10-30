CC = clang
CFLAGS = -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic 
LFLAGS = 
EXEC = xd
OTHE = bad_xd
TEST = tests

all: $(EXEC) $(OTHE)

$(EXEC): $(EXEC).o 
	$(CC) $^ $(LFLAGS) -o $@

$(OTHE): $(OTHE).o
	$(CC) $^ $(LFLAGS) -o $@


$(EXEC).o: $(EXEC).c
	$(CC) $(CFLAGS) -c $<

$(OTHE).o: $(OTHE).c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf $(EXEC) *.o
	rm -rf $(OTHE) *.o

format:
	clang-format -i -style=file *.[ch]
test: $(TEST)
	bash runner.sh
.PHONY: all clean format

