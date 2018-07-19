
//#include "FibonacciHeap.h"
#include <iostream>
#include "Heap.h"

using namespace std;



int main()
{
  Heap<int> h1;

  h1.Insert(4);
  h1.Insert(10);
  h1.Insert(5);
  h1.Insert(7);
  h1.Insert(6);
  h1.Insert(9);
  h1.Insert(11);

  h1.print();



  //h1.deleteMin();

  //h1.print();

  return 0;
}
