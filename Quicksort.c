#include <stdio.h>
#include <stdlib.h>
#define LEN 10
void quick_sort(int[], int, int);

int main(void) {
  int list[LEN] = {1, 9, 6, 3, 19, 5, 7, 9, 2, 13};
  quick_sort(list, 0, LEN);
  return 1;
}

void quick_sort(int list[], int L, int R) {
  int left = L;
  int right = R;
  int pivot = (L + R) / 2;
  do {
    while (list[left] < list[pivot]) {
      left++;
    }
    while (list[right] > list[pivot]) {
      right--;
    }
    if (left <= right) {
      printf("pivot : %2d  ,left : %2d, right : %2d //", list[pivot], left, right);
      int temp = list[left];
      list[left] = list[right];
      list[right] = temp;
      left++;
      right--;

      for (int i = 0; i < LEN; i++) {
        printf("%3d ", list[i]);
      }
      printf("\n");
    }
  } while (left <= right);
  if (L < right) {
    quick_sort(list, L, right);
  }
  if (left < R) {
    quick_sort(list, left, R);
  }
}
