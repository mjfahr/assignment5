#ifndef HEAP_H
#define HEAP_H


#include <vector>
#include <iostream>

using namespace std;

template <class T>
class Heap
{
public:
  Heap() { empty = true; marked = false; parent = nullptr; }
  Heap(const T _value) { nodeValue = _value; empty = false; marked = false; parent = nullptr; }
  ~Heap();

  bool Insert(const T _value);
  bool extractMin();
  void print();

  bool isMarked();
  void mark();
  void unmark();

  bool empty;
  bool marked;
  T nodeValue;
  vector<Heap<T>*> children;
  Heap<T>* parent;

  //Heap<T>* left;
  //Heap<T>* right;

};

template <class T>
Heap<T>::~Heap()
{
  for (Heap<T>* subHeap : children)
    delete subHeap;

  delete this;
}

template <class T>
bool Heap<T>::Insert(const T _value)
{
  // If the heap is empty, _value becomes the first value
  if (empty)
  {
    nodeValue = _value;
    empty = false;
    parent =  nullptr;
    return true;
  }
  else
  {

    Heap<T>* newHeap = new Heap<T>(_value);

    // If the value to be inserted is smaller than the heap's root, it violates the heap ordering
    if (_value < nodeValue)
      return false;
    // If the current subheap has children, try to insert the new heap into one of them.
    else if (children.size() != 0)
    {
      for (Heap<T>* childNode : children)
        if (childNode->Insert(_value))
          return true;
    }

    // If the value did not fit into any childen.
    children.push_back(newHeap);
    newHeap->parent = this;
    return true;

  }
}

template <class T>
bool Heap<T>::extractMin()
{

}

template <class T>
void Heap<T>::print()
{
  cout << nodeValue;
  cout << "(";
  for (Heap<T>* childNode : children)
  {
    childNode->print();
  }
  cout << ") ";
}


#endif
