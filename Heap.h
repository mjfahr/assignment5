#ifndef HEAP_H
#define HEAP_H

#include "HeapNode.h"

template <class T>
class Heap
{
public:
  Heap() { root = nullptr; }
  Heap(T rootValue) { root = new HeapNode<T>(rootValue); }
  ~Heap();

  bool Insert(const T _value);
  bool Delete(const T _value);
  bool Search(const T _value) const;

  HeapNode<T>* root;
};




#endif
