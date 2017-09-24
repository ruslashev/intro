#include<iostream>

static void counting_sort_on_digit(int arr[], int n, int exp) {
  int output[n];
  int count[10] = { 0 };

  for (int i = 0; i < n; i++)
    count[(arr[i] / exp) % 10]++;

  for (int i = 1; i < 10; i++)
    count[i] += count[i - 1];

  for (int i = n - 1; i >= 0; i--) {
    output[count[(arr[i] / exp) % 10] - 1] = arr[i];
    count[(arr[i] / exp) % 10]--;
  }

  for (int i = 0; i < n; i++)
    arr[i] = output[i];
}

void radix_sort(int arr[], int n) {
  int m = arr[0];
  for (int i = 1; i < n; i++)
    if (arr[i] > m)
      m = arr[i];

  for (int exp = 1; m/exp > 0; exp *= 10)
    counting_sort_on_digit(arr, n, exp);
}

