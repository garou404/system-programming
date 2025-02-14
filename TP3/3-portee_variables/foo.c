#include <stdio.h>
#include <stdlib.h>

int var_globale = 0;
static int var_globale_static = 0;
static int var_globale_extern;

int main(int argc, char**argv) {
  int a1 = 0;
  static int a2 = 0;

  int result = var_globale + var_globale_static + var_globale_extern;
  printf("%i\n", a1+a2);
  return EXIT_SUCCESS;
}
