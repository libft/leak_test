#!/bin/sh

# Linux
CPUS=$(getconf _NPROCESSORS_ONLN 2> /dev/null) ||
# BSD
CPUS=$(getconf NPROCESSORS_ONLN 2> /dev/null) ||
# Solaris
CPUS=$(ksh93 -c 'getconf NPROCESSORS_ONLN' 2> /dev/null) ||
# fallback
CPUS=1

printf "%s" "$CPUS"
