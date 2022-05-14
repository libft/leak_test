MAKEFLAGS += --no-builtin-rules
Q := $(if $(filter 1,$(V) $(VERBOSE)),,@)
MAKE := $(MAKE) $(if $(filter 1,$(V) $(VERBOSE)),,--no-print-directory)

NAME := leak_test
VARIANTS := none address memory undefined

.PHONY: all $(VARIANTS) $(addprefix libft_leak_test.,$(VARIANTS:=.a))
all: $(VARIANTS)
libft_leak_test.%.a: %
$(VARIANTS): %:
	$Q$(MAKE) -C .build libft_$(NAME).$@.a && cp .build/libft_$(NAME).$@.a libft_$(NAME).$@.a || echo "Failed to build libft_$(NAME).$@.a"

.PHONY: clean fclean all
clean:
	$Q$(MAKE) -C .build clean
fclean:
	$Q$(MAKE) -C .build fclean
	$Qrm -f *.a
re: fclean
	$Q$(MAKE) all
