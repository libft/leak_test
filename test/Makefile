MAKEFLAGS += --no-builtin-rules
Q := $(if $(filter 1,$(V) $(VERBOSE)),,@)
MAKE := $(MAKE) $(if $(filter 1,$(V) $(VERBOSE)),,--no-print-directory)
CASES := $(sort $(wildcard case*))
RULES := test clean fclean
CORES := $(shell sh scripts/nproc.sh)

all: test
re:
	$Q$(MAKE) fclean
	$Q$(MAKE) all
.PHONY: all $(RULES) re
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

test: prepare_test
.PHONY: prepare_test
prepare_test:
	$Q$(MAKE) -C ../src re
	@printf "\033[93m[INFO]\033[0m Test is prepared.\n"

