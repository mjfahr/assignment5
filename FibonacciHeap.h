#ifndef FIBONACCI_HEAP_H
#define FIBONACCI_HEAP_H

#include <limits>
#include "Heap.h"

using namespace std;

template <class T>
class FibonacciHeap
{
public:
  FibonacciHeap();
  FibonacciHeap(Heap<T>* initHeap);
  ~FibonacciHeap();

  void Insert(const T _value);
  void deleteMin();
  void decreaseKey(HeapNode<T>* node, T val);

  bool isEmpty() { return smallest == nullptr; }

  T getMin() { return smallest->root->value; }

private:
  T MIN; // Smallest possible value for a node in the heap 
  void addHeap(Heap<T>* newHeap);
  Heap<T>* smallest; // Equivalent to the 'head' node of a linked list. The root of this heap will be the smallest value in the fibonacci heap.

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
FibonacciHeap<T>::FibonacciHeap(Heap<T>* initHeap)
{
  smallest = initHeap;
  smallest->right = initHeap;
  smallest->left = initHeap;
  //Set the minimum possible value for any node (used to simplify code for deleting a node) NOTE: only works for numeric types
  if (numeric_limits<T>::is_specialized)
     MIN = numeric_limits<T>::lowest();
}

template <class T>
FibonacciHeap<T>::~FibonacciHeap()
{

}

template <class T>
void FibonacciHeap<T>::Insert(const T _value)
{
  Heap<T>* newHeap = new Heap<T>(_value);
  addHeap(newHeap);
}

template <class T>
void FibonacciHeap<T>::addHeap(Heap<T>* newHeap)
{
  if (!isEmpty())
  {
    // Insert new heap into list, to the right of smallest (arbitrary choice)
    newHeap->right = smallest->right;
    newHeap->left = smallest;

    newHeap->right->left = newHeap;
    smallest->right = newHeap;

    // Move smallest pointer if necessary
    if (smallest->root->value > newHeap->root->value)
      smallest = newHeap;
  }
  else // Fibonacci heap is empty, first value is the smallest.
  {
    smallest = newHeap;
    // Create circular linking
    smallest->right = smallest;
    smallest->left = smallest;
  }
}

template <class T>
void FibonacciHeap<T>::deleteMin()
{
  // Create new heaps with each of the to-be-deleted node's children as the roots
  for (HeapNode<T>* newRoot : smallest->children)
  {
    Heap<T>* newHeap = new Heap<T>(newRoot);
    addHeap(newHeap);
  }
  // remove the min (smallest->root) NOTE: DO NOT remove smallest itself, as this will remove all lower nodes as well, which should become new heaps.
  delete smallest->root;
}

#endif
