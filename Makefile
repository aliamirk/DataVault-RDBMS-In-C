CC = gcc
CFLAGS = -Wall
OBJ = ./build/main.o ./build/menu_operations.o

# Define the target program name and output directory
PROGRAM = ./build/program

all: $(PROGRAM)

$(PROGRAM): $(OBJ)
	$(CC) -o $(PROGRAM) $(OBJ)

# Rule for creating object files, putting them in the ./build folder
./build/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f ./build/*.o $(PROGRAM)
