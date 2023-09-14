# Let Me C

*A large personal reference file for the C programming language.*

## Build System

### Bash

```bash
#!/bin/bash

set -xe

mkdir -p ./bin

CC="cc"
CFLAGS="-ggdb -Wall -Werror -Wextra"
SRC="src"
BIN="bin"

$CC $CFLAGS -o $BIN/main $SRC/main.c
```

### Makefile

```make
CC = cc
CFLAGS = -ggdb -Wall -Werror -Wextra
LDFLAGS =

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
BIN = bin

all: dirs proto

dirs:
	mkdir -p ./bin

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $(BIN)/$@ $^ $(LDFLAGS)

clean:
	rm -rf $(BIN) $(OBJ)
```

### Hello World

Always create a hello_world program before starting a new project and make sure your build system works correctly.

```c
#include <stdio.h>

int main(int argc, char **argv) {
    printf("Hello, World!\n");
    return 0;
}
```

## Header Guards

Ensure that your header files are wrapped within header guards.

```c
#ifndef HEADER_H_
#define HEADER_H_

/* code goes here */

#endif /* HEADER_H_ */
```
