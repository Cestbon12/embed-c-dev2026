CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude
SRCS = src/main.c src/parse.c src/builtins.c src/execute.c
OBJS = $(SRCS:.c=.o)
TARGET = myshell

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
