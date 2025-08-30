#include <vector>

// should a singly linked list even have a "head" member?
// or should it just be the node itself?
// If it has a head, then should that head act as padding,
// holding no data but just pointing to the first element?
// Should LinkedListNodes have move semantics?
// How do you handle something like `T data` in a move oeprator?
// You can't set values to nullptr, nor can you call a destructor on them.
template <typename T>
class LinkedListNode {
  T data;
  LinkedListNode* next;

public:
  LinkedListNode(): next(nullptr) {}

  LinkedListNode(const T& val, LinkedListNode* ptr = nullptr): data(val), next(ptr) {}

  LinkedListNode(const LinkedListNode& rhs) : data(rhs.data), next(rhs.next) {}

  LinkedListNode& operator=(const LinkedListNode& rhs) {
    if(this == &rhs) return *this;

    data = rhs.data;
    next = rhs.next;

    return *this;
  }

  ~LinkedListNode() {}

  LinkedListNode(const LinkedListNode&& rhs) noexcept : data(rhs.data), next(rhs.next) {
    rhs.next = nullptr;
  }

  LinkedListNode& operator=(const LinkedListNode&& rhs) noexcept {
    if(this == &rhs) return *this;

    data = rhs.data;
    next = rhs.next;

    rhs.next = nullptr;

    return *this;
  }

  void setNext(LinkedListNode* ptr) noexcept {
    next = ptr;
  }

  void setVal(const T& val) noexcept {
    data = val;
  }

  LinkedListNode* getNext(LinkedListNode* ptr) noexcept {
    return ptr;
  }

  T getVal(const T& val) noexcept {
    return val;
  }
};

template <typename T>
class LinkedList {

  LinkedListNode<T>* head;
  size_t m_size;

public:
  
  LinkedList<T>() : head(new LinkedListNode<T>()), m_size(0) { }
  
  void push_front(const T& val) {
    LinkedListNode<T>* curr = new LinkedListNode(val, head);
    head = curr;
    ++m_size;
  }

  void pop_front() {
    if(head->next == nullptr) return;
    LinkedListNode<T>* curr = head->next->next;
    delete head->next;
    head->next = curr;
    --m_size;
  }

  size_t size() const noexcept { return m_size;}

  bool empty() const noexcept { return m_size == 0; }

  const T& front() const {
    if(!empty()) {
      return *(head->next);
    }
  }

};



