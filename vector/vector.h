// How to use templates in separate compilation
// How to use std::initializer_list
// Should push_back take in a const ref?
// Should pop_back return popped element?
// How is pop_back implemented in the standard library? are there guard rails
// for removing elements at size 0?
// What about push_back at size_t's max value?
// Iterator vs. Const Iterator ?
// Should I still use function declarations and separate definitions 


#include <cmath>
#include <cstddef>
#include <initializer_list>

const size_t DEFAULT_SIZE = 10;

template<typename T>
class Vector{
    T* data;
    size_t theSize;
    size_t theCapacity;

    class Iterator {

        T* ptr;

      public:

        Iterator(T* aPtr) { 

        Iterator operator++(int) {
          Iterator res = *this;
          ++ptr;
          return res;
        };

        Iterator& operator++() {
          ++ptr;
          return *this;
        };

        T& operator*() const {
          return *ptr;
        };
    };

    class Const_Iterator {
      public:
        const T* ptr;

        Const_Iterator operator++(int) {
          Iterator res = *this;
          ++ptr;
          return res;
        };

        Const_Iterator& operator++() {
          ++ptr;
          return *this;
        };

        T operator*() const {
          return *ptr;
        };
    };

  public:
    Vector() : theSize(0), theCapacity(1), data(new T[1]) {}; 

    Vector(const T& val, size_t theSize) : theSize(theSize), theCapacity(theSize + 1), data(new T[theSize]) {
      for(size_t ndx = 0; ndx < theSize; ++ndx) {
        data[ndx] = val;
      }
    };

    Vector(std::initializer_list<T> vals) {

    }; 

    ~Vector() {
      delete[] data;
    };

    Vector(const Vector& rhs) : theSize(rhs.theSize), theCapacity(rhs.theCapacity), data(new T[rhs.theSize]) {
      for(size_t ndx = 0; ndx < theSize; ++ndx) {
        data[ndx] = rhs.data[ndx];
      }
    };

    Vector& operator=(const Vector& rhs) {
      if (this == &rhs) return *this;

      delete[] data;

      data = new T[rhs.theCapacity];

      theSize = rhs.theSize;
      theCapacity = rhs.theCapacity;

      for(size_t ndx = 0; ndx < theSize; ++ndx) {
        data[ndx] = rhs.data[ndx];
      }

      return *this;
    }

    Vector(Vector&& rhs) : theSize(rhs.theSize), theCapacity(rhs.theCapacity), data(rhs.data) {
      rhs.data = nullptr;
    };

    Vector& operator=(Vector&& rhs) {
      if (this == &rhs) return *this;

      delete[] data;

      theSize = rhs.theSize;
      theCapacity = rhs.theCapacity;

      data = rhs.data;

      rhs.data = nullptr;

      return *this;
    };

    size_t size() const {
      return theSize;
    };

    size_t capacity() const {
      return theCapacity;
    };
  
    void resize() {
      if(theSize < theCapacity) return;
      if ( theCapacity == 0 ) ++theCapacity;

      theCapacity = theCapacity*2;

      T* oldData = data;
      
      data = new T[theCapacity];

      for(size_t ndx = 0; ndx < theSize; ++ndx) {
        data[ndx] = oldData[ndx];
      }

      delete[] oldData;
    }

    void push_back(const T& val) {
      if ( theSize == theCapacity ) resize();
      data[theSize] = val;
      ++theSize;
    };

    void push_back(T&& val) {
      if ( theSize == theCapacity ) resize();
      data[theSize] = val;
      ++theSize;
    }

    void pop_back() {
      if(theSize > 0) {
        --theSize;
      }
    };

    T operator[](size_t ndx) const {
      return data[ndx];
    };

    T& operator[](size_t ndx) {
      return data[ndx];
    };

    Const_Iterator begin() const {
      return Const_Iterator(data);
    };

    Iterator begin() {
      return Iterator(data);
    };

    Const_Iterator end() const {
      return Const_Iterator(data+theSize);
    };

    Iterator end() {
      return Iterator(data+theSize);
    };
};
