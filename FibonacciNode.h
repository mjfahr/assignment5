/*
Copyright (C) 2018  Michael Fahr, Adam Goertz, Alec Ray

This program is free software: you may redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but without any guarantee of its fitness for any particular purpose. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>
*/

#ifndef FIBONACCINODE_H
#define FIBONACCINODE_H


template <class T>
class FibonacciNode
{
public:
  FibonacciNode() { marked = false;
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
