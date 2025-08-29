#include <cmath>
#include <cstddef>
#include <initializer_list>

const size_t DEFAULT_SIZE = 10;

template<typename T>
class Vector {
    T* data;
    size_t theSize;
    size_t theCapacity;

    class Iterator {

        T* ptr;

        friend bool operator==(const Iterator& lhs, const Iterator& rhs);

      public:

        Iterator(T* aPtr) : ptr(aPtr) {}

        Iterator operator++(int) {
          Iterator res = *this;
          ++ptr;
          return res;
        }

        Iterator& operator++() {
          ++ptr;
          return *this;
        }

        T& operator*() const {
          return *ptr;
        }
    };

    class Const_Iterator {

        const T* ptr;

        friend bool operator==(const Const_Iterator& lhs, const Const_Iterator& rhs);

      public:

        Const_Iterator(const T* aPtr): ptr(aPtr) {}

        Const_Iterator operator++(int) {
          Const_Iterator res = *this;
          ++ptr;
          return res;
        }

        Const_Iterator& operator++() {
          ++ptr;
          return *this;
        }

        const T& operator*() const {
          return *ptr;
        }
    };


  public:

    Vector(): data(nullptr), theSize(0), theCapacity(0)  {}

    Vector(const T& val, size_t theSize) : theSize(theSize), theCapacity(theSize), data(new T[theSize]) {
      for(size_t ndx = 0; ndx < theSize; ++ndx) {
        data[ndx] = val;
      }
    }

    Vector(std::initializer_list<T> vals): theSize(vals.size()), theCapacity(theSize), data(new T[theCapacity]) {
      size_t ndx = 0;
      for(const T& val : vals) {
        data[ndx++] = val;
      }
    }

    ~Vector() {
      delete[] data;
    }

    Vector(const Vector& rhs) : theSize(rhs.theSize), theCapacity(rhs.theCapacity), data(new T[rhs.theCapacity]) {
      for(size_t ndx = 0; ndx < theSize; ++ndx) {
        data[ndx] = rhs.data[ndx];
      }
    }

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

    Vector(Vector&& rhs) noexcept : theSize(rhs.theSize), theCapacity(rhs.theCapacity), data(rhs.data) {
      rhs.data = nullptr;
      rhs.theSize = 0;
      rhs.theCapacity = 0;
    }

    Vector& operator=(Vector&& rhs) noexcept {
      if (this == &rhs) return *this;

      delete[] data;

      theSize = rhs.theSize;
      theCapacity = rhs.theCapacity;
      data = rhs.data;

      rhs.data = nullptr;
      rhs.theSize = 0;
      rhs.theCapacity = 0;

      return *this;
    }

    size_t size() const noexcept {
      return theSize;
    }

    size_t capacity() const noexcept {
      return theCapacity;
    }
  
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
    }

    void push_back(T&& val) {
      if ( theSize == theCapacity ) resize();
      data[theSize] = val;
      ++theSize;
    }

    void pop_back() {
      if(theSize > 0) {
        --theSize;
      }
    }

    T operator[](size_t ndx) const {
      return data[ndx];
    }

    T& operator[](size_t ndx) {
      return data[ndx];
    }

    Const_Iterator begin() const {
      return Const_Iterator(data);
    }

    Iterator begin() {
      return Iterator(data);
    }

    Const_Iterator end() const {
      return Const_Iterator(data+theSize);
    }

    Iterator end() {
      return Iterator(data+theSize);
    }
};

template <typename T>
bool operator==(const typename Vector<T>::Iterator& lhs, const typename Vector<T>::Iterator& rhs) {
 return lhs.ptr == rhs.ptr;  
}

template <typename T>
bool operator!=(const typename Vector<T>::Iterator& lhs, const typename Vector<T>::Iterator& rhs) {
 return !(lhs == rhs);  
}


template <typename T>
bool operator==(const typename Vector<T>::Const_Iterator& lhs, const typename Vector<T>::Const_Iterator& rhs) {
  return lhs.ptr == rhs.ptr;
}

template <typename T>
bool operator!=(const typename Vector<T>::Const_Iterator& lhs, const typename Vector<T>::Const_Iterator& rhs) {
  return !(lhs == rhs);
}
