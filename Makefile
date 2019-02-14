
# https://gcc.gnu.org/onlinedocs/gcc/Instrumentation-Options.html
UBSAN_FLAGS = -fno-sanitize-recover -fsanitize=undefined -fsanitize=leak -fsanitize=address

# m32:
# Build a 32-bit program because the source relies on that in some places
CFLAGS=-m32 -Wall -Wextra -g3 $(UBSAN_FLAGS)
LDFLAGS=-m32 $(UBSAN_FLAGS)

all: rbf-validate
rbf-validate: rbf-validate.o validate.o

clean:
	rm -f rbf-validate *.o
