CFLAGS := -std=c11 -Wall -Wextra -Werror -Wpedantic
CC := clang

all: uninstall libmx

libmx:
	$(CC) $(CFLAGS) -c src/*.c
	mkdir obj
	mv *.o obj
	ar -rc libmx.a obj/*.o
	ranlib libmx.a

clean:
	rm -rdf obj
	rm -rf *.o

uninstall: clean
	rm -f libmx.a

reinstall:
	make uninstall
	make


