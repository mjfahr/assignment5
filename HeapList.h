#ifndef HEAP_LIST_H
#define HEAP_LIST_H

#include <limits>
#include "Heap.h"

using namespace std;

template <class T>
class HeapList
{
public:
  HeapList() { smallest = nullptr; }
  HeapList(Heap<T>* initHeap) { smallest = initHeap; }
  ~HeapList();

  void addHeap(Heap<T>* newHeap);
  void deleteMin();
  void decreaseKey(HeapNode<T>* node, T val);

private:

  static const T MIN = std::numeric_limits<T>::lowest();
  Heap<T>* smallest;

};

template <class T>
HeapList<T>::~HeapList()
{

}

#endif
