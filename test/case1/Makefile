MAKEFLAGS += --no-builtin-rules
Q := $(if $(filter 1,$(V) $(VERBOSE)),,@)
MAKE := $(MAKE) $(if $(filter 1,$(V) $(VERBOSE)),,--no-print-directory)

CC := clang
CPPFLAGS += -I../../src/include
CFLAGS := -Wall -Wextra -Werror -std=c99 -pedantic
ARFLAGS := crs

.PHONY: all clean fclean test
all: test
clean:
	$Qrm -f *.exe
fclean: clean
	$Qrm -f *.o *.a
test:
	$Q[ -f ../../src/libft_leak_test.none.a ] && $(MAKE) test.none.exe && ./test.none.exe | sort | diff expected_result.txt -
	-$Q[ -f ../../src/libft_leak_test.address.a ] && $(MAKE) test.address.exe && ./test.address.exe | sort | diff expected_result.txt -
	-$Q[ -f ../../src/libft_leak_test.memory.a ] && $(MAKE) test.memory.exe && ./test.memory.exe | sort | diff expected_result.txt -
	-$Q[ -f ../../src/libft_leak_test.undefined.a ] && $(MAKE) test.undefined.exe && ./test.undefined.exe | sort | diff expected_result.txt -

.PHONY: target_none target_address target_memory target_undefined

SRCS := $(shell find . -maxdepth 1 -type f -name '*.c')

%.none.o: %.c
	$Q$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
%.address.o: %.c
	$Q$(CC) $(CFLAGS) $(CPPFLAGS) -fsanitize=address -c -o $@ $<
%.memory.o: %.c
	$Q$(CC) $(CFLAGS) $(CPPFLAGS) -fsanitize=memory -c -o $@ $<
%.undefined.o: %.c
	$Q$(CC) $(CFLAGS) $(CPPFLAGS) -fsanitize=undefined -c -o $@ $<

lib.none.a: $(SRCS:.c=.none.o)
lib.address.a: $(SRCS:.c=.address.o)
lib.memory.a: $(SRCS:.c=.memory.o)
lib.undefined.a: $(SRCS:.c=.undefined.o)
%.a:
	$Q$(AR) $(ARFLAGS) $@ $^

test.none.exe: lib.none.a
	$Q$(CC) -o $@ lib.none.a ../../src/libft_leak_test.none.a
test.address.exe: lib.address.a
	$Q$(CC) -fsanitize=address -o $@ lib.address.a ../../src/libft_leak_test.address.a
test.memory.exe: lib.memory.a
	$Q$(CC) -fsanitize=memory -o $@ lib.memory.a ../../src/libft_leak_test.memory.a
test.undefined.exe: lib.undefined.a
	$Q$(CC) -fsanitize=undefined -o $@ lib.undefined.a ../../src/libft_leak_test.undefined.a
