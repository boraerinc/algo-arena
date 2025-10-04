#include <cmath>
#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>

template <typename T>
struct DLLNode {
  T m_Data;
  DLLNode* m_Prev;
  DLLNode* m_Next;

  // L-Value constructor
  DLLNode<T>(const T& data, T* prev = nullptr, T* next = nullptr) : m_Data(data),
    m_Prev(prev), m_Next(next) {}
  
  // R-value constructor
  DLLNode<T>(T&& data, T* prev = nullptr, T* next = nullptr) : m_Data(std::move(data)),
    m_Prev(prev), m_Next(next) {}
};

template<typename T>
class DoublyLinkedList {

  struct Iterator {
    DLLNode<T>* m_Ptr;
    Iterator(DLLNode<T>* ptr) : m_Ptr(ptr) {}

    Iterator& operator++(int) {
      Iterator res = *this;
      m_Ptr = m_Ptr->m_Next;
      return res;
    }

    Iterator& operator++() {
      m_Ptr = m_Ptr->m_Next;
      return *this;
    }

    T& operator*() const { // is this const??
      return m_Ptr->m_Data;
    }

    T& operator->() const { // is this const??
      return m_Ptr->m_Data;
    }

    friend bool operator==(const Iterator& lhs, const Iterator& rhs) {
      return lhs.m_Ptr == rhs.m_Ptr;
    }
    friend bool operator!=(const Iterator& lhs, const Iterator& rhs) {
      return lhs.m_Ptr != rhs.m_Ptr;
    }
  };

  struct Const_Iterator {
    const DLLNode<T>* m_Ptr;
    Const_Iterator(const DLLNode<T>* ptr) : m_Ptr(ptr) {}
    Const_Iterator(Iterator it) : m_Ptr(it.m_Ptr) {}

    Const_Iterator& operator++(int) {
      Const_Iterator res = *this;
      m_Ptr = m_Ptr->m_Next;
      return res;
    }

    Const_Iterator& operator++() {
      m_Ptr = m_Ptr->m_Next;
      return *this;
    }

    const T& operator*() const {
      return m_Ptr;
    }
    const T& operator->() const {
      return m_Ptr; 
    }
    friend bool operator==(const Const_Iterator& lhs, const Const_Iterator& rhs) {
      return lhs.m_Ptr == rhs.m_Ptr;
    }
    friend bool operator!=(const Const_Iterator& lhs, const Const_Iterator& rhs) {
      return lhs.m_Ptr != rhs.m_Ptr;
    }
  };

  friend bool operator==(const Iterator& lhs, const Iterator &rhs);
  
  friend bool operator==(const Const_Iterator& lhs, const Const_Iterator &rhs);

  DLLNode<T>* m_Head;
  DLLNode<T>* m_Tail;
  size_t m_Size;

public:
  //Default Constructor
  DoublyLinkedList(): m_Head(nullptr), m_Tail(nullptr), m_Size(0) {}

  // Construct given a valid node
  DoublyLinkedList(DLLNode<T>* head) : m_Head(head), m_Tail(nullptr), m_Size(0) {
    if(m_Head != nullptr) {
      if(m_Head->m_Prev != nullptr) {
        // throw invalid param error
      }
      DLLNode<T>* curr = m_Head;
      while (curr->m_Next != nullptr) {
        ++m_Size;
        curr = curr->m_Next;
      }
      m_Tail = curr;
    }
  }

  // Copy constructor
  DoublyLinkedList(const DoublyLinkedList<T>& rhs) {
    for(const DLLNode<T>& node: rhs) {
      this->push_front(node);
    }
  }

  void cleanup() {
    DLLNode<T>* curr = m_Head;
    while(curr != nullptr) {
      DLLNode<T>* prev = curr;
      curr = curr->m_Next;
      delete prev;
    }
    m_Head = nullptr;
    m_Tail = nullptr;
    m_Size = 0;
  }

  ~DoublyLinkedList(){
    cleanup();
  }

  // Assignment operator
  DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& rhs) {
    // Check for self assignment
    if(this == &rhs) {
      return *this;
    }

    // Free up resources
    cleanup();

    // Copy over new resources
    for(const DLLNode<T>& node: rhs) {
      this->push_front(*node);
    }

    // Return new object
    return *this;
  }
 
  // Move assignment operator
  DoublyLinkedList<T>& operator=(DoublyLinkedList<T>&& rhs) noexcept {
    // Check for self assignment
    if(this == &rhs) {
      return *this;
    }
    
    // Steal resources
    m_Head = rhs.m_Head;
    m_Tail = rhs.m_Tail;
    m_Size = rhs.m_Size;

    // Leave other object in usable state
    rhs.m_Head = nullptr;
    rhs.m_Tail = nullptr;
    rhs.m_Size = 0;

    // Return new object
    return *this;
  }

  // Move Constructor
  DoublyLinkedList<T>(DoublyLinkedList&& rhs) noexcept : m_Head(rhs.m_Head), m_Tail(rhs.m_Tail), m_Size(rhs.m_Size) {
    rhs.m_Head = nullptr;
    rhs.m_Tail = nullptr;
    rhs.m_Size = 0;
  }

  // Utilities
  bool empty() const noexcept {
    return m_Size == 0;
  }

  size_t size() const noexcept {
    return m_Size;
  }

  void push_front(const T& rhs) {
    if(empty()) {
      m_Head = new DLLNode<T>(rhs, nullptr, nullptr);
      m_Tail = m_Head;
    } else {
      m_Head->m_Prev = new DLLNode<T>(rhs, nullptr, m_Head);
    }
    ++m_Size;
  }
  
  void push_front(T&& rhs) {
    if(empty()) {
      m_Head = new DLLNode<T>(rhs, nullptr, nullptr);
      m_Tail = m_Head;
    } else {
      m_Head->m_Prev = new DLLNode<T>(rhs, nullptr, m_Head);
    }
    ++m_Size;
  }

  void push_back(const T& rhs) {
    if(empty()) {
      m_Head = new DLLNode<T>(rhs, nullptr, nullptr);
      m_Tail = m_Head;
    } else {
      m_Tail->m_Next = new DLLNode<T>(rhs, m_Tail, nullptr);
    }
    ++m_Size;
  }
  
  void push_back(T&& rhs) {
    if(empty()) {
      m_Head = new DLLNode<T>(rhs, nullptr, nullptr);
      m_Tail = m_Head;
    } else {
      m_Tail->m_Next = new DLLNode<T>(rhs, m_Tail, nullptr);
    }
    ++m_Size;
  }

  void pop_front() {
    DLLNode<T>* curr = m_Head; 
    m_Head = m_Head->m_Next;
    m_Head->m_Prev = nullptr;
    delete curr;
    --m_Size;
  }

  void pop_back() {
    DLLNode<T>* curr = m_Tail; 
    m_Tail = m_Tail->m_Prev;
    m_Tail->m_Next = nullptr;
    delete curr;
    --m_Size;
  }

  const T& front() const {
    if(m_Head == nullptr) {
      throw std::out_of_range("Tried to use front() on an empty list! \n");
    }
    return m_Head->m_Data;
  }

  T& front() {
    if(m_Head == nullptr) {
      throw std::out_of_range("Tried to use front() on an empty list! \n");
    }
    return m_Head->m_Data;
  }
  
  const T& back() const {
    if(m_Tail == nullptr) {
      throw std::out_of_range("Tried to use front() on an empty list! \n");
    }
    return m_Tail->m_Data;
  }

  T& back() {
    if(m_Tail == nullptr) {
      throw std::out_of_range("Tried to use front() on an empty list! \n");
    }
    return m_Tail->m_Data;
  }

  DoublyLinkedList(const std::initializer_list<T>& list) : m_Head(nullptr), m_Tail(nullptr), m_Size(0) {
    for(const T& item: list) {
      push_front(item);
    }
  }

  // Iterators

  Iterator begin() {
    return Iterator(m_Head);
  }

  Const_Iterator begin() const {
    return Const_Iterator(m_Head);
  }

  Const_Iterator cbegin() const {
    return Const_Iterator(m_Head);
  }

  Iterator end() {
    return Iterator(m_Tail);
  }
  Const_Iterator end() const {
    return Const_Iterator(m_Tail);
  }
  Const_Iterator cend() const {
    return Const_Iterator(m_Tail);
  }
  
};
