#ifndef FIBONACCI_NODE_H
#define FIBONACCI_NODE_H


template <class T>
class FibonacciNode
{
public:
  FibonacciNode() {marked = false;
              parent = nullptr;
              child = nullptr;
              left = nullptr;
              right = nullptr;
              rank = 0; }

  FibonacciNode(T _value) { marked = false;
                       value = _value;
                       parent = nullptr;
                       child = nullptr;
                       left = nullptr;
                       right = nullptr;
                       rank = 0; }


  T value;
  bool marked;
  int rank; // number of childen NOTE: 'rank' is referred to in the algorithms book as 'degree', there is also a function in FibonacciHeap that can find the rank of a node, but using a variable would be faster.

  FibonacciNode<T>* parent;
  FibonacciNode<T>* child;

  FibonacciNode<T>* left;
  FibonacciNode<T>* right;

};


#endif