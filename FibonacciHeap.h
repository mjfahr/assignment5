#ifndef FIBONACCI_HEAP_H
#define FIBONACCI_HEAP_H

#include <limits>
#include <iostream>
#include "Heap.h"
#include "HeapList.h"

using namespace std;

template <class T>
class FibonacciHeap
{
public:
  FibonacciHeap();
  FibonacciHeap(Heap<T>* initHeap);
  ~FibonacciHeap();

  T peekMin() { return smallest->root->value; }
  void Insert(const T _value);
  void deleteMin();
  void decreaseKey(HeapNode<T>* node, T amt);

  bool isEmpty() { return smallest == nullptr; }


private:
  T MIN; // Smallest possible value for a node in the heap
  int getRank(HeapNode<T>* node) { return node->children.size(); }
  void combineHeaps(HeapNode<T>* baseHeapRoot, Heap<T>* subHeap);
  void removeHeap(Heap<T>* heap);
  void setSmallest();

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

//Insert: Public: Allows for the easy ( O(1) ) insertion of a value by creating a new heap.
template <class T>
void FibonacciHeap<T>::Insert(const T _value)
{
  Heap<T>* newHeap = new Heap<T>(_value);
  addHeap(newHeap);
}

//deleteMin: Public: Removes the minimum value of the heap, a.k.a the root of 'smallest'. This removes ONLY the root, not the entire heap.
template <class T>
void FibonacciHeap<T>::deleteMin()
{
  // Create new heaps with each of the to-be-deleted node's children as the roots
  for (HeapNode<T>* newRoot : smallest->root->children)
  {
    Heap<T>* newHeap = new Heap<T>(newRoot);
    addHeap(newHeap);
  }
  // remove heap of which smallest is the root (the sub-heaps have already been added to the list)
  Heap<T>* toRemove = smallest;
  smallest = smallest->right; // Set smallest to an arbitrary node, it will be set appropriately later.
  cout << "removeHeap(1)\n";
  removeHeap(toRemove);
  cout << "end removeHeap(1)\n";
  cout << "setSmallest(1)\n";
  setSmallest(); // set smallest to the appropriate heap;
  cout << "end setSmallest(1)\n";


  // Consolidate any heaps of equal rank
  bool loopAgain = true;
  while (loopAgain)
  {
    loopAgain = false;
    Heap<T>* ptr = smallest;
    Heap<T>* runner = smallest->right;
    do
    {
      while (runner != smallest)
      {
        if (getRank(ptr->root) == getRank(runner->root))
        {
          // remove the heap with the larger root value from the heap-list
          Heap<T>* toInsert = (ptr->root->value > runner->root->value ? ptr : runner);
          Heap<T>* baseHeap = (ptr->root->value > runner->root->value ? runner : ptr);
          cout << "removeHeap(2)\n";
          removeHeap(toInsert);
          cout << "end removeHeap(2)\n";
          // and insert it into the heap with the larger value
          cout << "combineHeaps(1)\n";
          combineHeaps(baseHeap->root, toInsert);
          cout << "end combineHeaps(1)\n";

          // If two heaps of equal rank were found, check again to ensure that the changes did not create more equal-rank heaps.
          loopAgain = true;
        }
        runner = runner->right;
      }
      ptr = ptr->right;
    } while (ptr != smallest);
  }
}

//removeHeap: private: Removes a heap from the circular, doubly-linked list of heaps, and returns a pointer to its root node.
template <class T>
void FibonacciHeap<T>::removeHeap(Heap<T>* heap)
{
  Heap<T>* toRemove = heap;
  // Reconnect doubly linked list
  heap->left->right = heap->right;
  heap->right->left = heap->left;

  // Reset heap's left and right pointers NOTE: This does NOT change the children, only the structure of the chain of heaps.
  heap->left = nullptr;
  heap->right = nullptr;

}

//combineHeaps: Private: attatches a heap to an existing heap, preserving heap order.
template <class T>
void FibonacciHeap<T>::combineHeaps(HeapNode<T>* baseHeapRoot, Heap<T>* subHeap)
{
  HeapNode<T>* ptr = baseHeapRoot;

  // Find the first (if any) child of the base heap that is greater than the root of the heap to-be-added
  for (HeapNode<T>* node : ptr->children)
  {
    if (subHeap->root->value > node->value)
    {
      // Recursively continue down the heap until you find the best spot to insert.
      combineHeaps(node, subHeap);
      break; // But only follow one branch of the heap.
    }
  }
  // Add the root of the subheap to the children of the node where they should be inserted.
  baseHeapRoot->children.push_back(subHeap->root);
  subHeap->root = nullptr;


}

//setSmallest: private: used to find the new min after a deleteMin call
template <class T>
void FibonacciHeap<T>::setSmallest()
{
  Heap<T>* ptr = smallest->right;
  Heap<T>* init = smallest; // Used to keep track of where we started, since smallest will change.

  while (ptr != init)
  {
    if (ptr->root->value < smallest->root->value)
      smallest = ptr;

    ptr = ptr->right;

  }
}

#endif
