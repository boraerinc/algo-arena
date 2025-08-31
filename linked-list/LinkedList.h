#include <cassert>
#include <vector>
#include <iostream>

// should a singly linked list even have a "head" member?
// or should it just be the node itself?
// If it has a head, then should that head act as padding,
// holding no data but just pointing to the first element?
// Should LinkedListNodes have move semantics?
// How do you handle something like `T data` in a move oeprator?
// You can't set values to nullptr, nor can you call a destructor on them.

template <typename T>
struct LinkedListNode {
  T data;
  LinkedListNode* next;

  LinkedListNode(const T& val, LinkedListNode* ptr = nullptr): data(val), next(ptr) {}
};

template <typename T>
class LinkedList {
  // iterator class
  class Iterator {
    public:
    LinkedListNode<T>* m_ptr;

    Iterator(LinkedListNode<T>* aPtr) : m_ptr(aPtr) {}

    Iterator& operator++() {
      m_ptr = m_ptr->next;
      return *this;
    }

    Iterator operator++(int) {
      Iterator res(*this);
      m_ptr = m_ptr->next;
      return res;
    }
    
    T& operator*() const {
      return m_ptr->data;
    }

    friend bool operator==(const Iterator& lhs, const Iterator& rhs);
  };


  class Const_Iterator {
    public:
    const LinkedListNode<T>* m_ptr;

    Const_Iterator(LinkedListNode<T>* aPtr) : m_ptr(aPtr) {}

    Const_Iterator& operator++() {
      m_ptr = m_ptr->next;
      return *this;
    }

    Const_Iterator operator++(int) {
      Const_Iterator res(*this);
      m_ptr = m_ptr->next;
      return res;
    }
    
    T operator*() const {
      return m_ptr->data;
    }

    friend bool operator==(const Const_Iterator& lhs, const Const_Iterator& rhs);

  };
      
  // const iterator class
  LinkedListNode<T>* head;

  size_t m_size;

public:
  
  LinkedList<T>() : head(nullptr), m_size(0) { }

  ~LinkedList<T>() {
    LinkedListNode<T>* curr = head;
    while(curr != nullptr) {
      LinkedListNode<T>* nxt = curr->next;
      delete curr;
      curr = nxt;
    }
  }

  LinkedList<T>(const LinkedList<T>& rhs) : head(nullptr), m_size(rhs.m_size) {
    if(! rhs.empty()) {
      head = new LinkedListNode<T>(rhs.head->data, nullptr);
      LinkedListNode<T>* r_curr = (rhs.head)->next;
      LinkedListNode<T>* l_curr = head;
      while(r_curr != nullptr) {
        l_curr->setNext(new LinkedListNode<T>(r_curr->data, nullptr));
        l_curr = l_curr->next;
        r_curr = r_curr->next;
      }
    }
  }

  LinkedList<T>& operator=(const LinkedList<T>& rhs) { 
    if( this == &rhs ) { return *this; }
    
    LinkedListNode<T>* curr = head;
    while(curr != nullptr) {
      LinkedListNode<T>* nxt = curr->next;
      delete curr;
      curr = nxt;
    }

    head = nullptr;
    m_size = rhs.m_size;

    if(! rhs.empty()) {
      head = new LinkedListNode<T>(rhs.head->data, nullptr);
      LinkedListNode<T>* r_curr = (rhs.head)->next;
      LinkedListNode<T>* l_curr = head;
      while(r_curr != nullptr) {
        l_curr->setNext(new LinkedListNode<T>(r_curr->data, nullptr));
        l_curr = l_curr->next;
        r_curr = r_curr->next;
      }
    }

    return *this;
  }

  // move copy constructor
  LinkedList<T>(LinkedList<T>&& rhs) noexcept : head(rhs.head), m_size(rhs.m_size) {
    rhs.head = nullptr;
    rhs.m_size = 0;
  }

  LinkedList<T>& operator=(LinkedList<T>&& rhs) noexcept {
    if ( this == &rhs ) { return *this; }
    head = rhs.head;
    m_size = rhs.m_size;
    rhs.head = nullptr;
    rhs.m_size = 0;
    return *this;
  }
  
  void push_front(const T& val) {
    LinkedListNode<T>* curr = new LinkedListNode(val, head);
    head = curr;
    ++m_size;
  }

  void pop_front() {
    if(head == nullptr) return;
    LinkedListNode<T>* curr = head->next;
    delete head;
    head = curr;
    --m_size;
  }

  size_t size() const noexcept { return m_size;}

  bool empty() const noexcept { return m_size == 0; }

  const T& front() const {
    if(empty()) {
      std::cerr << "Tried to use `front` on empty list! \n";
      exit(1);
    }
    return head->data; 
  }

  T& front() {
    if(empty()) {
      std::cerr << "Tried to use `front` on empty list! \n";
      exit(1);
    }
    return head->data;
  }

  const T& back() const {
    if(empty()) {
      std::cerr << "Tried to use `back()` on empty list! \n";
      exit(1);
    }
    LinkedListNode<T>* curr = head;
    while(curr->next != nullptr) {
      curr = curr->next;
    }
    return curr->data;
  }
  T& back() {
    if(empty()) {
      std::cerr << "Tried to use `back()` on empty list! \n";
      exit(1);
    }
    LinkedListNode<T>* curr = head;
    while(curr->data != nullptr) {
      curr = curr->next;
    }
    return curr->data;
  }
  
};
template <typename T>
bool operator==(const typename LinkedList<T>::Iterator& lhs, const typename LinkedList<T>::Iterator& rhs) {
  return lhs.m_ptr == rhs.m_ptr;
}

template <typename T>
bool operator!=(const typename LinkedList<T>::Iterator& lhs, const typename LinkedList<T>::Iterator& rhs) {
  return !(lhs == rhs);
}
template <typename T>
bool operator==(const typename LinkedList<T>::Const_Iterator& lhs, const typename LinkedList<T>::Const_Iterator& rhs) {
  return lhs.m_ptr == rhs.m_ptr;
}

template <typename T>
bool operator!=(const typename LinkedList<T>::Const_Iterator& lhs, const typename LinkedList<T>::Const_Iterator& rhs) {
  return !(lhs == rhs);
}
