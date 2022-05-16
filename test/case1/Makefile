MAKEFLAGS += --no-builtin-rules
Q := $(if $(filter 1,$(V) $(VERBOSE)),,@)
MAKE := $(MAKE) $(if $(filter 1,$(V) $(VERBOSE)),,--no-print-directory)

CC := clang
CPPFLAGS += -I../../src/include
CFLAGS := -g3
ARFLAGS := crs

.PHONY: all clean fclean test
all: test
clean:
	$Qrm -f *.exe
fclean: clean
	$Qrm -f *.o *.a
test:
	$Q$(MAKE) test.address.exe && ./test.address.exe | sort | diff expected_result.txt -

.PHONY: target_address
target_address:
	$Q$(MAKE) -C ../../src libft_leak_test.address.a

SRCS := $(shell find . -maxdepth 1 -type f -name '*.c')

%.address.o: %.c
	$Q$(CC) $(CFLAGS) $(CPPFLAGS) -fsanitize=address -c -o $@ $<

lib.address.a: $(SRCS:.c=.address.o)
	$Q$(AR) $(ARFLAGS) $@ $^

test.address.exe: target_address
	$Q$(CC) -fsanitize=address -o $@ lib.address.a ../../src/libft_leak_test.address.a
