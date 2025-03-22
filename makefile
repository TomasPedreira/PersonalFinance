CC = gcc

RAYLIB_PATH = C:/vcpkg/installed/x64-windows/
CFLAGS = -I$(RAYLIB_PATH)include -Iinclude
LDFLAGS = -L$(RAYLIB_PATH)lib -lraylib -lopengl32 -lgdi32 -lwinmm

TARGET = program
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, build/%.o, $(SRC))

all: build $(TARGET)

build:
	mkdir build

$(TARGET): $(OBJ)
	$(CC) -o build/$(TARGET).exe $(OBJ) $(LDFLAGS)

build/%.o: src/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	del /q build\*.o
	del /q build\$(TARGET).exe
	rmdir /q /s build
