MAKEFLAGS += --no-builtin-rules
Q := $(if $(filter 1,$(V) $(VERBOSE)),,@)
MAKE := $(MAKE) $(if $(filter 1,$(V) $(VERBOSE)),,--no-print-directory)

NAME := leak_test
VARIANTS := none address memory undefined

.PHONY: all $(addprefix libft_leak_test.,$(VARIANTS:=.a))
all: $(addprefix libft_leak_test.,$(VARIANTS:=.a))
libft_leak_test.none.a:
	$Q$(MAKE) -C .build $@ && cp .build/$@ $@ || echo "Failed to build $@"
libft_leak_test.address.a:
	$Q$(MAKE) -C .build $@ && cp .build/$@ $@ || echo "Failed to build $@"
libft_leak_test.memory.a:
	$Q$(MAKE) -C .build $@ && cp .build/$@ $@ || echo "Failed to build $@"
libft_leak_test.undefined.a:
	$Q$(MAKE) -C .build $@ && cp .build/$@ $@ || echo "Failed to build $@"

.PHONY: clean fclean all
clean:
	$Q$(MAKE) -C .build clean
fclean:
	$Q$(MAKE) -C .build fclean
	$Qrm -f *.a
re: fclean
	$Q$(MAKE) all
