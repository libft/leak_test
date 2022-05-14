MAKEFLAGS += --no-builtin-rules
Q := $(if $(filter 1,$(V) $(VERBOSE)),,@)
MAKE := $(MAKE) $(if $(filter 1,$(V) $(VERBOSE)),,--no-print-directory)

NAME := leak_test
VARIANTS := none address memory undefined

.PHONY: all $(VARIANTS)
all: $(VARIANTS)
$(VARIANTS): %:
	$Q$(MAKE) -C .build libft_$(NAME).$@.a && cp .build/libft_$(NAME).$@.a libft_$(NAME).$@.a || echo "Failed to build libft_$(NAME).$@.a"

.PHONY: clean fclean all
clean:
	$Q$(MAKE) -C .build clean
fclean:
	$Q$(MAKE) -C .build fclean
re: fclean
	$Q$(MAKE) all
