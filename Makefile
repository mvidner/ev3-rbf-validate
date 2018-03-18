# Build a 32-bit program because the source relies on that in some places
CFLAGS=-m32 -Wall -g3
LDFLAGS=-m32

rbf-validate: rbf-validate.o validate.o

clean:
	rm -f rbf-validate *.o
