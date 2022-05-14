MAKEFLAGS += --no-builtin-rules
Q := $(if $(filter 1,$(V) $(VERBOSE)),,@)

.PHONY: all clean test
all: test
clean:
	$Q$(MAKE) -C src fclean
	$Q$(MAKE) -C test clean
test:
	$Q$(MAKE) -C test test

.PHONY: sources
sources: test
	$Q$(MAKE) -C src fclean
	$Qrm -rf dist
	$Q$(MAKE) dist/sources.zip dist/sources.tar.gz dist/sources.bz2 dist/sources.xz dist/sources.lzma
dist:
	$Qmkdir -p $@
dist/sources.zip: | dist
	$Qcd src && zip -q -9 -r ../$@ .
dist/sources.tar.gz: | dist
	$Qcd src && tar -c -z -m -f ../$@ .
dist/sources.bz2: | dist
	$Qcd src && tar -c -j -m -f ../$@ .
dist/sources.xz: | dist
	$Qcd src && tar -c -J -m -f ../$@ .
dist/sources.lzma: | dist
	$Qcd src && tar -c --lzma -m -f ../$@ .
