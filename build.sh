#!/bin/bash

set -xe

mkdir -p ./bin

CC="cc"
CFLAGS="-ggdb -Wall -Werror -Wextra"
SRC="src"
BIN="bin"

$CC $CFLAGS -o $BIN/main $SRC/main.c
