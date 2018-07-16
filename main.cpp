#include "FibonacciHeap.h"
#include <iostream>


using namespace std;

int main()
{
  FibonacciHeap<int> h1;

  h1.Insert(5);

  cout << h1.getMin() << endl;

  h1.Insert(6);

  cout << h1.getMin() << endl;

  h1.Insert(4);

  cout << h1.getMin() << endl;

  return 0;
}
