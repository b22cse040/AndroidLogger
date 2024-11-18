CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lcurl
SRC = logger.c sms_simulator.c call_simulator.c app_simulator.c main.c
OBJ = $(SRC:.c=.o)
EXE = simulator

# Default target to build the executable
all: $(EXE)

# Build the executable from object files
$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $(EXE) $(LDFLAGS)

# Compile .c files to .o object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and the executable
clean:
	rm -f $(OBJ) $(EXE)

# Create a distribution tarball with source files and the Makefile
dist: clean
	tar czf simulator.tar.gz $(SRC) Makefile

# Run the executable
run: $(EXE)
	./$(EXE)

# Reminder to load .env variables manually
loadenv:
	@echo "Load .env variables manually using a tool like `source .env` or edit the file directly"

.PHONY: all clean dist run loadenv
