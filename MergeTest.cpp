#include "FibonacciHeap.h"
#include <iostream>

int main()
{
    cout << "Testing of the Merge operation:\n";
    FibonacciHeap<int> h1;
    FibonacciHeap<int> h2;
    FibonacciHeap<int> h3;

    cout << "Fibonacci Heap 1:\n";
    h1.Insert(1);
    h1.Insert(2);
    h1.Insert(3);
    h1.extractMin();
    h1.print();

    cout << "Fibonacci Heap 2:\n";
    h2.Insert(4);
    h2.Insert(5);
    h2.Insert(6);
    h2.extractMin();
    h2.print();

    cout << "Combined Fibonacci Heap:\n";
    h1.Merge(h1, h2);
    h1.print();

    return 0;
}
