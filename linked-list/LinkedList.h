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
  //
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
    return *(head);
  }

  T& front() {
    if(empty()) {
      std::cerr << "Tried to use `front` on empty list! \n";
      exit(1);
    }
    return *(head);
  }

  const T& back() const {
    if(empty()) {
      std::cerr << "Tried to use `back()` on empty list! \n";
      exit(1);
    }
    LinkedListNode<T>* curr = head;
    while(curr != nullptr) {
      curr = curr->next;
    }
    return *curr;
  }
  T& back() {
    if(empty()) {
      std::cerr << "Tried to use `back()` on empty list! \n";
      exit(1);
    }
    LinkedListNode<T>* curr = head;
    while(curr != nullptr) {
      curr = curr->next;
    }
    return *curr;
  }
  
};



