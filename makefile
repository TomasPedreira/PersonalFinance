CC = gcc

RAYLIB_PATH = ../raylib
CFLAGS = -I$(RAYLIB_PATH)/include -I.
LDFLAGS = -L$(RAYLIB_PATH)/lib -lraylib -lGL -lGLU -lm -lpthread -ldl -lrt -lX11

TARGET = program
SRC = $(wildcard *.c)

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(TARGET)
