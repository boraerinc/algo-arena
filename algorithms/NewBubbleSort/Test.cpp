#include "NewBubbleSort.h"
#include <iostream>

template <typename T>
void printVec(const Vector<T>& vec) {
  for (const T& item: vec) {
    std::cout << item << ", ";
  }
  std::cout << "\n";
}

int main() {
  Vector<int> myVec = {2, 6, 2, 9, 11, 3, 0, -1};

  std::cout << "myVec before NewBubbleSort: \n";
  printVec(myVec);

  NewBubbleSort(myVec);

  std::cout << "myVec after NewBubbleSort: \n";
  printVec(myVec);

  NewBubbleSort(myVec, false);
  
  std::cout << "myVec after NewBubbleSort (descending) \n";
  printVec(myVec);
}
