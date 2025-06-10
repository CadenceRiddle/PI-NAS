CC = gcc
CFLAGS = -Wall -I/usr/include
SRC = pi_nas.c
OUT = pi_nas

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $(OUT) $(SRC)

clean:
	rm -f $(OUT)