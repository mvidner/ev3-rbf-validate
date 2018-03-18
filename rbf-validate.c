#include <stdio.h>
#include "bytecodes.h"
#include "lmstypes.h"
#include "validate.h"

int main(int argc, char **argv) {
  unsigned char buffer[10000]; // OMG insecure

  PRGID PrgId = 0;
  LABEL *pLabel = NULL;
  DATA8 Disassemble = 1;

  FILE *f = fopen(argv[1], "r");
  fread(buffer, 1, 10000, f);
  fclose(f);

  RESULT r;
  r = cValidateProgram(PrgId, buffer, pLabel, Disassemble);

  printf("Result: %u\n", r);
  printf("Row: %u, ValidateErrorIndex: %u\n", ValidateInstance.Row, ValidateInstance.ValidateErrorIndex);
  return r;
}
