CC := gcc
LD := gcc
LDFLAGS :=
CCFLAGS := -Wall -Wextra

SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)

TARGET := tests

all: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CCFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJS)
