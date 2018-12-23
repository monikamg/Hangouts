COMP=gcc
TARGET=c_client
CFLAGS= -std=c89 -pedantic -Wall -Werror -lpthread
MLINK= -o
FILES= ./src/client.c

c_client: $(FILES)
	$(COMP) $(MLINK) $(TARGET) $(CFLAGS) $(FILES)