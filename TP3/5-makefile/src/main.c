#include <stdlib.h>
#include <stdio.h>
#include "foo.h"
#include "../libtab/tab.h"

int main(int argc, char**argv) {
  TYPE n = foo();
  int tab_size = 10;
  int tab[tab_size];
  saisir_tab(tab, tab_size);  
  printf("%d\n", n);
  return EXIT_SUCCESS;
}
