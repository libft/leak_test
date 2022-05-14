MAKEFLAGS += --no-builtin-rules
Q := $(if $(filter 1,$(V) $(VERBOSE)),,@)
MAKE := $(MAKE) $(if $(filter 1,$(V) $(VERBOSE)),,--no-print-directory)

CPPFLAGS += -I../../src/include
CFLAGS ?= -g3
VARIANT ?= address

.PHONY: all clean fclean test
all: test
clean:
	$Qrm -f *.o *.a *.exe
fclean: clean
test:
	$Q$(MAKE) test.$(VARIANT).exe
	$Q./test.$(VARIANT).exe | sort | diff expected_result.txt -

test.address.exe: CFLAGS += -fsanitize=address
test.memory.exe: CFLAGS += -fsanitize=memory
test.undefined.exe: CFLAGS += -fsanitize=undefined

../../src/libft_leak_test.%.a:
	$Q$(MAKE) -C $(@D) $(@F)

test.%.exe: main.c ../../src/libft_leak_test.%.a
	$Q$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^
