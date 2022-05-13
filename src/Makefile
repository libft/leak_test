SRCS := $(shell find . -maxdepth 1 -type f -name "*.c")
NAME := leak_test

all:
	$(MAKE) -k libft_$(NAME).none.a libft_$(NAME).address.a libft_$(NAME).memory.a libft_$(NAME).undefined.a

%.none.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -g3
%.address.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -fsanitize=address -g3
%.memory.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -fsanitize=memory -g3
%.undefined.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -fsanitize=undefined -g3

libft_$(NAME).%.a: $(SRCS:.c=.%.o)
	$(AR) $(ARFLAGS) $@ $^
