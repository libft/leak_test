MAKEFLAGS += --no-builtin-rules
Q := $(if $(filter 1,$(V) $(VERBOSE)),,@)

.PHONY: all clean test
all: test
clean:
	$Q$(MAKE) -C src fclean
	$Q$(MAKE) -C test clean
test:
	$Q$(MAKE) -C test test
