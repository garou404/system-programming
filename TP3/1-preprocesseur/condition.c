#include <stdio.h>
#include <stdlib.h>



#ifdef M
#define N M
#else
#define N 12
#endif


#if (N > 10)

void foo() {
  printf("N est très grand (%d)\n", N);
}

#elif (N<5)

void foo() {
  printf("N est très petit (%d)\n", N);
}

#else
void foo() {
  printf("N est très moyen (%d)\n", N);
}

#endif

int main(int argc, char**argv) {

  foo();
  return EXIT_SUCCESS;
}
