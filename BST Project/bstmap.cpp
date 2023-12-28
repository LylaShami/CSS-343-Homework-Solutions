// Yusuf Pisan pisan@uw.edu
// 17 Jan 2021

// BST class
// Creates a BST to store values
// Uses Node which holds the data

#include "bstmap.h"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <vector>

using namespace std;

// Copy constructor for the BSTMap class, used to create a deep copy of a binary
// search tree. It takes an existing BSTMap 'bst' and creates a new instance
// with the same structure and content. If 'bst' is not empty, it allocates
// memory for a new root node and recursively copies the left and right
// subtrees.
BSTMap::BSTMap(const BSTMap &bst) {

  if (bst.root != nullptr) {
    root = new Node{bst.root->data, nullptr, nullptr};
    if (bst.root->left != nullptr) {
      root->left = copySubtree(bst.root->left);
    }
    // Recursively copy the right subtree of 'bst' if it exists.
    if (bst.root->right != nullptr) {
      root->right = copySubtree(bst.root->right);
    }
  }
}

BSTMap::Node *BSTMap::copySubtree(Node *root) {
  if (root == nullptr) {
    // If the input 'root' is null (empty subtree), return null.
    return root;
  }
  // Create a new node with the same data as 'root'.
  Node *newNode = new Node{root->data, nullptr, nullptr};
  // Recursively copy the left and right subtrees of 'root' and set them in the
  // new node.
  newNode->left = copySubtree(root->left);
  newNode->right = copySubtree(root->right);
  // Return the root of the copied subtree.
  return newNode;
}

BSTMap::Node *BSTMap::createNode(const value_type &item) {
  auto *newNode = new Node();
  newNode->data = item;
  newNode->left = nullptr;
  newNode->right = nullptr;
  return newNode;
}

BSTMap::BSTMap(const vector<value_type> &v) {
  // Create a copy of the input vector to avoid modifying the original vector.
  vector<value_type> newVector(v);

  // Sort the new vector of key-value pairs based on the values.
  sort(newVector.begin(), newVector.end(),
       [](const value_type &a, const value_type &b) {
         return a.second < b.second;
       });

  if (newVector.empty()) {
    // If the sorted vector is empty, set the root of the BST to nullptr (an
    // empty tree).
    root = nullptr;
  } else {
    // If the sorted vector is not empty, construct the tree by recursively
    // building it using the sorted vector and set the root to the result of the
    // buildTree function.
    root = buildTree(newVector, 0, static_cast<int>(newVector.size() - 1));
  }
}

BSTMap::Node *BSTMap::buildTree(const vector<BSTMap::value_type> &v,
                                int firstIndex, int lastIndex) {
  // Base case: If 'firstIndex' exceeds 'lastIndex,' return nullptr to represent
  // an empty subtree.
  if (firstIndex > lastIndex) {
    return nullptr;
  }
  // Calculate the index of the middle element in the current range.
  int middleElem = firstIndex + (lastIndex - firstIndex) / 2;
  // Create a new node for the root using the middle element in the current
  // range.
  Node *root = createNode(v[middleElem]);
  // Recursively construct the left subtree from the elements to the left of the
  // middle element.
  root->left = buildTree(v, firstIndex, middleElem - 1);
  // Recursively construct the right subtree from the elements to the right of
  // the middle element.
  root->right = buildTree(v, middleElem + 1, lastIndex);
  // Return the root node of the constructed binary search tree.
  return root;
}

BSTMap::~BSTMap() { clear(); }

void BSTMap::clear() {
  clearTree(root);
  root = nullptr;
}

void BSTMap::clearTree(Node *node) {
  // Base case: If 'node' is nullptr, there is nothing to clear, so return
  // immediately.
  if (node == nullptr) {
    return;
  }
  // Recursively clear the left subtree, freeing its memory.
  clearTree(node->left);
  // Recursively clear the right subtree, freeing its memory.
  clearTree(node->right);
  // Delete the current 'node' to release the memory it occupies.

  delete node;
}
BSTMap::mapped_type &BSTMap::insert(const value_type &item) {
  // If the tree is empty, create a new root node with 'item' and return its
  // associated value.
  if (root == nullptr) {
    root = createNode(item);
    return root->data.second;
  }

  Node *current = root;
  Node *parent = nullptr;

  while (current != nullptr) {
    parent = current;
    if (item.first < current->data.first) {
      current = current->left;
    } else if (item.first > current->data.first) {
      current = current->right;
    } else {
      // If the key already exists, update the value and return it.
      current->data.second = item.second;
      return current->data.second;
    }
  }

  // Create a new node with 'item'.
  Node *newNode = createNode(item);

  // Determine whether to place the new node as the left or right child of
  // 'parent' based on the key.
  if (item.first < parent->data.first) {
    parent->left = newNode;
  } else {
    parent->right = newNode;
  }

  // Return the value associated with the newly inserted key.
  return newNode->data.second;
}

bool BSTMap::empty() { return true; }

int BSTMap::size() const { return countNodes(root); }

int BSTMap::countNodes(Node *node) const {
  // Base case: If 'node' is nullptr, return 0, as there are no nodes in an
  // empty subtree.
  if (node == nullptr) {
    return 0;
  }

  // Count the current node and recursively count nodes in the left and right
  // subtrees.
  return 1 + countNodes(node->left) + countNodes(node->right);
}

bool BSTMap::contains(const key_type &key) const {
  Node *current = root;

  while (current != nullptr) {
    if (key == current->data.first) {
      // The key is found in the current node, return true.
      return true;
    }
    if (key < current->data.first) {
      // If 'key' is less than the current node's key, move to the left subtree.
      current = current->left;
    } else {
      // If 'key' is greater than the current node's key, move to the right
      // subtree.
      current = current->right;
    }
  }

  // If the loop completes without finding 'key,' return false as it's not in
  // the tree.
  return false;
}

vector<BSTMap::value_type> BSTMap::getAll(const key_type &k) const {
  vector<value_type> result;
  retrieveMatchingValues(result, root, k);
  return result;
}

void BSTMap::retrieveMatchingValues(vector<value_type> &v, Node *root,
                                    const key_type &k) const {
  // Base case: If 'root' is nullptr, there are no nodes to process, so return.
  if (root == nullptr) {
    return;
  }

  // Extract the prefix of the current node's key to compare with 'k'.
  string currentPrefix = root->data.first.substr(0, k.length());

  if (currentPrefix < k) {
    // If the current prefix is less than 'k', search in the right subtree.
    retrieveMatchingValues(v, root->right, k);
  } else if (currentPrefix > k) {
    // If the current prefix is greater than 'k', search in the left subtree.
    retrieveMatchingValues(v, root->left, k);
  } else {
    // If the prefixes match, add the current node's data to the result vector.
    v.push_back(root->data);

    // Continue searching in both the right and left subtrees for more matches.
    retrieveMatchingValues(v, root->right, k);
    retrieveMatchingValues(v, root->left, k);
  }
}

int BSTMap::height() const { return getHeight(root); }

int BSTMap::getHeight(const Node *n) const {
  // Base case: If 'n' is nullptr, the subtree has no height, so return 0.
  if (n == nullptr) {
    return 0;
  }

  // Recursively calculate the height of the left and right subtrees.
  int leftHeight = getHeight(n->left);
  int rightHeight = getHeight(n->right);

  // Return 1 plus the maximum height between the left and right subtrees.
  return 1 + max(leftHeight, rightHeight);
}

// If k matches the key returns a reference to its value
// If k does not match any key, inserts a new element
// with that key and returns a reference to its mapped value.
BSTMap::mapped_type &BSTMap::operator[](const key_type &k) {

  // Check if the binary search tree contains the key 'k'.
  if (this->contains(k)) {
    // If 'k' is found, return the associated value directly from the root node.
    return root->data.second;
  }

  Node *current = root;
  Node *parent = nullptr;

  // Traverse the binary search tree to find the key 'k' while keeping track of
  // the parent node.
  while (current != nullptr) {
    if (k == current->data.first) {
      // If 'k' is found in the current node, return the associated value.
      return current->data.second;
    }
    if (k < current->data.first) {
      // If 'k' is less than the current node's key, move to the left subtree.
      parent = current;
      current = current->left;
    } else {
      // If 'k' is greater than the current node's key, move to the right
      // subtree.
      parent = current;
      current = current->right;
    }
  }

  // If 'k' is not found, create a new node for 'k' with a default value.
  Node *newNode = new Node;
  newNode->data.first = k;
  newNode->data.second = mapped_type{};
  newNode->left = nullptr;
  newNode->right = nullptr;

  if (parent == nullptr) {
    // If the tree is empty, set the new node as the root.
    root = newNode;
  } else if (k < parent->data.first) {
    // Set the new node as the left child of the parent if 'k' is less than the
    // parent's key.
    parent->left = newNode;
  } else {
    // Set the new node as the right child of the parent if 'k' is greater than
    // the parent's key.
    parent->right = newNode;
  }

  // Return the default value associated with the newly inserted key 'k'.
  return newNode->data.second;
}

void BSTMap::postorder(void visit(const value_type &item)) const {
  postorderHelper(root, visit);
}
void BSTMap::postorderHelper(Node *n,
                             void visit(const value_type &item)) const {
  if (n == nullptr) {
    return;
  }
  // Recursively visit the left subtree in a post-order manner.
  postorderHelper(n->left, visit);
  // Recursively visit the right subtree in a post-order manner.
  postorderHelper(n->right, visit);
  // Visit the data of the current node using the provided 'visit' function.
  visit(n->data);
}

void BSTMap::inorder(void visit(const value_type &item)) const {
  inorderRecursive(root, visit);
}
void BSTMap::inorderRecursive(Node *node,
                              void visit(const value_type &item)) const {
  if (node == nullptr) {
    return;
  }
  // Recursively visit the left subtree in an in-order manner.
  inorderRecursive(node->left, visit);
  // Visit the data of the current node using the provided 'visit' function.
  visit(node->data);
  // Recursively visit the right subtree in an in-order manner.
  inorderRecursive(node->right, visit);
}

void BSTMap::preorder(void visit(const value_type &item)) const {
  preorderHelper(root, visit);
}
void BSTMap::preorderHelper(Node *n, void visit(const value_type &item)) const {
  if (n == nullptr) {
    return;
  }
  // Visit the data of the current node using the provided 'visit' function.
  visit(n->data);
  // Recursively visit the left subtree in a pre-order manner.
  preorderHelper(n->left, visit);
  // Recursively visit the right subtree in a pre-order manner.
  preorderHelper(n->right, visit);
}

void BSTMap::rebalance() {
  vector<value_type> v;
  // Perform an in-order traversal of the tree to collect nodes in sorted order.
  inorderForRebalance(root, v);
  // Clear the current BST to rebuild it as a balanced tree.
  clear();
  // Rebuild the BST with the sorted nodes to ensure a balanced structure.
  root = buildBalancedTree(v, 0, static_cast<int>(v.size() - 1));
}

void BSTMap::inorderForRebalance(Node *n, vector<value_type> &v) const {
  if (n == nullptr) {
    return;
  }
  // Recursively traverse the left subtree in in-order.
  inorderForRebalance(n->left, v);
  // Add the current node's data to the vector in sorted order.
  v.push_back(n->data);
  // Recursively traverse the right subtree in in-order.
  inorderForRebalance(n->right, v);
}
BSTMap::Node *BSTMap::buildBalancedTree(const vector<value_type> &v, int left,
                                        int right) {
  if (left > right) {
    return nullptr;
  }
  // Calculate the middle index between 'left' and 'right'.
  int mid = left + (right - left) / 2;
  Node *newNode = createNode(
      v[mid]); // Create a new node with data from the middle element.

  // Recursively build the left subtree with elements from 'left' to 'mid - 1'.
  newNode->left = buildBalancedTree(v, left, mid - 1);

  // Recursively build the right subtree with elements from 'mid + 1' to
  // 'right'.
  newNode->right = buildBalancedTree(v, mid + 1, right);

  return newNode; // Return the current node representing the root of the
                  // balanced subtree.
}

bool BSTMap::erase(const key_type &k) { return eraseNode(root, nullptr, k); }

bool BSTMap::eraseNode(Node *current, Node *parent, const key_type &k) {
  if (current == nullptr) {
    // Base case: If 'current' is nullptr, the key 'k' is not found in the
    // subtree, so return false.
    return false;
  }

  if (k < current->data.first) {
    // If 'k' is less than the current node's key, continue searching in the
    // left subtree.
    return eraseNode(current->left, current, k);
  }

  if (k > current->data.first) {
    // If 'k' is greater than the current node's key, continue searching in the
    // right subtree.
    return eraseNode(current->right, current, k);
  }

  // The key 'k' is found in the current node, and it needs to be removed.
  Node *child = nullptr;

  if (current->left == nullptr) {
    child = current->right;
  } else if (current->right == nullptr) {
    child = current->left;
  } else {
    // When the current node has both left and right children, replace it with
    // the successor node.
    Node *successor = findLeftmostNode(current->right);

    if (current == this->root) {
      this->root = successor;
    } else if (current == parent->left) {
      parent->left = successor;
    } else {
      parent->right = successor;
    }

    successor->left = current->left;
    child = current->right;
  }

  // Update the tree structure to remove the current node.
  if (current == this->root) {
    this->root = child;
  } else if (current == parent->left) {
    parent->left = child;
  } else {
    parent->right = child;
  }

  // Deallocate memory by deleting the current node.
  delete current;
  return true;
}

bool BSTMap::operator==(const BSTMap &other) const {
  return compareTrees(root, other.root);
}

bool BSTMap::compareTrees(Node *node1, Node *node2) const {
  // Recursively compare two binary search trees (BSTs) for structural and data
  // equality.

  if (node1 == nullptr && node2 == nullptr) {
    // If both nodes are nullptr, they are considered equal.
    return true;
  }

  if (node1 != nullptr && node2 != nullptr) {
    // If both nodes are not nullptr, compare their data.
    if (node1->data != node2->data) {
      // If data in corresponding nodes is not equal, the trees are not equal.
      return false;
    }

    // Recursively compare left and right subtrees of both trees.
    return compareTrees(node1->left, node2->left) &&
           compareTrees(node1->right, node2->right);
  }

  // If one node is nullptr and the other is not, the trees are not equal.
  return false;
}
bool BSTMap::operator!=(const BSTMap &other) const { return !(*this == other); }

BSTMap::Node *BSTMap::findLeftmostNode(Node *currentNode) {
  Node *leftmostNode = nullptr;
  Node *parent = nullptr;

  // Traverse the left subtree to find the leftmost node.
  while (currentNode != nullptr) {
    parent = leftmostNode;
    leftmostNode = currentNode;
    currentNode = currentNode->left;
  }

  // Ensure that the tree structure is maintained after finding the leftmost
  // node.
  if (leftmostNode != nullptr) {
    parent->left = leftmostNode->right;
    leftmostNode->right = nullptr;
  }

  // Return the leftmost node found.
  return leftmostNode;
}

size_t BSTMap::count(const string &k) const {
  // Start the count from 0.
  size_t count = 0;

  // Call the helper function to recursively count the occurrences of 'k' in the
  // tree.
  count = countHelper(root, k);

  return count;
}

size_t BSTMap::countHelper(Node *node, const string &k) const {
  if (node == nullptr) {
    return 0;
  }

  size_t count = 0;

  if (k == node->data.first) {
    // If the key 'k' matches the key of the current node, increment the count
    // by 1.
    count = 1;
  }
  // Recursively count occurrences of 'k' in the left and right subtrees.
  count += countHelper(node->left, k);
  count += countHelper(node->right, k);
  return count; // Return the total count of occurrences of 'k' in the tree.
}