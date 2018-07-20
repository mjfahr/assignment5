#ifndef HEAP_NODE_H
#define HEAP_NODE_H


template <class T>
class FibonacciNode
{
public:
  HeapNode() {marked = false;
              parent = nullptr;
              child = nullptr;
              left = nullptr;
              right = nullptr; }

  HeapNode(T _value) { marked = false;
                       value = _value;
                       parent = nullptr;
                       child = nullptr;
                       left = nullptr;
                       right = nullptr; }


  T value;
  bool marked;

  FibonacciNode<T>* parent;
  FibonacciNode<T>* child;

  FibonacciNode<T>* left;
  FibonacciNode<T>* right;

};


#endif
