MAKEFLAGS += --no-builtin-rules
Q := $(if $(filter 1,$(V) $(VERBOSE)),,@)
MAKE := $(MAKE) $(if $(filter 1,$(V) $(VERBOSE)),,--no-print-directory)
CASES := $(sort $(wildcard case*))
RULES := all test clean fclean
CORES := $(shell sh scripts/nproc.sh)

.PHONY: $(RULES)
define build_common_rule
$1:
	$Q$(foreach t,$(CASES),$(MAKE) -C $t -j $(CORES) $1 && )true
endef
$(foreach r, \
	$(RULES), \
	$(eval $(call \
		build_common_rule, \
		$r \
	)) \
)
