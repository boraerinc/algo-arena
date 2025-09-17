#include <cstddef>



template <typename T>
struct DLLNode {
  T m_Data;
  DLLNode* m_Prev;
  DLLNode* m_Next;

  DLLNode(const T& data, T* prev = nullptr, T* next = nullptr) : m_Data(data),
    m_Prev(prev), m_Next(next) {}
};

template<typename T>
class DoublyLinkedList {

  class Iterator {};

  class Const_Iterator {};
  
  DLLNode<T>* m_Head;
  DLLNode<T>* m_Tail;
  size_t m_Size;

public:
  DoublyLinkedList(DLLNode<T>* head) : m_Head(head), m_Tail(nullptr), m_Size(0) {
    if(m_Head != nullptr) {
      DLLNode<T>* curr = m_Head;
      while (curr->m_Next != nullptr) {
        ++m_Size;
        curr = curr->m_Next;
      }
      m_Tail = curr;
    }
  }
};
