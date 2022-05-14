MAKEFLAGS += --no-builtin-rules
Q := $(if $(filter 1,$(V) $(VERBOSE)),,@)

DIST_DIR ?= dist

.PHONY: all clean test
all: test
clean:
	$Q$(MAKE) -C src fclean
	$Q$(MAKE) -C test clean
fclean:
	$Q$(MAKE) -C src fclean
	$Q$(MAKE) -C test fclean
	$Qrm -rf $(DIST_DIR)
test:
	$Q$(MAKE) -C test test

.PHONY: sources
sources: test
	$Q$(MAKE) -C src fclean
	$Qrm -rf $(DIST_DIR)
	$Q$(MAKE) $(DIST_DIR)/sources.zip $(DIST_DIR)/sources.tar.gz $(DIST_DIR)/sources.bz2 $(DIST_DIR)/sources.xz $(DIST_DIR)/sources.lzma
$(DIST_DIR):
	$Qmkdir -p $@
$(DIST_DIR)/sources.zip: | $(DIST_DIR)
	$Qcd src && zip -q -9 -r ../$@ .
$(DIST_DIR)/sources.tar.gz: | $(DIST_DIR)
	$Qcd src && tar -c -z -m -f ../$@ .
$(DIST_DIR)/sources.bz2: | $(DIST_DIR)
	$Qcd src && tar -c -j -m -f ../$@ .
$(DIST_DIR)/sources.xz: | $(DIST_DIR)
	$Qcd src && tar -c -J -m -f ../$@ .
$(DIST_DIR)/sources.lzma: | $(DIST_DIR)
	$Qcd src && tar -c --lzma -m -f ../$@ .
