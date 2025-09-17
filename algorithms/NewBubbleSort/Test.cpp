#include "NewBubbleSort.h"
#include <iostream>

template <typename T>
void printVec(const std::vector<T>& vec) {
  for (const T& item: vec) {
    std::cout << item << ", ";
  }
  std::cout << "\n";

}

int main() {
  std::vector<int> myVec = {2, 6, 2, 9, 11, 3, 0, -1};
  std::cout << "myVec before NewBubbleSort: \n";
  printVec(myVec);
  NewBubbleSort(myVec);
  std::cout << "myVec after NewBubbuleSort: \n";
  printVec(myVec);


}
