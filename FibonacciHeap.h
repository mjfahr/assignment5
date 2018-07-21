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

  FibonacciHeap<T>* Merge(FibonacciHeap<T>* heap1, FibonacciHeap<T>* heap2);

  bool isEmpty() { return smallest == nullptr; }

private:
  int getRank(FibonacciNode<T>* node); // Number of children of a node (just immediate children
  void setSmallest();
  void addNode(FibonacciNode<T>* newNode);

  T MIN; // Smallest possible value for a node in the heap
  FibonacciNode<T>* smallest; // Equivalent to the 'head' node of a linked list. The root of this heap will be the smallest value in the fibonacci heap.
  int numNodes;

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
FibonacciHeap<T>::~FibonacciHeap()
{

}

//Insert: Public: Allows for the easy ( O(1) ) insertion of a value by creating a new heap.
template <class T>
void FibonacciHeap<T>::Insert(const T _value)
{
  FibonacciNode<T>* newNode = new FibonacciNode<T>(_value);
  // Insert the new node into the root list of the heap
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

    ptr->parent = nullptr;

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
  numRoots++;
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
      FibonacciNode<T>* advance = smallest->child;
      do
      {
        advance = ptr->right; // store the next child to be processed, as ptr->right will change in addNode(ptr).
        addNode(ptr);
        ptr = advance;
      } while(ptr != smallest->child);
    }

    // Remove smallest from the heap and reconnect doubly linked list
    if (smallest == smallest->right) // smallest is not the only node
    {
      smallest->left->right = smallest->right;
      smallest->right->left = smallest->left;

      // delete smallest
      FibonacciNode<T>* toDel = smallest;
      smallest = smallest->right; // set new smallest to be the right sibling of the current smallest (arbitrary choice)
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

//decreaseKey: public: reduces the value of a node by the specified amount, preserves heap ordering
template <class T>
void FibonacciHeap<T>::decreaseKey(FibonacciNode<T>* node, T decreaseAmt)
{
  node->value -= decreaseAmt;

  // TODO: restore heap ordering, if violated
}

template <class T>
void FibonacciHeap<T>::Delete(FibonacciNode<T>* node)
{
  // decrease key of node to MIN
  // deleteMin()
}

//Merge: public: combines two fibonacci heaps into one by splicing together their top-level nodes. heap1 and heap2 are not deleted, but should not be used after calling this function.
// NOTE: Alternatively, we could create a copy constructor and create an entirely new heap containing the same node values.
// This would reduce the likelihood of bugs occuring if the original heaps are reused, but it would be slower and less memory-efficient.
template <class T>
FibonacciHeap<T>* FibonacciHeap<T>::Merge(FibonacciHeap<T>* heap1, FibonacciHeap<T>* heap2)
{
  // Link the two heaps
  heap1->smallest->right->left = heap2->smallest->left;
  heap2->smallest->left->right = heap1->smallest->right;

  heap1->smallest->right = heap2->smallest;
  heap2->smallest->left = heap1->smallest;

  // Set the smallest node
  heap1->smallest = (heap1->smallest <= heap2->smallest ? heap1->smallest : heap2->smallest);

  return heap1;
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

#endif
