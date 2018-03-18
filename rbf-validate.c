#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include "bytecodes.h"
#include "lmstypes.h"
#include "validate.h"

void usage(void) {
  fprintf(stderr, "Usage: rbf-validate [-d] file.rbf\n");
}

unsigned char *read_file(char *filename) {
  struct stat sb;

  if (stat(filename, &sb) == -1) {
    perror("stat");
    exit(EXIT_FAILURE);
  }
  off_t size = sb.st_size;

  unsigned char *buffer = malloc(size);
  if (buffer == NULL) {
    fprintf(stderr, "Could not allocate %lu bytes\n", size);
    exit(EXIT_FAILURE);
  }

  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }
  size_t got = fread(buffer, 1, size, f);
  if (got != (size_t) size) {
    fprintf(stderr, "Expected %lu bytes but read only %zu\n", size, got);
    exit(EXIT_FAILURE);
  }

  if (fclose(f) == -1) {
    perror("fclose");
    exit(EXIT_FAILURE);
  }

  return buffer;
}

int main(int argc, char *argv[]) {
  int disassemble = 0;
  int opt;

  while ((opt = getopt(argc, argv, "d")) != -1) {
    switch (opt) {
    case 'd':
      disassemble = 1;
      break;
    default: /* '?' */
      usage();
      exit(EXIT_FAILURE);
    }
  }

  if (optind >= argc) {
    usage();
    exit(EXIT_FAILURE);
  }

  unsigned char *buffer = read_file(argv[optind]);

  PRGID prg_id = 0; // unused by the routine
  LABEL *p_label = NULL; // ?

  RESULT r;
  r = cValidateProgram(prg_id, buffer, p_label, disassemble);

  printf("Result: %u\n", r);
  printf("Row: %u, ValidateErrorIndex: %u\n",
          ValidateInstance.Row, ValidateInstance.ValidateErrorIndex);

  return r;
}
