#include <cassert>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <utility>

template <typename T>
struct LinkedListNode {
  T data;
  LinkedListNode* next;

  LinkedListNode(const T& val, LinkedListNode* ptr = nullptr): data(val), next(ptr) {}
};

template <typename T>
class LinkedList {

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

    T* operator->() const {
      return m_ptr;
    }

    friend bool operator==(const Iterator& lhs, const Iterator& rhs);
  };


  class Const_Iterator {
    public:
    const LinkedListNode<T>* m_ptr;

    Const_Iterator(LinkedListNode<T>* aPtr) : m_ptr(aPtr) {}

    // Convert Iterator to Const Iterator
    Const_Iterator(const Iterator& rhs) : m_ptr(rhs.aPtr) {}

    Const_Iterator& operator++() {
      m_ptr = m_ptr->next;
      return *this;
    }

    Const_Iterator operator++(int) {
      Const_Iterator res(*this);
      m_ptr = m_ptr->next;
      return res;
    }
    
    const T& operator*() const {
      return m_ptr->data;
    }

    const T* operator->() const {
      return m_ptr;
    }

    friend bool operator==(const Const_Iterator& lhs, const Const_Iterator& rhs);
  };
      
  LinkedListNode<T>* head;

  size_t m_size;

  void cleanup() noexcept {
    LinkedListNode<T>* curr = head;
    while(curr != nullptr) {
      LinkedListNode<T>* nxt = curr->next;
      delete curr;
      curr = nxt;
    }
  }

public:
  
  LinkedList<T>() : head(nullptr), m_size(0) { }

  ~LinkedList<T>() { cleanup(); }

  LinkedList<T>(const LinkedList<T>& rhs) : head(nullptr), m_size(rhs.m_size) {
    if(! rhs.empty()) {
      head = new LinkedListNode<T>(rhs.head->data, nullptr);
      LinkedListNode<T>* r_curr = (rhs.head)->next;
      LinkedListNode<T>* l_curr = head;
      while(r_curr != nullptr) {
        l_curr.next = new LinkedListNode<T>(r_curr->data, nullptr);
        l_curr = l_curr->next;
        r_curr = r_curr->next;
      }
    }
  }

  LinkedList<T>& operator=(LinkedList<T> rhs) { 
    LinkedList<T> tmp(rhs);
    std::swap(head, tmp.head);
    std::swap(m_size, tmp.m_size);
    return *this;
  }

  LinkedList<T>(LinkedList<T>&& rhs) noexcept : head(rhs.head), m_size(rhs.m_size) {
    rhs.head = nullptr;
    rhs.m_size = 0;
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

  // const and non-const begin
  Iterator begin() {
    return Iterator(head);
  }

  Const_Iterator begin() const {
    return Const_Iterator(head);
  }
  
  // const and non-const begin
  Const_Iterator end() const {
    return Const_Iterator(nullptr);
  }

  Iterator end() {
    return Iterator(nullptr);
  }

  // cbegin and cend for C++11 and further
  Const_Iterator cbegin() const {
    return Const_Iterator(head);
  }

  Const_Iterator cend() const {
    return Const_Iterator(nullptr);
  }
  
  const T& front() const {
    if(empty()) {
      throw std::out_of_range("Tried to use `front()` on empty list! \n");
    }
    return head->data; 
  }

  T& front() {
    if(empty()) {
      throw std::out_of_range("Tried to use `front()` on empty list! \n");
    }
    return head->data;
  }

  const T& back() const {
    if(empty()) {
      throw std::out_of_range("Tried to use `back()` on empty list! \n");
    }
    LinkedListNode<T>* curr = head;
    while(curr->next != nullptr) {
      curr = curr->next;
    }
    return curr->data;
  }

  T& back() {
    if(empty()) {
      throw std::out_of_range("Tried to use `back()` on empty list! \n");
    }
    LinkedListNode<T>* curr = head;
    while(curr->next != nullptr) {
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
