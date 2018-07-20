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
  ~FibonacciHeap();

  T peekMin() { return smallest->value; }
  void Insert(const T _value);
  void extractMin();
  void decreaseKey(FibonacciNode<T>* node, T decreaseAmt);
  void Delete(FibonacciNode<T>* node);

  bool isEmpty() { return smallest == nullptr; }
  FibonacciHeap<T>* Merge(FibonacciHeap<T>* heap1, FibonacciHeap<T>* heap2);

private:
  int getRank(FibonacciNode<T>* node); // Number of children of a node (just immediate children
  void setSmallest();
  void addNode(FibonacciNode<T>* newNode);

  T MIN; // Smallest possible value for a node in the heap
  FibonacciNode<T>* smallest; // Equivalent to the 'head' node of a linked list. The root of this heap will be the smallest value in the fibonacci heap.

};

template <class T>
FibonacciHeap<T>::FibonacciHeap()
{
  smallest = nullptr;
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
  //Set the minimum possible value for any node (used to simplify code for deleting a node) NOTE: only works for numeric types
  if (numeric_limits<T>::is_specialized)
     MIN = numeric_limits<T>::lowest();
}

template <class T>
FibonacciHeap<T>::~FibonacciHeap()
{

}

//Insert: Public: Allows for the easy ( O(1) ) insertion of a value by creating a new heap.
template <class T>
void FibonacciHeap<T>::Insert(const T _value)
{
  FibonacciNode<T>* newNode = new FibonacciNode<T>(_value);
  // Insert the new node into the top level of the heap
  addNode(newNode);
}

//addHeap: Private: Adds a new heap to the circular, doubly-linked list of heaps.
template <class T>
void FibonaccHeap<T>::addNode(Heap<T>* newNode)
{
  if (!isEmpty())
  {
    // Insert new heap into list, to the right of smallest (arbitrary choice)
    newNode->right = smallest->right;
    newNode->left = smallest;

    newNode->right->left = newNode;
    smallest->right = newNode;

    // Move smallest pointer if necessary
    if (smallest->root->value > newHeap->root->value)
      smallest = newNode;
  }
  else // Fibonacci heap is empty, first value is the smallest.
  {
    smallest = newNode;
    // Create circular linking
    smallest->right = smallest;
    smallest->left = smallest;
  }
}

//deleteMin: Public: Removes the minimum value of the heap, a.k.a the root of 'smallest'. This removes ONLY the root, not the entire heap.
template <class T>
void FibonacciHeap<T>::extractMin()
{
  // Add smallest's children to the top level of the heap
  // Remove smallest from the heap
  // Consolidate nodes on the top level so that no two nodes have the same rank (# of children)
  // find the new smallest node
}

//removeHeap: private: Removes a node from the circular, doubly-linked list of nodes
template <class T>
void FibonacciHeap<T>::removeNode(FibonacciNode<T>* node)
{
  // Reconnect doubly linked list
  node->left->right = node->right;
  node->right->left = node->left;

  // If the node's parent points to the node as its child, and the node has a sibling
  if (node->parent != nullptr && node->parent->child == node && node->right != node)
      node->parent->child = node->right; // make the sibling the new child of the to-be-removed node's parent

}


//setSmallest: private: used to find the new min after a deleteMin call
template <class T>
void FibonacciHeap<T>::setSmallest()
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

template <class T>
void FibonacciHeap<T>::decreaseKey(FibonacciNode<T>* node, T decreaseAmt)
{
  node->value -= decreaseAmt;

  //restore heap ordering, if violated
}

template <class T>
void FibonacciHeap<T>::Delete(FibonacciNode<T>* node)
{
  // decrease key of node to MIN
  // deleteMin()
}

template <class T>
FibonacciHeap<T>* FibonacciHeap<T>::Merge(FibonacciHeap<T>* heap1, FibonacciHeap<T>* heap2)
{

}

template <class T>
int FibonacciHeap<T>::getRank(FibonacciNode<T>* node)
{
  // return the number of children of the node
}

#endif
