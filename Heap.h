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
  ~Heap();

  bool Insert(const T _value);
  bool Delete(const T _value);
  bool Search(const T _value) const;

  HeapNode<T>* root;
  Heap<T>* right;
  Heap<T>* left;
};




#endif
