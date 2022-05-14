MAKEFLAGS += --no-builtin-rules
Q := $(if $(filter 1,$(V) $(VERBOSE)),,@)
MAKE := $(MAKE) $(if $(filter 1,$(V) $(VERBOSE)),,--no-print-directory)

NAME := leak_test
VARIANTS := none address memory undefined

BUILDDIR ?= .build

.PHONY: all $(addprefix libft_leak_test.,$(VARIANTS:=.a))
all: $(addprefix libft_leak_test.,$(VARIANTS:=.a))
libft_leak_test.none.a: $(BUILDDIR)/Makefile
	$Q$(MAKE) -C $(BUILDDIR) $@ && cp $(BUILDDIR)/$@ $@ || echo "Failed to build $@"
libft_leak_test.address.a: $(BUILDDIR)/Makefile
	$Q$(MAKE) -C $(BUILDDIR) $@ && cp $(BUILDDIR)/$@ $@ || echo "Failed to build $@"
libft_leak_test.memory.a: $(BUILDDIR)/Makefile
	$Q$(MAKE) -C $(BUILDDIR) $@ && cp $(BUILDDIR)/$@ $@ || echo "Failed to build $@"
libft_leak_test.undefined.a: $(BUILDDIR)/Makefile
	$Q$(MAKE) -C $(BUILDDIR) $@ && cp $(BUILDDIR)/$@ $@ || echo "Failed to build $@"

.PHONY: clean fclean all
clean:
	$Qrm -rf $(BUILDDIR)
fclean: clean
	$Qrm -f *.a
re: fclean
	$Q$(MAKE) all

$(BUILDDIR)/Makefile:
	$Qmkdir -p $(BUILDDIR)
	$Qcp build.mk $(BUILDDIR)/Makefile
