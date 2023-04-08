.PHONY = all clean uninstall reinstall
LIB := libmx.a
SRC := $(wildcard src/*.c)
OBJ := $(patsubst src/%.c,%.o,$(wildcard src/*.c))


all: ULS
ULS: $(OBJ)
	@make -C ./libmx
	@clang -std=c11 -Wall -Werror -Wextra -Wpedantic -o uls $(addprefix ./obj/, $(OBJ)) $(addprefix ./libmx/, $(LIB))
$(OBJ):
	@mkdir -p obj
	@clang -std=c11 -Wall -Werror -Wextra -Wpedantic -c $(SRC)
	@mv $(OBJ) ./obj
clean:
	@rm -f
uninstall: clean
	@rm -f $(LIB)
	@rm -f uls
	@rm -drf obj
reinstall: uninstall ULS
