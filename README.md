# assignment5
Implementation of Fibonacci Heap

The Fibonacci Heap is a min-heap data structure that attempts to provide O(1)
amortized 'insert', 'min-access', and 'decrease_key' operations, as well as amortized
O(log(N)) 'extract_min' and 'delete' operations.


Compilation Instructions:

The data structure consists of two header files, "FibonacciNode.h" and  "FibonacciHeap.h".

To use the Fibonacci Heap, simply place these header files in the directory with your project,
or your includes directory, and add

  #include "FibonacciHeap.h"

or

  #include <FibonacciHeap.h>

respectively, to the relevant files in your project, and compile normally.


Also included is a custom "main.cpp" file containing some pre-written tests.
This file is not necessary for the function of the heap.
