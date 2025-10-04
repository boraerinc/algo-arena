#include <iostream>
#include <functional>
#include <stdexcept>

template <typename T>
struct TreeNode {
  T m_Data;
  TreeNode* m_Left;
  TreeNode* m_Right;

  // Constructor
  TreeNode(const T& data, TreeNode* left, TreeNode* right) : m_Data(data), m_Left(left), m_Right(right) {} 
  
  // R-value Constructor
  TreeNode(T&& data, TreeNode* left, TreeNode* right) : m_Data(std::move(data)), m_Left(left), m_Right(right) {} 

  // Utils
  bool isLeafNode() const noexcept {
    return (m_Left == nullptr && m_Right == nullptr);
  }
};

template <typename T>
class Tree {
  TreeNode<T>* m_Root;

  // Constructor given root node
  Tree(TreeNode<T>* root) : m_Root(root) {}

  //================================================
  // Traversals
  //================================================
  void inorderTraversal() const {
    std::function<void(TreeNode<T>*)> traverse;
    traverse = [&traverse](TreeNode<T>* root) -> void {
      if(root->m_Left != nullptr) {
        traverse(root->m_Left);
      }
      std::cout << root->m_Data << "\n";
      if(root->m_Right != nullptr) {
        traverse(root->m_Right);
      }
    };
    if (m_Root == nullptr) {
      std::cout << "Empty tree! \n";
      return;
    }
    traverse(m_Root);
  }

  void preorderTraversal() const {
    std::function<void(TreeNode<T>*)> traverse;
    traverse = [&traverse](TreeNode<T>* root) -> void {
      std::cout << root->m_Data << "\n";
      if(root->m_Left != nullptr) {
        traverse(root->m_Left);
      }
      if(root->m_Right != nullptr) {
        traverse(root->m_Right);
      }
    };
    if (m_Root == nullptr) {
      std::cout << "Empty tree! \n";
      return;
    }
    traverse(m_Root);
  }
  void postorderTraversal() const {
    std::function<void(TreeNode<T>*)> traverse;
    traverse = [&traverse](TreeNode<T>* root) -> void {
      if(root->m_Right != nullptr) {
        traverse(root->m_Right);
      }
      if(root->m_Left != nullptr) {
        traverse(root->m_Left);
      }
      std::cout << root->m_Data << "\n";
    };
    if (m_Root == nullptr) {
      std::cout << "Empty tree! \n";
      return;
    }
    traverse(m_Root);
  }

  bool empty() const noexcept {
    return m_Root == nullptr;
  }

  void insert(const T& val) {
    if(empty()) {
      m_Root = new TreeNode<T>(val);
    } else {
      TreeNode<T>* curr = m_Root;
      while(!curr->isLeafNode()){ 
        if(val > curr->m_Data) {
          curr = curr->m_Right;
        } else if(val < curr->m_Data) {
          curr = curr->m_Left;
        } else {
          throw std::invalid_argument("Attempted to insert a value that already exists!");
        }
      }
      if(val > curr->m_Data) {
        curr->m_Right = new TreeNode<T>(val);
      } else if(val < curr->m_Data) {
        curr->m_Left = new TreeNode<T>(val);
      } else {
        throw std::invalid_argument("Attempted to insert a value that already exists!");
      }
    }
  }
  
  void insert(T&& val) {
    if(empty()) {
      m_Root = new TreeNode<T>(val);
    } else {
      TreeNode<T>* curr = m_Root;
      while(!curr->isLeafNode()){ 
        if(val > curr->m_Data) {
          curr = curr->m_Right;
        } else if(val < curr->m_Data) {
          curr = curr->m_Left;
        } else {
          throw std::invalid_argument("Attempted to insert a value that already exists!");
        }
      }
      if(val > curr->m_Data) {
        curr->m_Right = new TreeNode<T>(val);
      } else if(val < curr->m_Data) {
        curr->m_Left = new TreeNode<T>(val);
      } else {
        throw std::invalid_argument("Attempted to insert a value that already exists!");
      }
    }
  }
};


