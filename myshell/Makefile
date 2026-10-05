CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = myshell

all: $(TARGET)

$(TARGET): myshell.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGET)
