CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude
SRCS = src/list.c src/stack.c src/queue.c src/main.c
OBJS = $(SRCS:.c=.o)
TARGET = app

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)	
