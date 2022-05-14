MAKEFLAGS += --no-builtin-rules
Q := $(if $(filter 1,$(V) $(VERBOSE)),,@)
MAKE := $(MAKE) $(if $(filter 1,$(V) $(VERBOSE)),,--no-print-directory)

CPPFLAGS := -I../../src
CFLAGS ?= -g3
VARIANT ?= address

.PHONY: all test clean
all: test
test: test.$(VARIANT).exe
	$Q./$< | sort | diff expected_result.txt -
clean:
	$Qrm -f *.o *.a *.exe

test.address.exe: CFLAGS += -fsanitize=address
test.memory.exe: CFLAGS += -fsanitize=memory
test.undefined.exe: CFLAGS += -fsanitize=undefined

.PHONY: ../../src/libft_leak_test.address.a
../../src/libft_leak_test.%.a:
	$Q$(MAKE) -C $(@D) $(@F)

test.%.exe: main.c ../../src/libft_leak_test.%.a
	$Q$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^
