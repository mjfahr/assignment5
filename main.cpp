#include "FibonacciHeap.h"

using namespace std;



int main()
{
  FibonacciHeap<int> h1;

  h1.Insert(4);
  h1.Insert(10);
  h1.Insert(5);
  h1.Insert(7);


  h1.print();



  //h1.deleteMin();

  //h1.print();

  return 0;
}