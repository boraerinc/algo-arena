#include <vector>

// should a singly linked list even have a "head" member?
// or should it just be the node itself?
// If it has a head, then should that head act as padding,
// holding no data but just pointing to the first element?
// Should Nodes have move semantics?
// How do you handle something like `T data` in a move oeprator?
// You can't set values to nullptr, nor can you call a destructor on them.

template <typename T>
class LinkedList {

  class Node {
    T data;
    Node* next;

  public:
    Node(): next(nullptr) {}

    Node(const T& val, Node* ptr = nullptr): data(val), next(ptr) {}

    Node(const Node& rhs) : data(rhs.data), next(rhs.next) {}

    Node& operator=(const Node& rhs) {
      if(this == &rhs) return *this;

      data = rhs.data;
      next = rhs.next;

      return *this;
    }

    ~Node() {}

    Node(const Node&& rhs) noexcept : data(rhs.data), next(rhs.next) {
      rhs.next = nullptr;
    }

    Node& operator=(const Node&& rhs) noexcept {
      if(this == &rhs) return *this;

      data = rhs.data;
      next = rhs.next;

      rhs.next = nullptr;

      return *this;
    }

    void setNext(Node* ptr) noexcept {
      next = ptr;
    }

    void setVal(const T& val) noexcept {
      data = val;
    }

    Node* getNext(Node* ptr) noexcept {
      return ptr;
    }

    T getVal(const T& val) noexcept {
      return val;
    }
  };

  Node* head;

public:
  
  LinkedList() : head(new Node()) { }


};



