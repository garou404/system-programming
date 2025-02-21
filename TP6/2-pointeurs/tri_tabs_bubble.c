#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define NB_ELEMENTS 7

// TODO Definissez une fonction compar_short
int compar_short(const void *m1, const void *m2) {
  const short* t1 = (const short*) m1;
  const short* t2 = (const short*) m2;
  if (*t1 < *t2) {
    return -1;
  }else if (*t1 > *t2) {
    return 1;
  }else {
    return 0;
  }
}

// TODO Definissez une fonction compar_double
int compar_double(const void *m1, const void *m2) {
  const double* t1 = (const double*) m1;
  const double* t2 = (const double*) m2;
  if (*t1 < *t2) {
    return -1;
  }else if (*t1 > *t2) {
    return 1;
  }else {
    return 0;
  }
}

// (tab_double, NB_ELEMENTS, sizeof(double), compar_double);
void bubble_sort(void* base, size_t nmemb, size_t size, int (*compar)(const void* c1, const void* c2)) {
  void* temp_val = malloc(size);
  if (!temp_val) return;
  for (size_t i = 0; i < nmemb-1; i++) {
    for (size_t o = 0; o < nmemb-1-i; o++) {
      if(compar(base+o*size, base+(o+1)*size) > 0) {
        memcpy(temp_val, (base+o*size), size);
        memcpy(base+o*size, base+(o+1)*size, size);
        memcpy(base+(o+1)*size, temp_val, size);
      }
    }
  }
  free(temp_val);
}


void print_tab_short(short tab[], size_t nmemb) {
  int i;
  for (i = 0 ; i < nmemb ; i++) {
    printf("tab_short[%d] = %d\n", i, tab[i]);
  }
}

void print_tab_double(double tab[], size_t nmemb) {
  int i;
  for (i = 0 ; i < nmemb ; i++) {
    printf("tab_double[%d] = %lf\n", i, tab[i]);
  }
}

int main(int argc, char** argv){
  short tab_short[NB_ELEMENTS] = {6, 5, 4, 3, 2, 1, 0};
  double tab_double[NB_ELEMENTS] = {7.1, 6.2, 5.3, 4.4, 3.5, 2.6, 1.7};

  printf("tab_short avant tri\n");
  print_tab_short(tab_short, NB_ELEMENTS);
  // TODO : Appelez la fonction qsort
  bubble_sort(tab_short, NB_ELEMENTS, sizeof(short), compar_short);

  printf("tab_short après tri\n");
  print_tab_short(tab_short, NB_ELEMENTS);

  printf("tab_double avant tri\n");
  print_tab_double(tab_double, NB_ELEMENTS);
  // TODO : Appelez la fonction qsort
  bubble_sort(tab_double, NB_ELEMENTS, sizeof(double), compar_double);

  printf("tab_double avant tri\n");
  print_tab_double(tab_double, NB_ELEMENTS);

  return EXIT_SUCCESS;
}
