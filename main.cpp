#include "FibonacciHeap.h"
#include <iostream>


using namespace std;

int main()
{
  FibonacciHeap<int> h1;

  h1.Insert(5);



  h1.Insert(6);



  h1.Insert(4);

  h1.print();

  h1.deleteMin();

  h1.print();

  return 0;
}
