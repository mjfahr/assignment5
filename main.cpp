

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

  h1.print();
  cout << "h1: Smallest: " << h1.peekMin() << endl;

  h2.Insert(3);
  h2.Insert(6);
  h2.Insert(1);
  h2.Insert(25);

  h2.print();
  cout << "h2: Smallest: " << h2.peekMin() << endl;

  //Merge is not working, for some unknown reason
  // FibonacciHeap<int> h3 = h1.Merge(h2);
  // h3.print();
  // cout << "h3: Smallest: " << h3.peekMin() << endl;


  //h1.decreaseKey();

  //h1.deleteMin();

  return 0;
}
