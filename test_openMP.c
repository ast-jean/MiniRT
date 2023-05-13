
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define PARALLEL_FOR_REDUCTION_TOTAL _Pragma("omp parallel for reduction(+:total)")

void fill_array(int *arr, int n) {
  for (int i = 0; i < n; i++) {
    arr[i] = i + 1;
  }
}

int compute_sum(int *arr, int n) {
  int total = 0;
  
  PARALLEL_FOR_REDUCTION_TOTAL
  for (int i = 0; i < n; i++) {
    total += arr[i];
  }

  return total;
}

int main() {
  int N = 1000000;
  int *arr = (int *)malloc(N * sizeof(int));
  int total = 0;
  
  fill_array(arr, N);
  total = compute_sum(arr, N);
  printf("La somme des éléments du tableau est: %d\n", total);

  free(arr);
  return 0;
}
