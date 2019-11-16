#include <iostream>
#include <algorithm>

const int NUM_ITEMS { 8 };

bool isSorted(int arr[], int toIx) {
  for (int ix = 1; ix < toIx; ix++) {
    if (arr[ix - 1] > arr[ix]) {
      return false;
    }
  }
  return true;
}

void insertionSort(int arr[NUM_ITEMS]) {
  for (int ix = 1; ix < NUM_ITEMS; ix++) {
    int jx = ix;
    while (jx > 0 && arr[jx - 1] > arr[jx])
    {
      int temp = arr[jx];
      arr[jx] = arr[jx - 1];
      arr[jx - 1] = temp;
      jx--;
    }
    assert(isSorted(arr, ix));
  }
}

int main() {
  int nums[NUM_ITEMS] = { 5, 12, 7, 3, 11, 1, -4, 3 };
  insertionSort(nums);
  assert(isSorted(nums, NUM_ITEMS));
  std::cout << "good job!" << std::endl;
}