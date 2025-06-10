CC = gcc
CFLAGS = -Wall -I/usr/include
LDFLAGS = -L/usr/lib/x86_64-linux-gnu -lssh
SRC = pi_nas.c
OUT = pi_nas

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $(OUT) $(SRC) $(LDFLAGS)

clean:
	rm -f $(OUT)