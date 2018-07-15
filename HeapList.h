#ifndef HEAP_LIST_H
#define HEAP_LIST_H

#include <limits>
#include <type_traits>
#include "Heap.h"

template <class T>
class HeapList
{
public:
  HeapList();
  HeapList(Heap<T>* initHeap);
  ~HeapList();

  void addHeap(Heap<T>* newHeap);
  void deleteMin();
  void decreaseKey(HeapNode<T>* node);

  Heap<T>* smallest;
};




#endif
