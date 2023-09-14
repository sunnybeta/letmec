CC = cc
CFLAGS = -ggdb -Wall -Werror -Wextra
LDFLAGS =

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

all: dirs proto

dirs:
	mkdir -p ./bin

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

proto: $(OBJ)
	$(CC) -o bin/$@ $^ $(LDFLAGS)

clean:
	rm -rf ./bin $(OBJ)
