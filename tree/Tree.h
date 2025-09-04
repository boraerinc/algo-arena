#include <iostream>
#include <functional>

template <typename T>
struct TreeNode {
  T m_Data;
  TreeNode* m_Left;
  TreeNode* m_Right;

  // Constructor
  TreeNode(const T& data, TreeNode* left, TreeNode* right) : m_Data(data), m_Left(left), m_Right(right) {} 
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

};


