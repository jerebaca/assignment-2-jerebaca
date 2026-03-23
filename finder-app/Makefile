# Compiler (supports cross-compilation)
CC := $(CROSS_COMPILE)gcc

# Compiler flags
CFLAGS := -Wall -Werror

# Target binary
TARGET := writer

# Source files
SRC := writer.c

# Object files
OBJ := $(SRC:.c=.o)

# Default target
all: $(TARGET)

# Link the application
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Compile source to object
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(TARGET) $(OBJ)

.PHONY: all clean