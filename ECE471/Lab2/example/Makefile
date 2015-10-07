CC = g++
INCLUDES = -I../include
LIBS = -L../lib -lmatrix
CFLAGS = $(INCLUDES)

EXECUTABLES =  testMatrix Lab2

.PHONY: all clean

all: $(EXECUTABLES)

Lab2: Lab2.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)


testMatrix: testMatrix.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f *.o $(EXECUTABLES)

%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@
