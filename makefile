CC = gcc

RAYLIB_PATH = C:/vcpkg/installed/x64-windows/
CFLAGS = -I$(RAYLIB_PATH)include -I.
LDFLAGS = -L$(RAYLIB_PATH)lib -lraylib -lopengl32 -lgdi32 -lwinmm

TARGET = program
SRC = $(wildcard *.c)

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC) $(CFLAGS) $(LDFLAGS)

clean:
	del $(TARGET).exe
