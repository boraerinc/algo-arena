#include <vector>
#include <utility>

template <typename T>
void NewBubbleSort(std::vector<T>& vec, bool ascending = true) {
  bool done = false;
  size_t n = vec.size(); // illustrative purposes
  while (done == false) {
    done = true;
    for(size_t ndx = 1; ndx <= n-1; ++ndx) { // loops of the style of the 
                                             // CLRS textbook
      if(ascending) {
        if (vec[ndx - 1] > vec[ndx]) {
          std::swap(vec[ndx-1], vec[ndx]);
          done = false;
        }
      } else {
        if (vec[ndx - 1] < vec[ndx]) {
          std::swap(vec[ndx-1], vec[ndx]);
          done = false;
        }
      }
    }
  }
}


