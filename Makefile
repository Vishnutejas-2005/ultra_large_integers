CC = gcc  # Change this if you use a different compiler
CFLAGS = -O3 -Wall -shared -fPIC  # Flags for warnings, shared library, PIC

# Target to create the shared library
all: uint.so

# Rule to compile and link the shared library
uint.so: uint.o
	$(CC) $(CFLAGS) -o uint.so uint.o

# Rule to compile the C source code
uint.o: uint.c
	$(CC) $(CFLAGS) -c uint.c

# Rule to clean up (remove object file and shared library)
clean:
	rm -f uint.so *.o