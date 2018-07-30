#include "FibonacciHeap.h"

using namespace std;

int main()
{
  FibonacciHeap<int> h1;

  FibonacciHeap<int> h2;

  h1.Insert(4);
  h1.Insert(10);
  h1.Insert(5);
  h1.Insert(7);

  //h1.print();
  //cout << "h1: Smallest: " << h1.peekMin() << endl;

  h2.Insert(3);
  h2.Insert(6);
  h2.Insert(1);
  h2.Insert(25);

  //h2.print();
  //cout << "h2: Smallest: " << h2.peekMin() << endl;

  FibonacciHeap<int> h3 = FibonacciHeap<int>::Merge(h1, h2);
  cout << "h3: " << endl;
  h3.print();


  // FibonacciHeap<int> h4 = h1;
  // cout << "h4: " << endl;
  // h4.print();
  // cout << endl;
  //
  // FibonacciNode<int>* n1 = h1.getNode(5);
  // h1.decreaseKey(n1, 2);
  // cout << h1.peekMin() << endl;



  //h1.deleteMin();

  return 0;
}
