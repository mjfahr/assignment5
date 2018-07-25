#ifndef FIBONACCI_HEAP_H
#define FIBONACCI_HEAP_H

#include <limits>
#include <iostream>
#include "FibonacciNode.h"

using namespace std;

template <class T>
class FibonacciHeap
{
public:
  FibonacciHeap();
  FibonacciHeap(FibonacciNode<T>* node);
  FibonacciHeap(const FibonacciHeap<T>& other); // TODO: Add copy constuctor
  ~FibonacciHeap();

  T peekMin() { return smallest->value; }
  void Insert(const T _value);
  void extractMin();
  bool decreaseKey(FibonacciNode<T>* node, T newKey);
  void Delete(FibonacciNode<T>* node);


  FibonacciHeap<T> Merge(FibonacciHeap<T>& other);
  FibonacciHeap<T> operator+(FibonacciHeap<T>& other) { return Merge(other); }
  //FibonacciHeap<T> operator=(const FibonacciHeap<T>& other); // TODO: add "=" operator (may be necessary to properly use the merge operation)

  bool isEmpty() { return smallest == nullptr; }
  void print();

private:
  int getRank(FibonacciNode<T>* node); // Number of children of a node (just immediate children
  void setSmallest();
  void addNode(FibonacciNode<T>* newNode);
  void printHelper(FibonacciNode<T>* root) const;
  void cut(FibonacciNode<T>* ndoe);
  void cascadingCut(FibonacciNode<T>* node);
  void destructHelper(FibonacciNode<T>* node);

  FibonacciNode<T>* smallest; // Equivalent to the 'head' node of a linked list. The root of this heap will be the smallest value in the fibonacci heap.
  int numNodes;
  T MIN; // Smallest possible value for a node in the heap

};

template <class T>
FibonacciHeap<T>::FibonacciHeap()
{
  smallest = nullptr;
  numNodes = 0;
  //Set the minimum possible value for any node (used to simplify code for deleting a node) NOTE: only works for numeric types
  if (numeric_limits<T>::is_specialized)
     MIN = numeric_limits<T>::lowest();
}

template <class T>
FibonacciHeap<T>::FibonacciHeap(FibonacciNode<T>* node)
{
  smallest = node;
  smallest->right = node;
  smallest->left = node;
  numNodes = 1;
  //Set the minimum possible value for any node (used to simplify code for deleting a node) NOTE: only works for numeric types
  if (numeric_limits<T>::is_specialized)
     MIN = numeric_limits<T>::lowest();
}

template <class T>
FibonacciHeap<T>::FibonacciHeap(const FibonacciHeap<T>& other)
{

}

template <class T>
FibonacciHeap<T>::~FibonacciHeap()
{
  destructHelper(smallest);
}

// destructHelper: private: recusive helper function for destructor
template <class T>
void FibonacciHeap<T>::destructHelper(FibonacciNode<T>* node)
{
  FibonacciNode<T>* current = node;
  FibonacciNode<T>* next = node;

  if (current != nullptr)
  {
    do
    {
      current = next;
      destructHelper(current->child);
      next = current->right;
      delete current;

    } while(next != node);
  }
}

//Insert: Public: Allows for the easy ( O(1) ) insertion of a value by adding a new heap to the root list.
template <class T>
void FibonacciHeap<T>::Insert(const T _value)
{
  FibonacciNode<T>* newNode = new FibonacciNode<T>(_value);
  // Insert the new node into the root list of the heap
  addNode(newNode);
}

//addHeap: Private: Adds a new heap to the root list.
template <class T>
void FibonacciHeap<T>::addNode(FibonacciNode<T>* newNode)
{
  if (!isEmpty())
  {
    // Insert new heap into list, to the right of smallest (arbitrary choice)
    newNode->right = smallest->right;
    newNode->left = smallest;

    newNode->right->left = newNode;
    smallest->right = newNode;

    newNode->parent = nullptr;

    // Move smallest pointer if necessary
    if (smallest->value > newNode->value)
      smallest = newNode;
  }
  else // Fibonacci heap is empty, first value is the smallest.
  {
    smallest = newNode;
    // Create circular linking
    smallest->right = smallest;
    smallest->left = smallest;
  }
  numNodes++;
}

//deleteMin: Public: Removes the minimum value of the heap, a.k.a the root of 'smallest'. This removes ONLY the root, not the entire heap.
template <class T>
void FibonacciHeap<T>::extractMin()
{
  if (!isEmpty())
  {
    // Add smallest's children to the top level of the heap
    if (smallest->child != nullptr)
    {
      FibonacciNode<T>* ptr = smallest->child;
      FibonacciNode<T>* next = smallest->child;
      do
      {
        next = ptr->right; // store the next child to be processed, as ptr->right will change in addNode(ptr).
        addNode(ptr);
        ptr = next;
      } while(ptr != smallest->child);
    }

    // Remove smallest from the heap and reconnect doubly linked list
    if (smallest != smallest->right) // smallest is not the only node
    {
      smallest->left->right = smallest->right;
      smallest->right->left = smallest->left;

      // delete smallest
      FibonacciNode<T>* toDel = smallest;
      smallest = smallest->right; // set new smallest to be the right sibling of the current smallest (arbitrary choice), will be changed later.
      delete toDel;



      // TODO: Consolidate nodes on the top level so that no two nodes have the same rank (# of children)


      // find the new smallest node
      setSmallest();
    }
    else
    {
      delete smallest;
      smallest = nullptr;
    }
    numNodes--;
  }
}


//setSmallest: private: used to find the new min after a deleteMin call
template <class T>
void FibonacciHeap<T>::setSmallest()
{

  if (!isEmpty())
  {
    FibonacciNode<T>* ptr = smallest->right;
    FibonacciNode<T>* init = smallest; // Used to keep track of where we started, since smallest will change.

    while (ptr != init)
    {
      if (ptr->value < smallest->value)
        smallest = ptr;

      ptr = ptr->right;
    }
  }
}

template <class T>
void FibonacciHeap<T>::cut(FibonacciNode<T>* node)
{
  // If the child has siblings
  if (node->right != node)
  {
    //reconnect the circular list of siblings
    node->left->right = node->right;
    node->right->left = node->left;


    // if the parent of node points to node as a child, change the child pointer
    if (node->parent->child == node)
      node->parent->child = node->right;
  }

  // decrease the degree/rank of the parent, since we removed a child
  node->parent->rank--;
  node->marked = false;

  addNode(node);

}

template <class T>
void FibonacciHeap<T>::cascadingCut(FibonacciNode<T>* node)
{
  if (node->parent != nullptr)
  {
    if (node->parent->marked == false)
      node->parent->marked = true;
    else
    {
      cut(node);
      cascadingCut(node->parent);
    }
  }
}

//decreaseKey: public: reduces the value of a node by the specified amount, preserves heap ordering
template <class T>
bool FibonacciHeap<T>::decreaseKey(FibonacciNode<T>* node, T newKey)
{
  // if the new value does not decrease the key of the node
  if (newKey > node->value)
    return false;
  else
  {
    node->value = newKey;

    // if the heap order is violated and the node is not a member of the root list, restore the heap order
    if (node->parent != nullptr && node->parent->value > node->value)
    {
      cut(node);
      cascadingCut(node->parent);
    }

    if (node->value < smallest->value)
      smallest = node;

    return true;
  }
}

template <class T>
void FibonacciHeap<T>::Delete(FibonacciNode<T>* node)
{
  // decrease key of node to MIN
  decreaseKey(node, MIN);
  // deleteMin()
}

//Merge: public: combines two fibonacci heaps into one by splicing together their top-level nodes. the two heaps are not deleted, but should not be used after calling this function.
// NOTE: Alternatively, we could create a copy constructor and create an entirely new heap containing the same node values.
// This would reduce the likelihood of bugs occuring if the original heaps are reused, but it would be slower and less memory-efficient.
template <class T>
FibonacciHeap<T> FibonacciHeap<T>::Merge(FibonacciHeap<T>& other)
{
  // Link the two heaps
  smallest->right->left = other.smallest->left;
  other.smallest->left->right = smallest->right;

  smallest->right = other.smallest;
  other.smallest->left = smallest;

  // Set the smallest node
  smallest = (smallest->value <= other.smallest->value ? smallest : other.smallest);

  return *this;
}


//getRank: private: return the number of children of a node.
template <class T>
int FibonacciHeap<T>::getRank(FibonacciNode<T>* node)
{
  int rank = 0;
  FibonacciNode<T>* init = node->child;

  if (init != nullptr)
  {
    FibonacciNode<T>* ptr = init->right;
    rank++;

    while (ptr != init)
    {
      rank++;
      ptr = ptr->right;
    }
  }

  return rank;
}

template <class T>
void FibonacciHeap<T>::print()
{
  FibonacciNode<T>* ptr1 = smallest;
  do
  {
    printHelper(ptr1);
    cout << endl;
    ptr1 = ptr1->right;

  } while(ptr1 != smallest);

}

template <class T>
void FibonacciHeap<T>::printHelper(FibonacciNode<T>* root) const
{
  cout << root->value << " ";

  if (root->child != nullptr)
  {
    FibonacciNode<T>* ptr2 = root->child;

    do
    {
      printHelper(ptr2);
      ptr2 = ptr2->right;
    } while(ptr2 != root->child);
  }
}


#endif
