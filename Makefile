CC = gcc
CFLAGS = -Wall
OBJ = ./build/main.o ./build/menu_operations.o ./build/library-functions.o ./build/table_operations.o ./build/record_operations.o

# Define the target program name and output directory
PROGRAM = ./build/program

all: $(PROGRAM)

$(PROGRAM): $(OBJ)
	$(CC) -o $(PROGRAM) $(OBJ)

# Creating object files and putting them in the ./build folder
./build/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f ./build/*.o $(PROGRAM)
