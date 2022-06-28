
CC=gcc
SRCS=$(wildcard *.c)
HEADERS=$(wildcard *.h)
OBJS=$(SRCS:.c=.o)
OBJSWITHDIR=$(addprefix obj/, $(OBJS))
CFLAGS=-Wall -Wextra -Werror
CTARGETFLAGS=-lm -rdynamic -Wall -Wextra -Werror
TARGET=rlTutorial

.PHONY: clean

all: target

target: obj $(OBJSWITHDIR)
	$(CC) $(OBJSWITHDIR) $(CTARGETFLAGS) -o $(TARGET)

obj:
	mkdir -p obj

obj/%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf obj
	rm -rf $(TARGET)

