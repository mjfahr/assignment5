#ifndef HEAP_NODE_H
#define HEAP_NODE_H

#include <vector>

template <class T>
class HeapNode
{
public:
  HeapNode() {marked = false;}
  HeapNode(T _value) { marked = false;
                       value = _value; }

  void addChild(T _value) { children.push_back(new HeapNode<T>(_value)); }

  void setMarked() { marked = true; }
  void setUnmarked() { marked = false; }
  bool isMarked() { return marked; }

  int numChildren() { return children.size(); }

  T value;
  bool marked;
  HeapNode<T>* parent;
  std::vector<HeapNode<T>*> children;

};


#endif
