#include "FibonacciHeap.h"
#include <string>

int main()
{
  FibonacciHeap<string>* h1 = new FibonacciHeap<string>();

  h1->Insert("hello");
  h1->Insert("apple");
  h1->Insert("banana");

  h1->print();

  //cout << h1->peekMin() << endl;
  //h1->extractMin();

  h1->Delete(h1->getNode("hello"));

  h1->print();

  return 0;
}
