#ifndef HEAP_H
#define HEAP_H

#include "HeapNode.h"

using namespace std;

template <class T>
class Heap
{
public:
  Heap() { root = nullptr;
           right = nullptr;
           left = nullptr; }
  Heap(T rootValue) { root = new HeapNode<T>(rootValue);
                      right = nullptr;
                      left = nullptr; }
  Heap(HeapNode<T>* newRoot) { root = newRoot; }
  ~Heap();

  bool Insert(const T _value);
  bool Delete(const T _value);
  bool Search(const T _value) const;

  bool isEmpty() { return root = nullptr; }

  HeapNode<T>* root; // Potential changes: (1) add a new layer: HeapList which separates Left and Right from the heap itself (2) make the children of a heap heaps themselves -- a fully recursive data structure.
  Heap<T>* right;
  Heap<T>* left;

private:
  void destructor(HeapNode<T>* current);

};

template <class T>
Heap<T>::~Heap()
{
  destructor(root);
}

// Recursive helper function for the destructor
template <class T>
void Heap<T>::destructor(HeapNode<T>* current)
{
  for (HeapNode<T>* node : current->children)
    destructor(node);

  delete current;
}

template <class T>
bool Heap<T>::Insert(const T _value)
{

}

template <class T>
bool Heap<T>::Delete(const T _value)
{

}

template <class T>
bool Heap<T>::Search(const T _value) const
{

}


#endif
