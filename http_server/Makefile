CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude
SRCS = src/main.c src/handler.c src/file.c src/log.c
OBJS = $(SRCS:.c=.o)
TARGET = http_server
LDFLAGS = -lpthread

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
