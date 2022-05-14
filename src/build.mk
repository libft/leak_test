MAKEFLAGS += --no-builtin-rules
Q := $(if $(filter 1,$(V) $(VERBOSE)),,@)
MAKE := $(MAKE) $(if $(filter 1,$(V) $(VERBOSE)),,--no-print-directory)

SRCS := $(shell find .. -maxdepth 1 -type f -name "*.c")
NAME := leak_test

CC ?= clang
CFLAGS ?= -Wall -Wextra -Werror -std=c99 -pedantic -g3

CPPFLAGS := -I../include
ARFLAGS := cr$(if $(filter 1,$(V) $(VERBOSE)),v,s)

.PHONY: clean fclena
clean:
	$Qrm -f *.o
fclean: clean
	$Qrm -f *.a

%.none.o: ../%.c
	$Q$(CC) $(CFLAGS) -c $< -o $@
%.address.o: ../%.c
	$Q$(CC) $(CFLAGS) -c $< -o $@ -fsanitize=address
%.memory.o: ../%.c
	$Q$(CC) $(CFLAGS) -c $< -o $@ -fsanitize=memory
%.undefined.o: ../%.c
	$Q$(CC) $(CFLAGS) -c $< -o $@ -fsanitize=undefined

libft_$(NAME).none.a: $(patsubst ../%.c,%.none.o,$(SRCS))
libft_$(NAME).address.a: $(patsubst ../%.c,%.address.o,$(SRCS))
libft_$(NAME).memory.a: $(patsubst ../%.c,%.memory.o,$(SRCS))
libft_$(NAME).undefined.a: $(patsubst ../%.c,%.undefined.o,$(SRCS))
%.a:
	$Q$(AR) $(ARFLAGS) $@ $^
